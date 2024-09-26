#include <iostream>
#include <string>
#include <thread>
#include <ctime>
#include <chrono>
#include <cassert>
#include <vector>
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
void swim (Swimmer* this_swimmer, std::vector <Swimmer*>& results) {
    std::time_t startTime = std::time(nullptr);
    double distance = 0;
    while(distance < 100) {
        distance = this_swimmer->get_swim_speed() * (std::time(nullptr) - startTime);
        if(distance >= 100) break;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        block_out.lock();
            std::cout << "The swimmer " << this_swimmer -> get_name() << " swam " 
                    << distance << " metres." << std::endl;
        block_out.unlock();
    }
    this_swimmer -> set_finish_time(std::time(nullptr) - startTime);
    this_swimmer -> set_is_finish();
    block_out.lock();
        results.push_back(this_swimmer);
    block_out.unlock();
}

void lets_start (std::vector<Swimmer*>& swimmers, std::vector<Swimmer*>& results) {
    std::thread swimmer1 (swim, swimmers[0], std::ref(results));
    std::thread swimmer2 (swim, swimmers[1], std::ref(results));
    std::thread swimmer3 (swim, swimmers[2], std::ref(results));
    std::thread swimmer4 (swim, swimmers[3], std::ref(results));
    std::thread swimmer5 (swim, swimmers[4], std::ref(results));
    std::thread swimmer6 (swim, swimmers[5], std::ref(results));
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

void print_all (std::vector<Swimmer*>& results) {
    unsigned number = 1;
    for(auto swimmer : results) {
        std::cout << number << ". " << swimmer->get_name() << " " <<
                swimmer->get_finish_time() << " sec." << std::endl;
        ++number;
    }
}

int main () {
    std::vector <Swimmer*> swimmers;
    to_create_swimmers(swimmers);
    std::vector <Swimmer*> results;
    lets_start(swimmers, results);
    to_sort(swimmers);
    print_all(results);

    for(auto swimmer : swimmers) {
        delete swimmer;
    }
    
    return 0;
}