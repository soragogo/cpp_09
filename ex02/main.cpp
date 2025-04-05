#include "PmergeMe.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>  // atoi, strtol
#include <climits>  // INT_MAX
#include <cstring>  // strcmp

int create_node(std::vector<Node *> &v, int argc, char **argv) {

    if (argc < 2) return 1;

    for (int i = 1; i < argc; i++){
        char *endptr;
        long num = std::strtol(argv[i], &endptr, 10);

        if (*endptr != '\0' || num <= 0 || num > INT_MAX) {
            for (size_t j = 0; j < v.size(); j++) delete v[j];
            return 1;
        }
        v.push_back(new Node(static_cast<int>(num)));
    }
    return 0;
}

int main(int argc, char **argv) {
    std::vector<Node *> v;

    if (create_node(v, argc, argv) == 1) {
        std::cout << "Error" << std::endl;
        return 1;
    }

    std::vector<Node *> res_vector;
    merge_insersion_sort(v, res_vector);

    // std::deque<Node *> res_deque;
    // merge_insersion_sort(v, res_deque);

    int i = 0; int j = -1;
    for (std::vector<Node *>::iterator it = res_vector.begin(); it != res_vector.end(); ++it) {
        i = (*it)->getNumber();
        std::cout << i << " ";
        if (i < j) {
            std::cout << RED << "KO" << END << std::endl;
            return 1;
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
}

