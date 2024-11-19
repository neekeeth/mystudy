#include <iostream>

double get_double (std::string& a) {
    double b {atof(a.c_str())};
    return b;
}

double get_int (std::string& a) {
    int c = atoi(a.c_str());
    return c;
}

int main () {
    std::string a = "ppp";
    double b = 0;
    int c = 0;
    try {
        b = get_double(a);
        std::cout << b << std::endl;
    } catch (std::exception& x) {
        std::cerr << "CATCH EXEPT.: " << x.what() << std::endl;
    }
    try {
        c = get_int(a);
        std::cout << c << std::endl;
    } catch (std::exception& x) {
        std::cerr << "CATCH EXEPT.: " <<  x.what() << std::endl;
    }

    if (b == c) {
        std::cout << b << " = " << c << std::endl;
    }

    return 0;
}