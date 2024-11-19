#include <iostream>
#include <string>

class Toy {
    std::string toy_name = "";
    public:
    Toy(std::string in_toy_name) : toy_name(in_toy_name) {};
    Toy() : toy_name("Unknow_toy") {};
    ~Toy() {
        std::cout << "The toy named " << toy_name << " was drop." << std::endl;
    }
    std::string get_toy_name () {
        return toy_name;
    }
};
class Dog {
    std::string name = "";
    std::shared_ptr <Toy> its_toy = nullptr;
    public:
    Dog (std::string in_name, std::shared_ptr<Toy> in_toy_ptr) :
            name (in_name), its_toy(in_toy_ptr) {}; //what 'bout nullptr
    Dog () : Dog("Unknow", nullptr) {};
    Dog (std::string in_name) : 
            Dog(in_name, nullptr) {};
    Dog (std::shared_ptr<Toy> in_toy_ptr) : 
            Dog("Unknow", in_toy_ptr) {};

    void get_toy (std::shared_ptr<Toy>& in_toy_ptr) {
        if (its_toy != nullptr) {
            if(in_toy_ptr == its_toy) {
                std::cout << name << ": I already have this toy." << std::endl;
            } else if (in_toy_ptr.use_count() > 1) {
                std::cout << name << ": Another dog is playing with this toy." << std::endl;
            } else {
                std::cout << name << " drops " << its_toy -> get_toy_name();
                its_toy = in_toy_ptr;
                std::cout << name << " takes " << its_toy -> get_toy_name();
            }
        } else if (in_toy_ptr.use_count() > 1) {
            std::cout << name << ": Another dog is playing with this toy." << std::endl;
        } else {
            its_toy = in_toy_ptr;
            std::cout << name << " takes " << its_toy -> get_toy_name() << std::endl;
        }
    }
    void drop_toy () {
        if (its_toy != nullptr) {
            std::cout << name << " drops " << its_toy -> get_toy_name() << std::endl;
            its_toy = nullptr;
        } else {
            std::cout << name << ": Nothing to drop" << std::endl;
        }
    }
};

int main () {

    std::shared_ptr <Toy> ball = std::make_shared <Toy> ("Ball");
    std::shared_ptr <Toy> bone = std::make_shared <Toy> ("Bone");

    Dog* a = new Dog ("Volf", ball);
    Dog* b = new Dog ("Nikolay");
    Dog* c = new Dog ();

    b -> get_toy (ball);
    b -> drop_toy ();
    b -> get_toy (bone);
    a -> drop_toy ();
    c -> get_toy (ball);

    delete (a);
    delete (b);
    delete (c);

    return 0;
}