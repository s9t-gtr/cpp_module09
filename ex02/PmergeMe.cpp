#include "PmergeMe.hpp"

bool argCheck(int argc, char **argv, intVec &args){
    for(int i=1;i<argc;i++){
        long long num = 0;
        size_t digit = 0;
        char *arg = argv[i];
        while(arg[digit])
            digit++;
        if(digit == 0)
            return false;
        for(size_t j=0;j<digit;j++){
            if(!std::isdigit(arg[j]))
                return false;
            num *= 10;
            num += arg[j] - ASCII_TO_DIGIT;
            if(num > INT_MAX){
                std::cout << num << std::endl;
                return false;
            }
        }
        args.push_back(static_cast<int>(num));
    }
    return true;
}