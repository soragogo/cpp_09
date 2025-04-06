#include "PmergeMe.hpp"
std::vector<int> calculate_jacobsthal_sequence(int n) {
    std::vector<int> sequence(n + 1);
    sequence[0] = 0;
    if (n > 0) sequence[1] = 1;

    for (int i = 2; i <= n; ++i) {
        sequence[i] = sequence[i - 1] + 2 * sequence[i - 2];
    }

    return sequence;
}

std::vector<int> generate_indices(int count) {
    std::vector<int> indices(count);

    int jacobsthal_count = 20;
    std::vector<int> jacobsthal_seq = calculate_jacobsthal_sequence(jacobsthal_count);

    int index = 0;
    for (int i = 0; i < jacobsthal_count && index < count; ++i) {
        for (int j = jacobsthal_seq[i + 1]; j > jacobsthal_seq[i] && index < count; --j) {
            indices[index++] = j;
        }
    }
    return indices;
}

void merge_insersion_sort_vector(std::vector<Node_v*> v, std::vector<Node_v*> &res){

    if (v.size() < 2) {
        res.push_back(v[0]);
        return;
    }

    if (v.size() == 2) {
        // count
        count_vector++;
        if (v[0]->getNumber() > v[1]->getNumber()) {
            res.push_back(v[1]);
            res.push_back(v[0]);
        } else {
            res.push_back(v[0]);
            res.push_back(v[1]);
        }
        v[0]->sorted();
        v[1]->sorted();
        return;
    }

    std::vector < Node_v * >large;
    std::vector < Node_v * >small;
    for (std::vector<Node_v*>::iterator it = v.begin(); it != v.end() - 1; ++it) {
        if (std::distance(it, v.begin()) % 2 == 0) {
            std::vector<Node_v *>::iterator l_it;
            std::vector<Node_v *>::iterator s_it;
            // count
            count_vector++;
            if ((*it)->getNumber() > (*(it + 1))->getNumber()) {
                l_it = it;
                s_it = it + 1;
            } else {
                l_it = it + 1;
                s_it = it;
            }
            (*l_it)->setSmallerPair(*s_it);
            (*s_it)->setLargerPair(*l_it);
            large.push_back(*l_it);
        }
    }
    Node_v * leaf = NULL;
    if (v.size() % 2 == 1)
        leaf = v.back();

    merge_insersion_sort_vector(large, res);
    for (std::vector<Node_v *>::iterator it = res.begin(); it != res.end(); ++it) {
        if ((*it)->getSmallerPair() != NULL) {
            small.push_back((*it)->getSmallerPair());
            (*it)->eraseSmallerPair();
        }
    }
    if (leaf != NULL) small.push_back(leaf);


    std::vector<int> indices = generate_indices(small.size());
    int small_end = small.size() - 1;
    for (size_t i = 0; i < small.size(); ++i) {

        if (i == 0) {
            small[0]->sorted();
            res.insert(res.begin(), small[0]);
            continue;
        }

        int geta = (indices[i] - 1) > small_end ? small_end-- : indices[i] - 1;
        std::vector<Node_v*>::iterator it = (small.begin() + geta);
        Node_v* smaller_pair = *it;
        Node_v* larger_pair = smaller_pair->getLargerPair();

        std::vector<Node_v*>::iterator res_pos;
        for (res_pos = res.begin(); res_pos != res.end(); ++res_pos) {
            if (*res_pos == larger_pair) break;
        }

        std::vector<Node_v*>::iterator begin = res.begin();
        std::vector<Node_v*>::iterator end = res_pos - 1;
        std::vector<Node_v*>::iterator mid;
        while (begin <= end) {
            mid = begin + (end - begin) / 2;
            // count
            count_vector++;
            if ((*mid)->getNumber() > smaller_pair->getNumber()) {
                end = mid - 1;
            } else {
                begin = mid + 1;
            }
        }

        smaller_pair->sorted();
        res.insert(begin, smaller_pair);
    }
}


