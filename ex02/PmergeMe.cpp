#include "PmergeMe.hpp"

// Node class constructor and destructor
Node::Node(const int & i) : _number(i), _sorted(false) {};

Node::Node(void) : _number(-1), _sorted(false) {};

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
        this->_smaller_pair = rhs._smaller_pair;
    }
    return *this;
}

// debug
void Node::printNode(void) {
    std::cout << "Node: " << _number << std::endl;
    std::cout << "Larger pair: ";
        std::cout << _larger_pair->getNumber() << " ";
    std::cout << std::endl;
    std::cout << "Smaller pair: ";
    for (std::vector<Node *>::iterator it = _smaller_pair.begin(); it != _smaller_pair.end(); ++it) {
        std::cout << (*it)->getNumber() << " ";
    }
    std::cout << std::endl;
}


void merge_insersion_sort(std::vector<Node*> v, std::vector<Node*> &res){

    if (v.size() < 2) {
        return;
    }

    if (v.size() == 2) {
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

    std::vector < Node * >large;
    std::vector < Node * >small;
    for (std::vector<Node*>::iterator it = v.begin(); it != v.end() - 1; ++it) {
        if (std::distance(it, v.begin()) % 2 == 0) {
            std::vector<Node *>::iterator l_it = (*it)->getNumber() > (*(it + 1))->getNumber() ? it : (it + 1);
            std::vector<Node *>::iterator s_it = !((*it)->getNumber() > (*(it + 1))->getNumber()) ? it : (it + 1);
            (*l_it)->setSmallerPair(*s_it);
            (*s_it)->setLargerPair(*l_it);
            large.push_back(*l_it);
            small.push_back(*s_it);
        }
    }
    if (v.size() % 2 == 1)
        large.push_back(v.back());

    merge_insersion_sort(large, res);
    for (std::vector<Node *>::reverse_iterator it = small.rbegin(); it != small.rend(); ++it) {

        Node* smaller_pair = *it;
        Node* larger_pair = smaller_pair->getLargerPair();

        std::vector<Node*>::iterator res_pos;
        for (res_pos = res.begin(); res_pos != res.end(); ++res_pos) {
            if (&*res_pos == &larger_pair) {
                break;
            }
        }

        std::vector<Node*>::iterator begin = res.begin();
        std::vector<Node*>::iterator end = res_pos - 1;
        std::vector<Node*>::iterator mid;
        while (begin <= end) {
            mid = begin + (end - begin) / 2;
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
