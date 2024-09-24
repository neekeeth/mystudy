#include <iostream>
#include <string>
#include <thread>
#include <ctime>
#include <chrono>
#include <cassert>
#include <vector>
#include <map>
#include <mutex>

std::mutex block_out;

class Swimmer {
    std::string name = "Swimmer";
    double swim_speed = 0;
    time_t finish = 0;
    bool is_finish = false;

    public:
    Swimmer (std::string inName, double inSpeed) : swim_speed(inSpeed) {
        name += inName;
        assert(inSpeed > 0);
    }
    void set_is_finish () {
        if(finish != 0) is_finish = true;
    }
    bool get_is_finish () {
        return is_finish;
    }
    void set_finish_time (std::time_t inFinish) {
        finish = (inFinish > 0) ? inFinish : 0;
    }
    double get_swim_speed () {
        return swim_speed;
    }
    std::string get_name () {
        return name;
    }
    time_t get_finish_time () {
        return finish;
    }
};

void to_create_swimmers (std::vector <Swimmer*>& swimmers) {
    unsigned number = 1;
    std::srand(time(0));
    for (unsigned i = 0; i < 6; ++i) {
        Swimmer* newSwimmer = new Swimmer(std::to_string(number), (rand() % 6 + 5));
        swimmers.push_back(newSwimmer);
        ++number;
    }
}

bool not_everyone_finished (std::vector <Swimmer*>& swimmers) {
    for (unsigned i = 0; i < swimmers.size(); ++i) {
        if(!swimmers[i]->get_is_finish()) return true;
    }
    return false;
}
void swim (Swimmer* this_swimmer, std::time_t start, 
        std::map <time_t, Swimmer*>& board_of_honor) {
    std::time_t swimming = std::time(nullptr);
    double distance = 0;
    while(distance < 100) {
        swimming = std::time(nullptr);
        distance = this_swimmer->get_swim_speed() * (swimming - start);
        if(distance >= 100) break;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        block_out.lock();
        std::cout << "The swimmer " << this_swimmer -> get_name() << " swam " 
            << distance << " metres." << std::endl;
        block_out.unlock();
    }
    this_swimmer -> set_finish_time(swimming - start);
    this_swimmer -> set_is_finish();
}

void lets_start (std::vector<Swimmer*>& swimmers, std::time_t start,
        std::map <time_t, Swimmer*>& board_of_honor) {
    std::thread swimmer1 (swim, swimmers[0], start, std::ref(board_of_honor));
    std::thread swimmer2 (swim, swimmers[1], start, std::ref(board_of_honor));
    std::thread swimmer3 (swim, swimmers[2], start, std::ref(board_of_honor));
    std::thread swimmer4 (swim, swimmers[3], start, std::ref(board_of_honor));
    std::thread swimmer5 (swim, swimmers[4], start, std::ref(board_of_honor));
    std::thread swimmer6 (swim, swimmers[5], start, std::ref(board_of_honor));
    swimmer1.join();
    swimmer2.join();
    swimmer3.join();
    swimmer4.join();
    swimmer5.join();
    swimmer6.join();
}


void to_sort (std::vector<Swimmer*>& swimmers) {
    for (int i = 0; i < swimmers.size(); ++i)
    {
        for (int j = swimmers.size()-1; j > i; --j)
        {
            if (swimmers[i]->get_finish_time() > swimmers[j]->get_finish_time()) {  
                Swimmer* tempSwimmer = swimmers[i];
                swimmers[i] = swimmers[j];
                swimmers[j] = tempSwimmer;
            }
        }
    }
}

void print_all (std::vector<Swimmer*>& swimmers) {
    unsigned number = 1;
    for(auto swimmer : swimmers) {
        std::cout << number << ". " << swimmer->get_name() << " time: "
                << swimmer->get_finish_time () << " sec." << std::endl;
        ++number;
    }
}

int main () {
    std::vector <Swimmer*> swimmers;
    to_create_swimmers(swimmers);
    std::map <time_t, Swimmer*> board_of_honor;
    std::time_t start = std::time(nullptr);
    lets_start(swimmers, start, board_of_honor);
    to_sort(swimmers);
    print_all(swimmers);

    for(auto swimmer : swimmers) {
        delete swimmer;
    }
    
    return 0;
}