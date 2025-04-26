#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <vector>
#include <utility>

#define FAILURE 1
#define ASCII_TO_DIGIT 48
extern int g_compare_cnt;
typedef std::vector<int> intVec;
typedef std::vector<int *> intpVec;
typedef std::list<int *> intpLst;
typedef std::vector<std::pair<int *, int *> > pairVec;
typedef std::pair<int, int> intPair;

class PmergeMeVector {
    private:
        PmergeMeVector();
    public:
        PmergeMeVector(size_t argLen);
        ~PmergeMeVector();
        PmergeMeVector(const PmergeMeVector& other);
        PmergeMeVector& operator=(const PmergeMeVector& other);
    private:
        void pairSwap(std::pair<int, int> *pair);
        void copySortLargeToContainer(intpVec &large);
        intpVec::iterator getIdxByBinarySearch(int *largeValueInInsertPair, size_t jacob, int *smallValueInInsertPair);
        size_t getInsertArea(int *largeValueInInsertPair);
        int searchPairCorrespondingToContainer(const int *largeValue, const pairVec &pairs);
        void insert();
    public:
        void sort(intpVec vec);
        void printContainerElements();
    private:
        intpVec container;
    public:
        class InvalidArgument: public std::invalid_argument {
            public:
                InvalidArgument(const std::string message);
        };
    const static int nil = -1;
};

class PmergeMeList {
    private:
        PmergeMeList();
    public:
        PmergeMeList(size_t argLen);
        ~PmergeMeList();
        PmergeMeList(const PmergeMeList& other);
        PmergeMeList& operator=(const PmergeMeList& other);
    private:
        void pairSwap(std::pair<int, int> *pair);
        void copySortLargeToContainer(intpVec &large);
        intpLst::iterator getIdxByBinarySearch(int *largeValueInInsertPair, size_t jacob, int *smallValueInInsertPair);
        size_t getInsertArea(int *largeValueInInsertPair);
        int searchPairCorrespondingToContainer(const int *largeValue, const pairVec &pairs);
        void insert();
    public:
        void sort(intpVec vec);
        void printContainerElements();
    private:
        intpLst container;
    public:
        class InvalidArgument: public std::invalid_argument {
            public:
                InvalidArgument(const std::string message);
        };
    const static int nil = -1;
};

bool argCheck(int argc, char **argv, intVec &args);
void createPair(pairVec &pairs, intpVec &large, intpVec refVec);
bool sortCheck(intpVec& vec);

#endif
