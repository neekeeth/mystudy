#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <mutex>

std::mutex block_out;

class Train {
    std::string train_name = "";
    int status = 2;
    enum train_status {
        departed = 1,
        waiting = 2,
        arrived = 3
    };
    int travel_time = 0;

    public:

    Train (std::string in_train_name, std::vector <Train*>& trains): train_name(in_train_name) {
        trains.push_back(this);
    }
    std::string get_name () {
        return train_name;
    }
    void set_status (int in_status) {
        if (    in_status == departed ||
                in_status == waiting  ||
                in_status == arrived  ) {
            status = in_status;        
        } else {
            std::cout << "Incorrect input" << std::endl;
            return;
        }
    }
    std::string get_status () {
        if (status == departed) {
            return "departed from station.";
        }
        else if (status == waiting) {
            return "is waiting.";
        }   
        else if (status == arrived) {
            return "arrived to station.";
        } else return "is wherenever.";
    }
    void set_travel_time (int in_travel_time) {
        if (in_travel_time > 0)
            travel_time = in_travel_time;
        else {
            std::cout << "Incorrect input" << std::endl;
            return;
        }
    }
    int get_travel_time () {
        return travel_time;
    }
};
void print_status (Train* desribing_train) {
    std::cout << std::endl << "The train " << desribing_train -> get_name() << " "
            << desribing_train -> get_status() << std::endl;
}
class Railway_station {
    int trains_counter = 0;
    bool is_busy = false;
    Train* parked_train = nullptr;

    public:
    void take_the_train (Train* in_parked_train) {
        parked_train = in_parked_train;
        ++trains_counter;
        is_busy = true;
    }
    void release_the_train () {
        parked_train -> set_status(1);
        print_status(parked_train);
        parked_train = nullptr;
        is_busy = false;
    }
    int get_trains_counter () {
        return trains_counter;
    }
};
void create_trains (unsigned in_number_of_trains, std::vector <Train*>& trains) {
    std::vector <std::string> names {"A", "B", "C"};
    for (unsigned i = 0; i < in_number_of_trains; ++i) {
        Train* new_train = new Train (names[i], trains);
    }
}

void set_trains_speed (std::vector <Train*>& trains) {
    for (auto train : trains) {
        std::cout << "Enter the travel time for the train "
                << train -> get_name() << " (sec):" << std::endl;
        int travel_time = 0;
        std::cin >> travel_time;
        train -> set_travel_time(travel_time);
    }
    
}

bool depart_from_station (std::string command, Railway_station* new_station) {
    if(command == "depart") {
        new_station -> release_the_train ();
        block_out.unlock();
        return false;
    } else return true;
}

void allow_departs (Railway_station* new_station) {
    std::string command = "";
    std::cout << "Enter the command:" << std::endl;
    std::cin >> command;
    while (depart_from_station(command, new_station)) {
        std::cout << "Incorrect input. Try again." << std::endl;
        std::cout << "Enter the command:" << std::endl;
        std::cin >> command; 
    }
}

void arrive_to_station (Train* arrived_train, Railway_station* new_station) {
    std::this_thread::sleep_for(std::chrono::seconds(arrived_train -> get_travel_time()));
    arrived_train -> set_status(2);
    print_status (arrived_train);
    block_out.lock();
    new_station -> take_the_train (arrived_train);
    arrived_train -> set_status(3);
    print_status (arrived_train);
    allow_departs(new_station);
}

void on_the_way (std::vector <Train*>& trains, Railway_station* new_station) {
    int co = 0;
    trains[co] -> set_status(1);
    print_status (trains[co]);
    std::thread train_1 (arrive_to_station, trains[co], new_station);
    ++co;
    trains[co] -> set_status(1);
    print_status (trains[co]);
    std::thread train_2 (arrive_to_station, trains[co], new_station);
    ++co;
    trains[co] -> set_status(1);
    print_status (trains[co]);
    std::thread train_3 (arrive_to_station, trains[co], new_station);
    train_1.join();
    train_2.join();
    train_3.join();
}


int main () {

    std::vector <Train*> trains;
    int number_of_trains = 3;
    create_trains (number_of_trains, trains);
    set_trains_speed (trains);
    Railway_station* new_station = new Railway_station;
    on_the_way(trains, new_station);
    if(new_station -> get_trains_counter() == number_of_trains) 
           std::cout << "All trains departs from station" << std::endl;
    for(auto train : trains) {
        delete train;
    }   
    delete new_station;

    return 0;
}