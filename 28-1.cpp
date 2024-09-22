#include <iostream>
#include <string>
#include <thread>
#include <cassert>

class Swimmer {
    std::string name = "Swimmer";
    int swim_speed = 0;

    public:
    Swimmer (std::string inName, int inSpeed) : name(inName), swim_speed(inSpeed) {
        assert(inSpeed < 0);
    }
};

int main () {

    return 0;
}