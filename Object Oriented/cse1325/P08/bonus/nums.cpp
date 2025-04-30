#include <iostream>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
    std::vector<std::string> numbers;
    std::vector<std::string>* words = new std::vector<std::string>;

    for(int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if(isdigit(arg[0])) {
            numbers.push_back(arg);
        }
        else {
            words->push_back(arg);
        }
    }

    std::cout << "Numbers: " << std::endl;
    
    for(auto a : numbers) {
        std::cout << a << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Words: " << std::endl;
    for(auto b : *words) {
        std::cout << b << std::endl;
    }
}