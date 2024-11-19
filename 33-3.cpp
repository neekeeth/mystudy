#include <iostream>
#include <string>
#include <vector>

template <typename T1, typename T2>
class The_pair {
    T1 key;
    T2 value;

    public:
    The_pair(T1 in_key, T2 in_value) : key(in_key), value(in_value) {}
    T1 get_key() const {
        return key;
    }
    T2 get_value() const {
        return value;
    }
};

template <typename T1, typename T2>
class Registry {
    std::vector<The_pair<T1, T2>> pairs;

public:
    std::vector<The_pair<T1, T2>>& get_vec () {
        return pairs;
    }
    void add() {
        T1 key; 
        T2 value;
        std::cout << "Enter the key: " << std::endl;
        std::cin >> key;
        std::cout << "Enter the value: " << std::endl;
        std::cin >> value;
        The_pair<T1, T2> new_pair (key, value);
        pairs.push_back(new_pair);
        std::cout << "Done." << std::endl;
    }

    void to_print() const {
        for (unsigned i = 0; i < pairs.size(); ++i) {
            std::cout << "Key: " << pairs[i].get_key();
            std::cout << " Value: " << pairs[i].get_value();
            std::cout << std::endl;
        }
    }
    void to_find(T1 in_key) {
        for (auto pair : pairs) {
            if (pair.get_key() == in_key) {
                std::cout << "Key: " << pair.get_key() << " ";
                std::cout << "Value: " << pair.get_value() << std::endl;
            }
        }
    }
    void to_remove (T1 in_key) {
        for (auto it = pairs.begin(); it != pairs.end(); ) {
            if (it->get_key() == in_key) {
                it = pairs.erase(it);  // erase is returns iter on the next elem or end
            } else {
                ++it;
            }
        }
    }
};

int main() {

    Registry<int, std::string> regs;

    std::string command = "";

    while (command != "exit") {
        std::cout << "Enter the command:" << std::endl;
        std::cin >> command;
        if (command == "add") {
            regs.add();
        } else if (command == "remove") {
            std::cout << "Enter the key of pairs you want to remove:" << std::endl;
            int key_to_find = 0;
            std::cin >> key_to_find;
            regs.to_remove (key_to_find);
        } else if (command == "print") {
            regs.to_print ();
        } else if (command == "find") {
            std::cout << "Enter the key of pairs you want to find:" << std::endl;
            int key_to_find = 0;
            std::cin >> key_to_find;
                regs.to_find (key_to_find);
        }
    }

    return 0;
}