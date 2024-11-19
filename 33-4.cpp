#include <iostream>

template <typename T>
void input(T array[8])
{
    std::cout << "Fill the array (8):" << std::endl;
    for (int i = 0; i < 8; ++i) {
        std::cin >> array[i];
    }
    std::cout << "Done!" << std::endl;
}

template <typename T>
void arithmetic_mean (T array[8]) {
    T sum;
    for (int i = 0; i < 8; ++i) {
        sum += array [i];
    }
    std::cout << "The arithmetic mean is: " << sum / 8 << std::endl;
}

int main () {

    int arr[8];
    input (arr);
    arithmetic_mean (arr);

    return 0;

}