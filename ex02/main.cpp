#include "PmergeMe.hpp"


int main() {
    std::vector<Node *> v;
    int tmp[] = {
        10, 9, 8, 7, 6
    };
    for (unsigned int n = 0; n < sizeof(tmp) / sizeof(int); n++) {
        v.push_back(new Node(tmp[n]));
    }
    // for (int n = 0; n < 10000; n++) {
    //     int l;
    //     std::cin >> l;
    //     v.push_back(new Node(l));
    // }
    std::cout << std::endl;
    std::vector<Node *> res;
    merge_insersion_sort(v, res);
    int i = 0; int j = -1;
    for (std::vector<Node *>::iterator it = res.begin(); it != res.end(); ++it) {
        i = (*it)->getNumber();
        std::cout << i << " ";
        if (i < j) {
            std::cout << RED << "KO" << END << std::endl;
            return 1;
        }
        j = i;
    }
    std::cout << GREEN << "OK" << END << std::endl;
    if ((sizeof(tmp) / sizeof(int)) == res.size()) {
        std::cout << GREEN << "AND SIZE OK" << END << std::endl;
    } else {
        std::cout << RED << "BUT SIZE KO" << END << std::endl;
    }
}

