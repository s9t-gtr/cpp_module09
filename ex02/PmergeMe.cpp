#include "PmergeMe.hpp"
#include <climits>

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

// PmergeMeVector implementation
PmergeMeVector::PmergeMeVector(size_t argLen) {
    (void)argLen;
}

PmergeMeVector::~PmergeMeVector() {
}

PmergeMeVector::PmergeMeVector(const PmergeMeVector& other) {
    if(this != &other)
        return;
    *this = other;
}

PmergeMeVector& PmergeMeVector::operator=(const PmergeMeVector& other) {
    if(this != &other)
        return *this;
    container = other.container;
    return *this;
}

int PmergeMeVector::searchPairCorrespondingToContainer(const int *largeValue, const pairVec &pairs) {
    for(size_t i=0; i<pairs.size(); i++) {
        if(pairs[i].second == largeValue)
            return i;
    }
    return -1;
}

size_t PmergeMeVector::getInsertArea(int *largeValueInInsertPair) {
    for (size_t i = 0; i < container.size(); ++i) {
        if (container[i] == largeValueInInsertPair)
            return i;
    }
    return container.size();
}

intpVec::iterator PmergeMeVector::getIdxByBinarySearch(int *largeValueInInsertPair, size_t jacob, int *smallValueInInsertPair) {
    size_t lower = 0;
    size_t upper = getInsertArea(largeValueInInsertPair);

    if (jacob == 1)
        return container.begin();

    while (lower < upper) {
        size_t mid = lower + (upper - lower) / 2;

        if (*container[mid] < *smallValueInInsertPair)
            lower = mid + 1;
        else
            upper = mid;
        // g_compare_cnt++;
    }
    return container.begin() + upper;
}

void PmergeMeVector::sort(intpVec vec) {
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
    intpVec copyContainer = container;
    size_t len = pairs.size();
    if (surplas) len++;
    for (size_t xn = 1; xn <= len; xn++) {
        if (xn >= 2) {
            xn = xn1 + 2 * xn2;
            if (xn > len)
                xn = len;
        }
        for (size_t i = xn; i > xn1; i--) {
            int pairIdx = searchPairCorrespondingToContainer(copyContainer[i-1], pairs);

            if (pairIdx == -1) {
                intpVec::iterator insertIt = getIdxByBinarySearch(NULL, i, surplas);
                container.insert(insertIt, surplas);
            } else {
                intpVec::iterator insertIt = getIdxByBinarySearch(copyContainer[i-1], i, pairs[pairIdx].first);
                container.insert(insertIt, pairs[pairIdx].first);
            }
        }
        xn2 = xn1;
        xn1 = xn;
    }
}

void PmergeMeVector::printContainerElements() {
    for (size_t i = 0; i < container.size(); ++i) {
        std::cout << " " << *container[i];
    }
    std::cout << std::endl;
}

PmergeMeVector::InvalidArgument::InvalidArgument(const std::string message): std::invalid_argument(message) {}

// PmergeMeList implementation
PmergeMeList::PmergeMeList(size_t argLen) {
    (void)argLen;
}

PmergeMeList::~PmergeMeList() {
}

PmergeMeList::PmergeMeList(const PmergeMeList& other) {
    if(this != &other)
        return;
    *this = other;
}

PmergeMeList& PmergeMeList::operator=(const PmergeMeList& other) {
    if(this != &other)
        return *this;
    container = other.container;
    return *this;
}

int PmergeMeList::searchPairCorrespondingToContainer(const int *largeValue, const pairVec &pairs) {
    for(size_t i=0; i<pairs.size(); i++) {
        if(pairs[i].second == largeValue)
            return i;
    }
    return -1;
}

size_t PmergeMeList::getInsertArea(int *largeValueInInsertPair) {
    size_t i = 0;
    for (intpLst::iterator it = container.begin(); it != container.end(); ++it, ++i) {
        if (*it == largeValueInInsertPair)
            return i;
    }
    return container.size();
}

intpLst::iterator PmergeMeList::getIdxByBinarySearch(int *largeValueInInsertPair, size_t jacob, int *smallValueInInsertPair) {
    size_t lower = 0;
    size_t upper = getInsertArea(largeValueInInsertPair);

    if (jacob == 1)
        return container.begin();

    while (lower < upper) {
        size_t mid = lower + (upper - lower) / 2;
        intpLst::iterator midIt = container.begin();
        std::advance(midIt, mid);

        if (**midIt < *smallValueInInsertPair)
            lower = mid + 1;
        else
            upper = mid;
        // g_compare_cnt++;
    }
    intpLst::iterator result = container.begin();
    std::advance(result, upper);
    return result;
}

void PmergeMeList::sort(intpVec vec) {
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
    intpLst copyContainer = container;
    size_t len = pairs.size();
    if (surplas) len++;
    for (size_t xn = 1; xn <= len; xn++) {
        if (xn >= 2) {
            xn = xn1 + 2 * xn2;
            if (xn > len)
                xn = len;
        }
        for (size_t i = xn; i > xn1; i--) {
            intpLst::iterator it = copyContainer.begin();
            std::advance(it, i - 1);
            int pairIdx = searchPairCorrespondingToContainer(*it, pairs);

            if (pairIdx == -1) {
                intpLst::iterator insertIt = getIdxByBinarySearch(NULL, i, surplas);
                container.insert(insertIt, surplas);
            } else {
                intpLst::iterator insertIt = getIdxByBinarySearch(*it, i, pairs[pairIdx].first);
                container.insert(insertIt, pairs[pairIdx].first);
            }
        }
        xn2 = xn1;
        xn1 = xn;
    }
}

void PmergeMeList::printContainerElements() {
    for (intpLst::iterator it = container.begin(); it != container.end(); ++it) {
        std::cout << " " << **it;
    }
    std::cout << std::endl;
}

PmergeMeList::InvalidArgument::InvalidArgument(const std::string message): std::invalid_argument(message) {}

// Global functions
void createPair(pairVec &pairs, intpVec &large, intpVec refVec) {
    for(size_t i=1; i<refVec.size(); i+=2) {
        if(*(refVec[i-1]) < *(refVec[i])) {
            pairs[i/2].first = refVec[i-1];
            pairs[i/2].second = refVec[i];
        } else {
            pairs[i/2].first = refVec[i];
            pairs[i/2].second = refVec[i-1];
        }
        // g_compare_cnt++; 
        large[i/2] = pairs[i/2].second;
    }
}

bool sortCheck(intpVec& vec) {
    for(size_t i=1; i<vec.size(); i++) {
        if(*(vec[i-1]) > *(vec[i]))
            return false;
    }
    return true;
}
