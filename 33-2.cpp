#include <iostream>
#include <exception>
#include <ctime>

class fishing_done_exception : public std::exception {
    const char* what() const noexcept override {
        return "You catch a fish!";
    }
};

class shoe_caught_exception : public std::exception {
    const char* what() const noexcept override {
        return "You catch a boot.";
    }
};

void fishing (std::string pond [9], const unsigned& sector,
        unsigned& boot, bool& fish) {
    if (pond [sector] == "fish") {
        fish = true;
        throw fishing_done_exception();
    } else if (pond [sector] == "boot") {
        ++boot;
        pond [sector] = "empty";
        throw shoe_caught_exception();
    } else {
        std::cout << "There's nothing here" << std::endl;
    }
}

void validate (int sector, size_t arr_size) {
    if (sector < 0 || sector >= arr_size) {
        throw std::invalid_argument ("Invalid sector value!");
    }
}

int main () {
    std::string pond [9];
    std::srand (std::time(0));
    pond [std::rand() % 9] = "fish";
    for (unsigned i = 0; i < 3;) {
        unsigned n = std::rand() % 9;
        if (pond [n] != "fish" && pond [n] != "boot") {
            pond [n] = "boot";
            ++i;
        } else continue;
    } 
    for (unsigned i = 0; i < 6;) {
        unsigned n = std::rand() % 9;
        if (pond [n] != "fish" && pond [n] != "boot") {
            pond [n] = "empty";
            ++i;
        } else continue;
    }  
    unsigned co = 0;
    unsigned boot = 0;
    bool fish = false;
    int sector = 0;

    while (!fish && boot != 3) {
        ++co;
        try {
            sector = 0;
            std::cout << "Enter the sector:" << std::endl;
            std::cin >> sector;
            validate (sector, sizeof(pond)/sizeof(pond [0]));
        } catch (std::exception& x) {
            std::cerr << "CAUGHT EXCEPTION: " << x.what () << std::endl;
            continue;
        }
        try {
            fishing (pond, sector, boot, fish);
        } catch (std::exception& x) {
            std::cout << x.what() << " You got it on the " << co << " try." << std::endl;
            continue;
        }
    }

    return 0;
}