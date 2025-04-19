#include "PmergeMe.hpp"
#include <sys/time.h>
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


  	struct timeval start, end;
	gettimeofday(&start, NULL); // 計測開始
	vecSort.sort(pArgs);
	gettimeofday(&end, NULL);   // 計測終了
	
	std::cout << "After: ";
	vecSort.printContainerElements();
	
	// 経過時間をマイクロ秒（us）単位でdoubleとして取得
	double elapsed_us = (end.tv_sec - start.tv_sec) * 1e6 
	                  + (end.tv_usec - start.tv_usec);
	
	// 小数付きのマイクロ秒として表示（例: 0.00031 us）
	std::cout << std::fixed << std::setprecision(5)
	          << "Time to process a range of " << args.size()
	          << " elements with std::[..] : " << elapsed_us << " us" << std::endl;
    //std::cout << "=====================================================" << std::endl;

    elapsed_us = 0;
    PmergeMe<std::list<int *> > lstSort(args.size());
	gettimeofday(&start, NULL); // 計測開始
    lstSort.sort(pArgs);
	gettimeofday(&end, NULL); // 計測開始
	
	elapsed_us = (end.tv_sec - start.tv_sec) * 1e6 
	                  + (end.tv_usec - start.tv_usec);
	std::cout << std::fixed << std::setprecision(5)
	          << "Time to process a range of " << args.size()
	          << " elements with std::[..] : " << elapsed_us << " us" << std::endl;
}
