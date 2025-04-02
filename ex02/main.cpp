#include "PmergeMe.hpp"


int main() {
    std::vector<Node *> v;
    int tmp[] = {
        3, 86, 70, 31, 91, 44, 30, 51, 52, 10,
        100, 63, 10, 22, 59, 94, 42, 9, 58, 46,
        20, 5, 60, 57, 31, 9, 2, 31, 50, 100,
        99, 98, 97, 96, 95, 94, 93, 92, 91, 90,
        89, 88, 87, 86, 85, 84, 83, 82, 81, 80,
        2000, 1932, 1923, 1924, 1925, 1926, 1927, 1928, 1929, 1930,
        1931, 1932, 1933, 1934, 1935, 1936, 1937, 1938, 1939, 1940,
        1941, 1942, 1943, 1944, 1945, 1946, 1947, 1948, 1949, 1950
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
}

