#include <iostream>
#include <vector>
#include <unordered_set>


int main () {
    std::vector <int> vec;
    auto n = 1;
    vec.push_back (n);
    for (auto i = 0; n <= 8; ++i) {
        if (i > 0) n = vec[i] + vec [i-1];
        vec.push_back (n);
    }
    for (auto next : vec) {
        std::cout << next << " ";
    }
    std::cout << std::endl;
    auto del_duplicate = [] (const std::vector <int>& vec) {
        std::unordered_set <int> list;
        for (auto next : vec) {
            list.insert(next);
        }
        std::vector<int> new_vec;
        for (auto next : list) {
            if (list.count (next) == 1) {
                new_vec.push_back (next);
            }
        }
        return std::make_unique <std::vector<int>>(new_vec);
    };

    std::vector <int> new_vec = *del_duplicate (vec);
    for (auto next : new_vec) {
        std::cout << next << " ";
    }
    std::cout << std::endl;
    return 0;
}
