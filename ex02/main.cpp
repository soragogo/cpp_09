#include "PmergeMe.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>  // atoi, strtol
#include <climits>  // INT_MAX
#include <cstring>  // strcmp
#include <sys/time.h>  // gettimeofday
#include <algorithm>  // std::sort

template <typename Container>
int create_node(Container &c, int argc, char **argv) {

    if (argc < 2) return 1;

    for (int i = 1; i < argc; i++){
        char *endptr;
        long num = std::strtol(argv[i], &endptr, 10);

        if (*endptr != '\0' || num <= 0 || num > INT_MAX) {
            return 1;
        }
        c.push_back(new Node(static_cast<int>(num)));
    }
    return 0;
}

double elapsed_time(struct timeval start, struct timeval end) {
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed = seconds * 1000.0 + microseconds / 1000.0;
    return elapsed;
}

struct NodeComparator {
    bool operator()(Node *a, Node *b) const {
        return a->getNumber() < b->getNumber();
    }
};

void print_debug(std::vector<Node *> v, std::deque<Node *> d, std::vector<Node *> &res_vector, std::deque<Node *> &res_deque) {


    std::sort(v.begin(), v.end(), NodeComparator());
    std::sort(d.begin(), d.end(), NodeComparator());

    for (size_t i = 0; i < v.size(); i++) {
        if (v[i]->getNumber() != res_vector[i]->getNumber()) {
            std::cout << RED << "Error: vector" << END << std::endl;
            break;
        }
    }

    for (size_t i = 0; i < d.size(); i++) {
        if (d[i]->getNumber() != res_deque[i]->getNumber()) {
            std::cout << RED << "Error: deque" << END << std::endl;
            break;
        }
    }

    std::cout << BLUE << "Count of the comparison(vector): " << count_vector << END << std::endl;
    std::cout << BLUE << "Count of the comparison(deque): " << count_deque << END << std::endl;
}

size_t count_vector = 0;
size_t count_deque = 0;

int main(int argc, char **argv) {
    std::vector<Node *> v;
    std::deque<Node *> d;

    if (create_node(v, argc, argv) == 1 || create_node(d, argc, argv) == 1) {
        std::cout << "Error" << std::endl;
        for (size_t j = 0; j < v.size(); j++) delete v[j];
        for (size_t j = 0; j < d.size(); j++) delete d[j];
        return 1;
    }

    std::vector<Node *> res_vector;
    std::deque<Node *> res_deque;

    struct timeval start_v, end_v;
    struct timeval start_d, end_d;

    gettimeofday(&start_v, NULL);
    merge_insersion_sort_vector(v, res_vector);
    gettimeofday(&end_v, NULL);

    gettimeofday(&start_d, NULL);
    merge_insersion_sort_deque(d, res_deque);
    gettimeofday(&end_d, NULL);

    std::cout << "Before: ";
    for (int i = 1; i < argc; i++) {
        std::cout << argv[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "After: ";
    for (size_t i = 0; i < res_vector.size(); i++) {
        std::cout << res_vector[i]->getNumber() << " ";
    }
    std::cout << std::endl;

    print_debug(v, d, res_vector, res_deque);

    // time
    std::cout << "Time to process a range of " << (argc - 1) << " elements with std::vector : " << elapsed_time(start_v, end_v) << " us" << std::endl;
    std::cout << "Time to process a range of " << (argc - 1) << " elements with std::deque : " << elapsed_time(start_d, end_d) << " us" << std::endl;


    // free memory
    for (size_t j = 0; j < v.size(); j++) delete v[j];
    for (size_t j = 0; j < d.size(); j++) delete d[j];
}

// // memory leak確認
// __attribute__((destructor)) void destructor() {
//     system("leaks -q PmergeMe");
// }
