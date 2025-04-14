#include "PmergeMe.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>  // atoi, strtol
#include <climits>  // INT_MAX
#include <cstring>  // strcmp
#include <sys/time.h>  // gettimeofday
#include <algorithm>  // std::sort

template <typename Container>
int create_pmergeme(Container &c, int argc, char **argv) {

    if (argc < 2) return 1;

    for (int i = 1; i < argc; i++){
        char *endptr;
        long num = std::strtol(argv[i], &endptr, 10);

        if (*endptr != '\0' || num <= 0 || num > INT_MAX) {
            return 1;
        }
        c.push_back(new PmergeMe(static_cast<int>(num)));
    }
    return 0;
}

double elapsed_time(struct timeval start, struct timeval end) {
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed = seconds * 1000000.0 + microseconds;
    return elapsed;
}

struct PmergeMeComparator {
    bool operator()(PmergeMe *a, PmergeMe *b) const {
        return *a < *b;
    }
};

void print_debug(std::vector<PmergeMe *> v, std::list<PmergeMe *> l, std::vector<PmergeMe *> &res_vector, std::list<PmergeMe *> &res_list) {


    std::sort(v.begin(), v.end(), PmergeMeComparator());
    l.sort(PmergeMeComparator());

    int error = 0;
    for (size_t i = 0; i < v.size(); i++) {
        if (*v[i] != *res_vector[i]) {
            std::cerr << RED << "Error: vector" << END << std::endl;
            error = 1;
            break;
        }
    }

    for (size_t i = 0; i < l.size(); i++) {
        if (*access_list(l, i) != *access_list(res_list, i)) {
            std::cerr << RED << "Error: list" << END << std::endl;
            error = 1;
            break;
        }
    }
    if (!error) std::cout << GREEN << "Sort success" << END << std::endl;

    std::cout << BLUE << "Count of the comparison(vector): " << count_vector << END << std::endl;
    std::cout << BLUE << "Count of the comparison(list): " << count_list << END << std::endl;
}

size_t count_vector = 0;
size_t count_list = 0;

int main(int argc, char **argv) {
    std::vector<PmergeMe *> v;
    std::list<PmergeMe *> l;

    if (create_pmergeme(v, argc, argv) == 1 || create_pmergeme(l, argc, argv) == 1) {
        std::cerr << "Error" << std::endl;
        for (size_t j = 0; j < v.size(); j++) delete v[j];
        for (size_t j = 0; j < l.size(); j++) delete access_list(l, j);
        return 1;
    }

    std::vector<PmergeMe *> res_vector;
    std::list<PmergeMe *> res_list;

    struct timeval start_v, end_v;
    struct timeval start_l, end_l;

    gettimeofday(&start_v, NULL);
    merge_insersion_sort_vector(v, res_vector);
    gettimeofday(&end_v, NULL);

    gettimeofday(&start_l, NULL);
    merge_insersion_sort_list(l, res_list);
    gettimeofday(&end_l, NULL);
    std::cout << std::endl;

    std::cout << "Before: ";
    for (int i = 1; i < argc; i++) {
        std::cout << argv[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "After: ";
    for (size_t i = 0; i < res_vector.size(); i++) {
        std::cout << *res_vector[i] << " ";
    }
    // std::cout << std::endl;
    // std::cout << "[list] After : ";
    // for (size_t i = 0; i < res_list.size(); i++) {
    //     std::cout << *access_list(res_list, i) << " ";
    // }
    std::cout << std::endl;

    print_debug(v, l, res_vector, res_list);

    // time
    std::cout << "Time to process a range of " << (argc - 1) << " elements with std::vector : " << elapsed_time(start_v, end_v) << " us" << std::endl;
    std::cout << "Time to process a range of " << (argc - 1) << " elements with std::list : " << elapsed_time(start_l, end_l) << " us" << std::endl;


    // free memory
    for (size_t j = 0; j < v.size(); j++) delete v[j];
    for (size_t j = 0; j < l.size(); j++) delete access_list(l, j);
}

// // memory leak確認
// __attribute__((destructor)) void destructor() {
//     system("leaks -q PmergeMe");
// }
