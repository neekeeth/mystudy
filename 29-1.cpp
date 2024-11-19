#include <iostream>
#include <string>
#include <vector>

class Talent {
    public:
    virtual std::string show_me () = 0;
    virtual ~Talent () {}
};
class Swimming: virtual public Talent {
    public:
    virtual std::string show_me () {
        return "swimming";
    }
};
class Counting: virtual public Talent {
    public:
    virtual std::string show_me () {
        return "counting";
    }
};
class Dancing: virtual public Talent {
    public:
    virtual std::string show_me () {
        return "dancing";
    }
};
class Dog {
    std::string dog_name = "";
    std::vector <Talent*> talents;
    void show_talent () {
        for(auto talent : talents) {
            std::cout << "It can " << talent -> show_me() << "." << std::endl;
        }
    }
    void get_name () {
        if(dog_name != "") {
            std::cout << "This is " << dog_name 
                    << " and it has some talents:" << std::endl;
        }
    }
    public:
    Dog (std::string in_dog_name) : dog_name (in_dog_name) {}
    void set_talent (Talent* new_talent) {
        talents.push_back(new_talent);
    }
    ~Dog () {
        for (auto talent : talents) {
            delete talent;
        }
    }
    void get_bio () {
        get_name();
        show_talent();
    }
};

int main () {
    Dog* new_dog = new Dog("Doggy");
    Talent* swim = new Swimming();
    new_dog -> set_talent(swim);
    Talent* count = new Dancing();
    new_dog -> set_talent(count);
    Talent* dance = new Counting();
    new_dog -> set_talent(dance);
    new_dog -> get_bio();

    delete(new_dog);
    return 0;

}