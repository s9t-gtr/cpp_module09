#include "PmergeMe.hpp"
#include <iomanip>
void createPair(pairVec &pairs, intpVec &large, intpVec refVec){
    for(size_t i=1;i<refVec.size();i+=2){
        if(*(refVec[i-1]) < *(refVec[i])){
            pairs[i/2].first = refVec[i-1];
            pairs[i/2].second = refVec[i];
        }else{
            pairs[i/2].first = refVec[i];
            pairs[i/2].second = refVec[i-1];
        }
        large[i/2] = pairs[i/2].second;
    }
}

bool sortCheck(intpVec& vec){
    for(size_t i=1;i<vec.size();i++){
        if(*(vec[i-1]) > *(vec[i]))
            return false;
    }
    return true;
}
int main(int argc, char **argv){
    std::chrono::system_clock::time_point  start, end; // 型は auto で可
    intVec args;
    if(argc < 3 || !argCheck(argc, argv, args)){
        std::cerr << "Error: invalid arguments" << std::endl;
        return FAILURE;
    }

    std::cout << "Before: ";
    for(size_t i=0;i<args.size();i++){
        std::cout << args[i] << " ";
    }
    std::cout << std::endl;

    PmergeMe<std::vector<int *> > vecSort(args.size());
    intpVec pArgs(args.size());
    for(size_t i=0;i<args.size();i++){
        pArgs[i] = &args[i];
    }

   

    start = std::chrono::system_clock::now(); // 計測開始時間
    vecSort.sort(pArgs);
    end = std::chrono::system_clock::now();  // 計測終了時間

    std::cout << "After: ";
    vecSort.printContainerElements();

    double elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    std::cout << std::fixed << std::setprecision(5) <<"Time to process a range of " << args.size() <<" elements with std::[..] : " <<  elapsed / 1000 / 1000 /100 << " us" << std::endl;
    //std::cout << "=====================================================" << std::endl;

    elapsed = 0;
    PmergeMe<std::list<int *> > lstSort(args.size());
    start = std::chrono::system_clock::now(); // 計測開始時間
    lstSort.sort(pArgs);
    end = std::chrono::system_clock::now();  // 計測終了時間
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
    std::cout << std::fixed << std::setprecision(5) <<"Time to process a range of " << args.size() <<" elements with std::[..] : " << elapsed / 1000 / 1000 / 100 << " us" << std::endl;
}