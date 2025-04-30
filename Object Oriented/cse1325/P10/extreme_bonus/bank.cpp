#include <iostream>
#include "Purse.h"
#include <map>
#include <string>

int main(int argc, char* argv[]) {
    int num_acc;
    std::map<std::string, Purse> vault;

    std::cout << "How many accounts to make?" << std::endl;
    std::cin >> num_acc;

    for (int i = 0; i < num_acc; i++) {
        std::string name;
        std::string temp;
        int pounds;
        int shillings;
        int pence;
        std::cout << "Enter account name: " << std::endl;
        std::getline(std::cin, temp); //clear cin
        std::getline(std::cin, name);
        std::cout << "Enter initial deposit: " << std::endl;
        Purse wallet;
        std::cin >> wallet;
        vault[name] = wallet;
    }

    Purse total;
    
    std::cout <<"Accounts: "<<std::endl;

    for(const auto& [name, purse] : vault) {
        std::cout << name << ":" << purse << std::endl;
        total += purse;
    }
    std::cout << "Total in bank is: " << total << std::endl;

    return 0;
}