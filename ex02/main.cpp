#include "PmergeMe.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>  // atoi, strtol
#include <climits>  // INT_MAX
#include <cstring>  // strcmp
#include <sys/time.h>  // gettimeofday
#include <algorithm>  // std::sort

template <typename Container, typename Node>
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

template <typename Node>
struct NodeComparator {
    bool operator()(Node *a, Node *b) const {
        return a->getNumber() < b->getNumber();
    }
};

Node_l * access_list(std::list<Node_l *> &l, int i) {
    std::list<Node_l *>::iterator it = l.begin();
    std::advance(it, i);
    return *it;
}

void print_debug(std::vector<Node_v *> v, std::list<Node_l *> l, std::vector<Node_v *> &res_vector, std::list<Node_l *> &res_list) {


    std::sort(v.begin(), v.end(), NodeComparator<Node_v>());
    std::sort(l.begin(), l.end(), NodeComparator<Node_l>());

    if (v == res_vector) {
        std::cout << GREEN << "OK: vector" << END << std::endl;
    } else {
        std::cout << RED << "Error: vector" << END << std::endl;
    }
    if (l == res_list) {
        std::cout << GREEN << "OK: deque" << END << std::endl;
    } else {
        std::cout << RED << "Error: deque" << END << std::endl;
    }

    std::cout << BLUE << "Count of the comparison(vector): " << count_vector << END << std::endl;
    std::cout << BLUE << "Count of the comparison(deque): " << count_list << END << std::endl;
}

size_t count_vector = 0;
size_t count_list = 0;

int main(int argc, char **argv) {
    std::vector<Node_v *> v;
    std::list<Node_l *> l;

    if (create_node<std::vector<Node_v *>, Node_v>(v, argc, argv) == 1 || create_node<std::list<Node_l *>, Node_l>(l, argc, argv) == 1) {
        std::cout << "Error" << std::endl;
        for (size_t j = 0; j < v.size(); j++) delete v[j];
        for (size_t j = 0; j < l.size(); j++) delete access_list(l, j);
        return 1;


    std::vector<Node_v *> res_vector;
    std::list<Node_l *> res_list;

    struct timeval start_v, end_v;
    struct timeval start_l, end_l;

    gettimeofday(&start_v, NULL);
    merge_insersion_sort_vector(v, res_vector);
    gettimeofday(&end_v, NULL);

    gettimeofday(&start_l, NULL);
    merge_insersion_sort_list(l, res_list);
    gettimeofday(&end_l, NULL);

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

    print_debug(v, l, res_vector, res_list);

    // time
    std::cout << "Time to process a range of " << (argc - 1) << " elements with std::vector : " << elapsed_time(start_v, end_v) << " us" << std::endl;
    std::cout << "Time to process a range of " << (argc - 1) << " elements with std::deque : " << elapsed_time(start_l, end_l) << " us" << std::endl;


    // free memory
    for (size_t j = 0; j < v.size(); j++) delete v[j];
    for (size_t j = 0; j < l.size(); j++) delete access_list(l, j);
}

// // memory leak確認
// __attribute__((destructor)) void destructor() {
//     system("leaks -q PmergeMe");
// }
