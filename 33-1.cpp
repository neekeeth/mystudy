#include <iostream>
#include <string>
#include <map>

std::string add_article (const std::map <std::string, int>& in_map) {
    std::string article = "";
    std::cin >> article;
    if (in_map.find (article) == in_map.end ()) {
        throw std::invalid_argument ("Invalid article!");
    } else return article;
}

int add_quantity () {
    int quantity = 0;
    std::cin >> quantity;
    if (quantity <= 0) {
        throw std::invalid_argument ("Invalid quantity!");
    } else return quantity;
}

int add_quantity (const std::map <std::string, int>& in_map, const std::string& article) {
    int quantity = 0;
    std::cin >> quantity;
    if (in_map.find(article) -> second < quantity || quantity <= 0) {
        throw std::invalid_argument ("Invalid quantity!");
    } else return quantity;
}

void add_warehouse (std::map <std::string, int>& warehouse) {
    std::string command = "";
    std::cout << "---ADD WAREHOUSE---" << std::endl;
    std::string article = "";
    int quantity = 0;
    while (command != "end") {
        std::cout << "Enter \"add\" or \"end\":" << std::endl;
        std::cin >> command;
        if (command != "add") continue;
        std::cout << "Article:" << std::endl;
        std::cin >> article;
        std::cout << "Quantity:" << std::endl;
        while (quantity == 0) {
            try {
                quantity = add_quantity();
            } catch (const std::exception& x) {
                std::cerr << "CAUGHT EXCEPTION: " << x.what() << std::endl;
                std::cout << "Try again." << std::endl;
                continue;
            }
        }
        if (warehouse.find(article) != warehouse.end()) {
            warehouse.find(article) -> second += quantity;
            std::cout << "Added!" << std::endl;
            continue;
        }
        warehouse.insert({article, quantity});
        std::cout << "Added!" << std::endl;
    }
}

void add_basket (std::map <std::string, int>& warehouse,
        std::map <std::string, int>& basket) {
    std::string command = "";
    std::cout << "---ADD BASKET---" << std::endl;
    std::string article = "";
    int quantity = 0;
    while (command != "end") {
        std::cout << "Enter \"add\" or \"end\":" << std::endl;
        std::cin >> command;
        if (command != "add") continue;
        std::cout << "Article:" << std::endl;
        while (article == "") {
            try {
                article = add_article(warehouse);
            } catch (const std::exception& x) {
                std::cerr << "CAUGHT EXCEPTION: " << x.what() << std::endl;
                std::cout << "Try again." << std::endl;
                continue;
            }
        }
        std::cout << "Quantity:" << std::endl;
        while (quantity == 0) {
            try {
                quantity = add_quantity(warehouse, article);
            } catch (const std::exception& x) {
                std::cerr << "CAUGHT EXCEPTION: " << x.what() << std::endl;
                std::cout << "Try again." << std::endl;
                continue;
            }
        }
        if (basket.find (article) != basket.end ()) {
            warehouse.find (article) -> second -= quantity;
            basket.find (article) -> second += quantity;
            std::cout << "Added!" << std::endl;
        } else {
            warehouse.find (article) -> second -= quantity;
            basket.insert ({article, quantity});
            std::cout << "Added!" << std::endl;
        }   
    }
}

void remove_basket (std::map <std::string, int>& warehouse,
        std::map <std::string, int>& basket) {
    if (basket.begin() == basket.end()) {
        throw std::runtime_error("The basket is empty!");
    }
    std::string command = "";
    std::cout << "---REMOVE FROM BASKET---" << std::endl;
    while (command != "end" && basket.begin() != basket.end()) {
        std::string article = "";
        int quantity = 0;
        std::cout << "Enter \"remove\" or \"end\":" << std::endl;
        std::cout << "Article:" << std::endl;
        while (article == "") {
            try {
                article = add_article(basket);
            } catch (const std::exception& x) {
                std::cerr << "CAUGHT EXCEPTION: " << x.what() << std::endl;
                std::cout << "Try again." << std::endl;
                continue;
            }
        }
        std::cout << "Quantity:" << std::endl;
        while (quantity == 0) {
            try {
                quantity = add_quantity(basket, article);
            } catch (const std::exception& x) {
                std::cerr << "CAUGHT EXCEPTION: " << x.what() << std::endl;
                std::cout << "Try again." << std::endl;
                continue;
            }
        }
        if (basket.find(article) -> second == quantity) {
            basket.erase(basket.find(article));
            warehouse.find(article) -> second += quantity;
            std::cout << "The product has been deleted from the basket." << std::endl;
        } else {
            basket.find(article) -> second -= quantity;
            warehouse.find(article) -> second += quantity;
            std::cout << "The rest of the product: " << basket.find(article) -> first << std::endl;
            std::cout << "in the basket is:" << basket.find(article) -> second << std::endl;
        }

    }
}

void working (std::map <std::string, int>& warehouse) {
    std::map <std::string, int> basket;
    std::string command = "";
    while (command != "exit") {   
        std::cout << "Enter the command (add, remove or exit):" << std::endl;
        std::cin >> command;
        if (command == "add") {
            add_basket (warehouse, basket);
        } else if (command == "remove") {
            try {
                remove_basket (warehouse, basket);
            } catch (const std::exception& x) {
                std::cerr << "CAUGHT EXCEPTION: " <<  x.what() << std::endl;
                std::cout << "Try again." << std::endl;
                continue;
            }
        } else if (command == "exit") {
            continue;
        } else {
            std::cout << "Incorrect command! Try again." << std::endl;
            continue;
        }
    }
}


int main () {

    std::map <std::string, int> warehouse;
    add_warehouse (warehouse);

    working (warehouse);

    
    return 0;
}