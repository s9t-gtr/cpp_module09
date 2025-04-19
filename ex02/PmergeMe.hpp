#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include "Node.hpp"
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <vector>
#include <utility>

#define FAILURE 1
#define ASCII_TO_DIGIT 48

typedef std::vector<int> intVec;
typedef std::vector<int *> intpVec;
typedef std::list<int *> intpLst;
typedef std::vector<std::pair<int *, int *> > pairVec;
typedef std::pair<int, int> intPair;

template <typename Container>
class PmergeMe{
    private:
        PmergeMe();
    public:
        PmergeMe(size_t argLen);
        ~PmergeMe();
        PmergeMe(const PmergeMe<Container>& other);
        PmergeMe<Container>& operator=(const PmergeMe<Container>& other);
    private:
        // void createPair(intVec::iterator it, intVec::iterator argsEnd, size_t pairsVecIdx);
        void pairSwap(std::pair<int, int> *pair);
        void copySortLargeToContainer(intpVec &large);
        typename Container::iterator getIdxByBinarySearch(int *largeValueInInsertPair, size_t jacob, int *smallValueInInsertPair);
        size_t getInsertArea(int *largeValueInInsertPair);
        size_t searchPairCorrespondingToContainer(const int *largeValue, const pairVec &pairs);
        void insert();
    public:
        void sort(intpVec vec);
        void printContainerElements();
    private:
        Container container;
    public:
        class InvalidArgument: public std::invalid_argument{
            public:
                InvalidArgument(const std::string message);
        };
    const static int nil = -1;
};

bool argCheck(int argc, char **argv, intVec &args);

template <typename Container>
PmergeMe<Container>::PmergeMe(size_t argLen){
    // container.reserve(argLen);
    (void)argLen;
}

template <typename Container>
PmergeMe<Container>::~PmergeMe(){
}

template <typename Container>
PmergeMe<Container>::PmergeMe(const PmergeMe<Container>& other){
    if(this != &other)
        return;
    *this = other;
}

template <typename Container>
PmergeMe<Container>& PmergeMe<Container>::operator=(const PmergeMe<Container>& other){
    if(this != &other)
        return *this;
    container = other.container;
}


template <typename Container>
size_t PmergeMe<Container>::searchPairCorrespondingToContainer(const int *largeValue,  const pairVec &pairs){
    for(size_t i=0;i<pairs.size();i++){
        if(pairs[i].second == largeValue)
            return i;
    }
    std::cout << "bug: not found largeValue in pairs: largeValue = " << *largeValue << "pointer" << std::endl;
    return 0;
}

template <typename Container>
size_t PmergeMe<Container>::getInsertArea(int *largeValueInInsertPair) {
    typename Container::iterator it = container.begin();
    for (size_t i = 0; i < container.size(); ++i, ++it) {
        if (*it == largeValueInInsertPair)
            return i;
    }
    return container.size(); // surplus のとき
}

template <typename Container>
typename Container::iterator PmergeMe<Container>::getIdxByBinarySearch(int *largeValueInInsertPair, size_t jacob, int *smallValueInInsertPair) {
    size_t lower = 0;
    size_t upper = getInsertArea(largeValueInInsertPair);

    if (jacob == 1)
        return container.begin();

    while (lower < upper) {
        size_t mid = lower + (upper - lower) / 2;

        // mid番目のイテレータを取得
        typename Container::iterator midIt = container.begin();
        for (size_t i = 0; i < mid; ++i)
            ++midIt;

        if (**midIt < *smallValueInInsertPair)
            lower = mid + 1;
        else
            upper = mid;
    }

    // upper番目のイテレータを取得
    typename Container::iterator result = container.begin();
    for (size_t i = 0; i < upper; ++i)
        ++result;

    return result;
}

void createPair(pairVec &pairs, intpVec &large, intpVec refVec);
bool sortCheck(intpVec& vec);


template <typename Container>
void PmergeMe<Container>::sort(intpVec vec) {
    pairVec pairs(vec.size() / 2);
    intpVec large(vec.size() / 2);
    int* surplas = vec.size() % 2 == 1 ? vec[vec.size() - 1] : NULL;
    createPair(pairs, large, vec);

    if (!sortCheck(large))
        sort(large);
    else
        container.assign(large.begin(), large.end());

    size_t xn1 = 0;
    size_t xn2 = 0;
    Container copyContainer = container;

    for (size_t xn = 1; xn <= pairs.size(); xn++) {
        if (xn >= 2) {
            xn = xn1 + 2 * xn2;
            if (xn > pairs.size())
                xn = pairs.size();
        }

        for (size_t i = xn; i > xn1; i--) {
            // i-1番目の要素に対応するイテレータを取得
            typename Container::iterator it = copyContainer.begin();
            for (size_t j = 0; j < i - 1; ++j)
                ++it;

            size_t pairIdx = searchPairCorrespondingToContainer(*it, pairs);

            typename Container::iterator insertTarget = copyContainer.begin();
            for (size_t j = 0; j < i - 1; ++j)
                ++insertTarget;

            typename Container::iterator insertIt = getIdxByBinarySearch(*insertTarget, i, pairs[pairIdx].first);
            container.insert(insertIt, pairs[pairIdx].first);
        }

        xn2 = xn1;
        xn1 = xn;
    }

    if (surplas) {
        typename Container::iterator insertIt = getIdxByBinarySearch(0, 0, surplas);
        container.insert(insertIt, surplas);
    }
}

// template <typename Container>
// void PmergeMe<Container>::insert(){
//     size_t xn1 = 0; //xn-1
//     size_t xn2 = 0; //xn-2
//     for(size_t xn=0;xn < pairs.size();xn++){
//         if(xn >= 2){
//             xn = xn1 + 2*xn2;
//             if(xn > pairs.size()-1)
//                 xn = pairs.size()-1;
//         }
//         // if()
//         xn2 = xn1;
//         xn1 = xn;
//     }
// }

template <typename Container>
void PmergeMe<Container>::printContainerElements() {
    typename Container::iterator it = container.begin();
    for (size_t i = 0; i < container.size(); ++i, ++it) {
        std::cout << " " << **it;
    }
    std::cout << std::endl;
}

template <typename Container>
PmergeMe<Container>::InvalidArgument::InvalidArgument(const std::string message): std::invalid_argument(message){}

#endif
