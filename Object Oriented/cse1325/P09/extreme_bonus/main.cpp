#include <iostream>
#include <stdexcept>
#include <string>
#include "Timer.h"


int main(int argc, char* argv[]) {
    if(argc == 4) {
       std::string _hours_str = argv[1];
        std::string _minutes_str = argv[2];
        std::string _seconds_str = argv[3];

        int _hours = std::stoi(_hours_str);
        int _minutes = std::stoi(_minutes_str);
        int _seconds = std::stoi(_seconds_str);

        try{
            Timer _timer{_hours, _minutes, _seconds};
            std::cout << "Enter 'q' to quit." << std::endl;
            while(1) {
                std::string inp;
                _timer.print();
                std::getline(std::cin, inp);
                if(inp == "q") {
                return 0;
                }
                _timer.tic();
        }
        } catch(std:: out_of_range& e) {
            std::cerr << e.what() << std::endl;
        } catch(std:: runtime_error& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    else {
        std::cerr << "usage: clock <hour> <minutes> <seconds>" << std::endl;
        return -1;
    }
}