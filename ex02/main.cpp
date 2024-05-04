#include "PmergeMe.hpp"
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
    // std::cout << "size = " << args.size() << std::endl;
    // for(intVec::iterator it=args.begin();it!=args.end();it++){
    //     std::cout << *it << " " ;
    // }
    PmergeMe<std::vector<int *> > vecSort(args.size());
    intpVec pArgs(args.size());
    for(size_t i=0;i<args.size();i++){
        pArgs[i] = &args[i];
    }
    vecSort.sort(pArgs);
    // FordJhonson<std::list<int> > lstSort;
    // lstSort.sort(args);
}