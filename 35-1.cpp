#include <iostream>

int main () {

    std::initializer_list<int> list {1, 2, 3, 4, 5};
    for (auto i : list) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}