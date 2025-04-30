#include <iostream>
#include "Date.h"
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <iomanip>

typedef double TEMP;

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "usage: <program name> <data file>" << std::endl;
        return -1;
    }
    std::string filen = argv[1];
    std::ifstream ist{filen};
    if(!ist) {
        throw std::runtime_error("Can't open input file " + filen);
        return -1;
    }
    std::map<Date, TEMP> temps;

    std::string s;
    while(std::getline(ist, s)) {
        std::istringstream iss(s);
        std::string cont, country, state, city, m, d, y, val;
        std::getline(iss, cont, ',');
        std::getline(iss, country, ',');
        std::getline(iss, state, ',');
        std::getline(iss, city, ',');

        std::getline(iss, m, ',');
        std::getline(iss, d, ',');
        std::getline(iss, y, ',');
        std::getline(iss, val, ',');

        int month = std::stoi(m);
        int day = std::stoi(d);
        int year = std::stoi(y);

        Date date(year, month, day);

        TEMP temp = std::stod(val);

        temps[date] = temp;
    }
    while(std::cin.good()) {
        int iy, im, id, ey, em, ed;
        std::cout << "Starting date (YYYY, MM, DD): ";
        std::cin >> iy >> im >> id;
        Date start(iy, im, id);
        std::cout << "Ending date (YYYY, MM, DD): ";
        std::cin >> ey >> em >> ed;
        Date end(ey, em, ed);
        for(auto it = temps.begin(); it != temps.end(); it++) {
            const Date& date = it -> first;
            const TEMP& temp = it -> second;
            if(start <= date && date <= end) {
                std::cout << date << "     " << std::fixed << std::setprecision(1) << temp << std::endl;            
            }
        }
    }
    return 0;
}