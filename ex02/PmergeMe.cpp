#include "PmergeMe.hpp"

// Node class constructor and destructor
Node::Node(const int & i) : _number(i), _sorted(false) {}

Node::Node(void) : _number(-1), _sorted(false) {}

Node::~Node() {}

// Copy constructor and assignment operator
Node::Node(const Node & src) {
    *this = src;
}

Node & Node::operator=(const Node & rhs) {
    if (this != &rhs) {
        this->_number = rhs._number;
        this->_sorted = rhs._sorted;
        this->_larger_pair = rhs._larger_pair;
        this->_smaller_pair_v = rhs._smaller_pair_v;
        this->_smaller_pair_l = rhs._smaller_pair_l;
    }
    return *this;
}


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

void merge_insersion_sort_vector(std::vector<Node*> v, std::vector<Node*> &res){

    if (v.size() < 2) {
        res.push_back(v[0]);
        return;
    }

    if (v.size() == 2) {
        // count
        count_vector++;
        if (*v[0] > *v[1]) {
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

    std::vector < Node * >large;
    std::vector < Node * >small;
    for (std::vector<Node*>::iterator it = v.begin(); it != v.end() - 1; ++it) {
        if (std::distance(it, v.begin()) % 2 == 0) {
            std::vector<Node *>::iterator l_it;
            std::vector<Node *>::iterator s_it;
            // count
            count_vector++;
            if (*(*it) > (*(*(it + 1)))) {
                l_it = it;
                s_it = it + 1;
            } else {
                l_it = it + 1;
                s_it = it;
            }
            (*l_it)->setSmallerPairV(*s_it);
            (*s_it)->setLargerPair(*l_it);
            large.push_back(*l_it);
        }
    }
    Node * leaf = NULL;
    if (v.size() % 2 == 1)
        leaf = v.back();

    merge_insersion_sort_vector(large, res);
    for (std::vector<Node *>::iterator it = res.begin(); it != res.end(); ++it) {
        if ((*it)->getSmallerPairV() != NULL) {
            small.push_back((*it)->getSmallerPairV());
            (*it)->eraseSmallerPairV();
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
        std::vector<Node*>::iterator it = (small.begin() + geta);
        Node* smaller_pair = *it;
        Node* larger_pair = smaller_pair->getLargerPair();

        std::vector<Node*>::iterator res_pos;
        for (res_pos = res.begin(); res_pos != res.end(); ++res_pos) {
            if (*res_pos == larger_pair) break;
        }

        std::vector<Node*>::iterator begin = res.begin();
        std::vector<Node*>::iterator end = res_pos - 1;
        std::vector<Node*>::iterator mid;
        while (begin <= end) {
            mid = begin + (end - begin) / 2;
            // count
            count_vector++;
            if (*(*mid) > *smaller_pair) {
                end = mid - 1;
            } else {
                begin = mid + 1;
            }
        }

        smaller_pair->sorted();
        res.insert(begin, smaller_pair);
    }
}


void merge_insersion_sort_list(std::list<Node*> l, std::list<Node*> &res){

    if (l.size() < 2) {
        res.push_back(access_list(l, 0));
        return;
    }

    if (l.size() == 2) {
        // count
        count_list++;
        if (*access_list(l, 0) > *access_list(l, 1)) {
            res.push_back(access_list(l, 1));
            res.push_back(access_list(l, 0));
        } else {
            res.push_back(access_list(l, 0));
            res.push_back(access_list(l, 1));
        }
        access_list(l, 0)->sorted();
        access_list(l, 1)->sorted();
        return;
    }

    std::list < Node * >large;
    std::list < Node * >small;
    for (std::list<Node*>::iterator it = l.begin(); it != l.end(); ++it) {
        if (std::distance(l.begin(), it) % 2 == 0) {
            std::list<Node *>::iterator l_it;
            std::list<Node *>::iterator s_it;

            std::list<Node *>::iterator next_it = it;
            std::advance(next_it, 1);
            if (next_it == l.end()) break;
            // count
            count_list++;
            if (*(*it) > (*(*next_it))) {
                l_it = it;
                s_it = next_it;
            } else {
                l_it = next_it;
                s_it = it;
            }
            (*l_it)->setSmallerPairL(*s_it);
            (*s_it)->setLargerPair(*l_it);
            large.push_back(*l_it);
        }
    }
    Node * leaf = NULL;
    if (l.size() % 2 == 1)
        leaf = l.back();

    merge_insersion_sort_list(large, res);
    for (std::list<Node *>::iterator it = res.begin(); it != res.end(); ++it) {
        if ((*it)->getSmallerPairL() != NULL) {
            small.push_back((*it)->getSmallerPairL());
            (*it)->eraseSmallerPairL();
        }
    }
    if (leaf != NULL) small.push_back(leaf);


    std::vector<int> indices = generate_indices(small.size());
    int small_end = small.size() - 1;
    for (size_t i = 0; i < small.size(); ++i) {

        if (i == 0) {
            access_list(small, 0)->sorted();
            res.insert(res.begin(), access_list(small, 0));
            continue;
        }

        int geta = (indices[i] - 1) > small_end ? small_end-- : indices[i] - 1;
        std::list<Node*>::iterator it = small.begin();
        std::advance(it, geta);
        Node* smaller_pair = *it;
        Node* larger_pair = smaller_pair->getLargerPair();

        std::list<Node*>::iterator res_pos;
        for (res_pos = res.begin(); res_pos != res.end(); ++res_pos) {
            if (*res_pos == larger_pair) break;
        }

        std::list<Node*>::iterator begin = res.begin();
        std::list<Node*>::iterator end = res_pos;
        --end;
        
        std::list<Node*>::iterator mid;

        while (std::distance(res.begin(), begin) <= std::distance(res.begin(), end)) {
            int distance = std::distance(begin, end);
            mid = begin;
            std::advance(mid, distance / 2);
            // count
            count_list++;
            if (*(*mid) > *smaller_pair) {
                end = mid;
                if (end == res.begin()) break;
                --end;
            } else {
                begin = mid;
                if (begin == res.end()) break;
                ++begin;
            }
        }

        smaller_pair->sorted();
        res.insert(begin, smaller_pair);
    }
}
