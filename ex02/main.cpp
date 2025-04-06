#include "PmergeMe.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>  // atoi, strtol
#include <climits>  // INT_MAX
#include <cstring>  // strcmp
#include <sys/time.h>  // gettimeofday

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

void print_debug(std::vector<Node *> &res_vector, std::deque<Node *> &res_deque, int argc) {


    int i = 0; int j = -1;
    for (std::vector<Node *>::iterator it = res_vector.begin(); it != res_vector.end(); ++it) {
    i = (*it)->getNumber();
    std::cout << i << " ";
    if (i < j) {
        std::cout << RED << "KO" << END << std::endl;
        break;
    }
    j = i;
    }
    std::cout << std::endl;

    std::cout << GREEN << "OK" << END << std::endl;
    if ((unsigned long)(argc - 1) == res_vector.size()) {
        std::cout << GREEN << "AND SIZE OK" << END << std::endl;
    } else {
        std::cout << RED << "BUT SIZE KO" << END << std::endl;
    }


    //deque
    i = 0; j = -1;
    for (std::deque<Node *>::iterator it = res_deque.begin(); it != res_deque.end(); ++it) {
        i = (*it)->getNumber();
        std::cout << i << " ";
        if (i < j) {
            std::cout << RED << "KO" << END << std::endl;
            break;
        }
        j = i;

    // count
}

std::cout << std::endl;
std::cout << GREEN << "OK" << END << std::endl;
if ((unsigned long)(argc - 1) == res_deque.size()) {
    std::cout << GREEN << "AND SIZE OK" << END << std::endl;
} else {
    std::cout << RED << "BUT SIZE KO" << END << std::endl;
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
    for (int i = 1; i < (argc > 6 ? 5 : argc); i++) {
        std::cout << argv[i] << " ";
    }
    if (argc > 6) {
        std::cout << "[...]";
    }
    std::cout << std::endl;
    std::cout << "After: ";
    for (int i = 0; i < (argc > 6 ? 5 : argc - 1); i++) {
        std::cout << res_vector[i]->getNumber() << " ";
    }
    if (argc > 6) {
        std::cout << "[...]";
    }
    std::cout << std::endl;

    // print_debug(res_vector, res_deque, argc);

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