void merge_insersion_sort_list(std::list<Node_l*> l, std::list<Node_l*> &res){

    if (l.size() < 2) {
        res.push_back(l[0]);
        return;
    }

    if (l.size() == 2) {
        // count
        count_list++;
        if (l[0]->getNumber() > l[1]->getNumber()) {
            res.push_back(l[1]);
            res.push_back(l[0]);
        } else {
            res.push_back(l[0]);
            res.push_back(l[1]);
        }
        l[0]->sorted();
        l[1]->sorted();
        return;
    }

    std::list < Node_l * >large;
    std::list < Node_l * >small;
    for (std::list<Node_l*>::iterator it = l.begin(); it != l.end() - 1; ++it) {
        if (std::distance(it, l.begin()) % 2 == 0) {
            std::list<Node_l *>::iterator l_it;
            std::list<Node_l *>::iterator s_it;
            // count
            count_list++;
            if ((*it)->getNumber() > (*(it + 1))->getNumber()) {
                l_it = it;
                s_it = it + 1;
            } else {
                l_it = it + 1;
                s_it = it;
            }
            (*l_it)->setSmallerPair(*s_it);
            (*s_it)->setLargerPair(*l_it);
            large.push_back(*l_it);
        }
    }
    Node_l * leaf = NULL;
    if (l.size() % 2 == 1)
        leaf = l.back();

    merge_insersion_sort_list(large, res);
    for (std::list<Node_l *>::iterator it = res.begin(); it != res.end(); ++it) {
        if ((*it)->getSmallerPair() != NULL) {
            small.push_back((*it)->getSmallerPair());
            (*it)->eraseSmallerPair();
        }
    }
    if (leaf != NULL) small.push_back(leaf);


    std::vector<int> indices = generate_indices(small.size());
    int small_end = small.size() - 1;
    for (size_t i = 0; i < small.size(); ++i) {

        if (i == 0) {
            small[0]->sorted();
            res.insert(res.begin(), small[0]);
            continue;
        }

        int geta = (indices[i] - 1) > small_end ? small_end-- : indices[i] - 1;
        std::list<Node_l*>::iterator it = (small.begin() + geta);
        Node_l* smaller_pair = *it;
        Node_l* larger_pair = smaller_pair->getLargerPair();

        std::list<Node_l*>::iterator res_pos;
        for (res_pos = res.begin(); res_pos != res.end(); ++res_pos) {
            if (*res_pos == larger_pair) break;
        }

        std::list<Node_l*>::iterator begin = res.begin();
        std::list<Node_l*>::iterator end = res_pos - 1;
        std::list<Node_l*>::iterator mid;
        while (begin <= end) {
            mid = begin + (end - begin) / 2;
            // count
            count_list++;
            if ((*mid)->getNumber() > smaller_pair->getNumber()) {
                end = mid - 1;
            } else {
                begin = mid + 1;
            }
        }

        smaller_pair->sorted();
        res.insert(begin, smaller_pair);
    }
}


//Node_v

// Node class constructor and destructor
Node_v::Node_v(const int & i) : _number(i), _sorted(false) {}

Node_v::Node_v(void) : _number(-1), _sorted(false) {}

Node_v::~Node_v() {}

// Copy constructor and assignment operator
Node_v::Node_v(const Node_v & src) {
    *this = src;
}

Node_v & Node_v::operator=(const Node_v & rhs) {
    if (this != &rhs) {
        this->_number = rhs._number;
        this->_sorted = rhs._sorted;
        this->_larger_pair = rhs._larger_pair;
        this->_smaller_pair = rhs._smaller_pair;
    }
    return *this;
}

//Node_l

Node_l::Node_l(const int & i) : _number(i), _sorted(false) {}

Node_l::Node_l(void) : _number(-1), _sorted(false) {}

Node_l::~Node_l() {}

// Copy constructor and assignment operator
Node_l::Node_l(const Node_l & src) {
    *this = src;
}

Node_l & Node_l::operator=(const Node_l & rhs) {
    if (this != &rhs) {
        this->_number = rhs._number;
        this->_sorted = rhs._sorted;
        this->_larger_pair = rhs._larger_pair;
        this->_smaller_pair = rhs._smaller_pair;
    }
    return *this;
}
