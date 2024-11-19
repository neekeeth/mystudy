#include <iostream>
#include <string>


class Toy_counter {
    unsigned co = 0;

    public:

    unsigned get_toy_counter () {
        return co;
    }
    void increment_toy_counter () {
        ++co;
    }
    void decrement_toy_counter () {
        --co;
    }
};

class Toy {
    std::string toy_name = "";

    public:

    Toy (std::string in_toy_name) : toy_name (in_toy_name) {}
    Toy () : toy_name ("Unknow") {}
    ~Toy () { std::cout << "The toy named " << toy_name << " was drop." << std::endl;}
    
    std::string get_toy_name () {
        return toy_name;
    }
};

class Shared_ptr_toy {
    Toy* toy_ptr = nullptr;
    Toy_counter* toy_ptr_counter = nullptr;

    public:
    Shared_ptr_toy () : toy_ptr (nullptr), toy_ptr_counter (nullptr) {}
    Shared_ptr_toy (std::string in_toy_name) : 
            toy_ptr (new Toy (in_toy_name)), toy_ptr_counter (new Toy_counter) {
        toy_ptr_counter -> increment_toy_counter();
    }
     
    Shared_ptr_toy (const Shared_ptr_toy& another_obj) ://Google why it need to get as const???
            toy_ptr (another_obj.toy_ptr), toy_ptr_counter (another_obj.toy_ptr_counter) {
        if(toy_ptr_counter != nullptr)
            toy_ptr_counter -> increment_toy_counter ();
    }
    
    Shared_ptr_toy& operator= (const Shared_ptr_toy& another_obj) {
        if (this == &another_obj) {
            return *this;
        } else if (toy_ptr != nullptr) {
            if (toy_ptr_counter -> get_toy_counter () == 1) {
                delete toy_ptr;
                delete toy_ptr_counter;
            } else {
                toy_ptr_counter -> decrement_toy_counter();
                toy_ptr = nullptr;
                toy_ptr_counter = nullptr;
            }
        } 
        toy_ptr = another_obj.toy_ptr;
        toy_ptr_counter = another_obj.toy_ptr_counter;
        return *this;
    }
     ~Shared_ptr_toy() {
        if (toy_ptr_counter != nullptr) {
            if (toy_ptr_counter->get_toy_counter() == 1) {
                delete toy_ptr;
                delete toy_ptr_counter;
            } else if (toy_ptr_counter->get_toy_counter() != 1) {
                toy_ptr_counter->decrement_toy_counter();
            }
        }
    }

    void reset() {
        if (toy_ptr_counter != nullptr) {
            if (toy_ptr_counter->get_toy_counter() == 1) {
                delete toy_ptr;
                delete toy_ptr_counter;
                toy_ptr = nullptr;
                toy_ptr_counter = nullptr;
            }
        }
    }
    Toy* get_toy_ptr () {
        return toy_ptr;
    }
    Toy_counter* get_toy_counter () {
        return toy_ptr_counter;
    }
    unsigned use_count () {
        if(toy_ptr_counter != nullptr) return toy_ptr_counter -> get_toy_counter ();
        else return 0;
    }
    std::string getToyName () {
        if(toy_ptr != nullptr) return toy_ptr -> get_toy_name ();
        else return "Nothing";
    }
};

Shared_ptr_toy make_shared_toy (std::string in_toy_name) {
   return Shared_ptr_toy (in_toy_name);
}

int main () {
    Shared_ptr_toy toy_01 = make_shared_toy("ball");
    Shared_ptr_toy toy_02(toy_01);
    Shared_ptr_toy toy_03("duck");
    std::cout << "=================================================" << std::endl;
    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
            << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
            << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;
    toy_02 = toy_03;
    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
            << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
            << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;
    toy_01.reset();
    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
            << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
            << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;
    return 0;
}