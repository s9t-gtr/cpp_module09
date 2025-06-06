#include "PmergeMe.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>

// int g_compare_cnt = 0;

void printTime(clock_t start, clock_t end, const std::string& container_type, size_t element_count) {
    double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
    std::cout << "Time to process a range of " << element_count << " elements with std::" << container_type << " : " << std::fixed << time << " us" << std::endl;
}

// void printComparisonCount(const std::string& container_type) {
//     std::cout << "Number of comparisons: " << g_compare_cnt << " with " << container_type << std::endl;
// }

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Error: No arguments provided" << std::endl;
        return 1;
    }

    intVec args;
    if (!argCheck(argc, argv, args)) {
        std::cerr << "Error: Invalid arguments" << std::endl;
        return 1;
    }

    // Convert args to intpVec
    intpVec vec;
    for (size_t i = 0; i < args.size(); ++i) {
        vec.push_back(new int(args[i]));
    }
    if(sortCheck(vec)){
        for (size_t i = 0; i < vec.size(); ++i) delete vec[i];
        std::cout << "sorted" << std::endl;
        return 0;
    }
    std::cout << "Before:";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << " " << *vec[i];
    }
    std::cout << std::endl;

    // Test with vector
    {
        // g_compare_cnt = 0;
        PmergeMeVector pmergeVec(args.size());
        clock_t start = clock();
        pmergeVec.sort(vec);
        clock_t end = clock();
        std::cout << "After:";
        pmergeVec.printContainerElements();
        printTime(start, end, "vector", vec.size());
        // printComparisonCount("std::vector");
    }

    // Test with list
    {
        // g_compare_cnt = 0;
        PmergeMeList pmergeList(args.size());
        clock_t start = clock();
        pmergeList.sort(vec);
        clock_t end = clock();
        // std::cout << "After:";
        // pmergeList.printContainerElements();
        printTime(start, end, "list", vec.size());
        // printComparisonCount("std::list");
    }

    // Clean up
    for (size_t i = 0; i < vec.size(); ++i) delete vec[i];
    return 0;
}
