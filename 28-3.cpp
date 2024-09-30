#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <ctime>
#include <mutex>
#include <chrono>

std::mutex block_out;

class Cafe {
    unsigned order_counter = 0;

    public:

    void add_counter () {
        ++order_counter;
    }
    unsigned get_counter () {
        return order_counter;
    }
};

class Menu {
    std::vector <std::string> dishes {"Pizza", "Soup", "Steak", "Salad", "Susi"};

    public:
    std::vector <std::string> get_menu () {
        return dishes;
    }

};

void delivery (std::string in_order, Cafe* new_cafe) {
    std::this_thread::sleep_for(std::chrono::seconds(30));
    std::cout << "\t" << in_order << " DELIVERED." << std::endl;
    new_cafe -> add_counter();
}

void kitchen (std::string dish, Cafe* new_cafe) {
    block_out.lock();
    std::cout << "Start to cook a " <<  dish << "." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(rand() % 15 + 5));
    std::thread new_delivery (delivery, dish, new_cafe);
    new_delivery.detach();
    std::cout << dish << " is ready. Sent for delivery." << std::endl;
    block_out.unlock();

}

void to_order (std::vector <std::string> in_menu, Cafe* new_cafe) {
    std::string ordered_dish = "";
    ordered_dish = in_menu[rand() % in_menu.size()];
    std::cout << "\tNEW ORDER: " << ordered_dish << "." << std::endl;
    std::thread new_dish (kitchen, ordered_dish, new_cafe);
    new_dish.join();
}

int main () {
    Cafe* new_cafe = new Cafe;
    Menu* new_menu = new Menu;
    std::srand(time(0));
    while(new_cafe -> get_counter() < 10) {
        to_order (new_menu -> get_menu(), new_cafe);
    }
    std::cout << "The working day is over" << std::endl;

    return 0;
}