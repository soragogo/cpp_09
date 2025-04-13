#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <deque>
#include <list>
#include <iostream>

class Node {
    public:
        // Constructor and Destructor
        Node(const int & i);
        ~Node();

        // Member functions
        inline Node *  getLargerPair() { return _larger_pair; };
        inline Node *  getSmallerPairV()
        {
            if (_smaller_pair_v.empty()) return NULL;
            return _smaller_pair_v.back();
        };
        inline Node *  getSmallerPairL()
        {
            if (_smaller_pair_l.empty()) return NULL;
            return _smaller_pair_l.back();
        };
        inline void setLargerPair(Node * n) {_larger_pair = n;};
        inline void setSmallerPairV(Node * n) {_smaller_pair_v.push_back(n);};
        inline void setSmallerPairL(Node * n) {_smaller_pair_l.push_back(n);};
        inline void eraseSmallerPairV() {_smaller_pair_v.pop_back();}
        inline void eraseSmallerPairL() {_smaller_pair_l.pop_back();}
        inline void sorted() {_sorted = true;};
        inline bool isSorted() {return _sorted;};

        inline operator int() const { return _number; }

    private:
        int _number;
        bool _sorted;
        std::vector<Node *> _smaller_pair_v;
        std::list<Node *> _smaller_pair_l;
        Node* _larger_pair;

        // Copy constructor and assignment operator
        Node(void);
        Node(const Node & src);
        Node & operator=(const Node & rhs);
};

inline Node * access_list(std::list<Node*> &l, int i) {
    std::list<Node*>::iterator it = l.begin();
    if ((size_t)i < 0 || (size_t)i >= l.size()) {
        std::cerr << "Index out of range" << std::endl;
        return NULL;
    }
    std::advance(it, i);
    return *it;
}

void merge_insersion_sort_vector(std::vector<Node*> v, std::vector<Node*> &res);
void merge_insersion_sort_list(std::list<Node*> v, std::list<Node*> &res);

// count
extern size_t count_vector;
extern size_t count_list;

// colors
# define END             "\033[0m"
# define BOLD            "\033[1m"
# define BLACK           "\033[30m"
# define RED             "\033[31m"
# define GREEN           "\033[32m"
# define YELLOW          "\033[33m"
# define BLUE            "\033[34m"
# define MAGENTA         "\033[35m"
# define CYAN            "\033[36m"
# define WHITE           "\033[37m"
# define UNDERLINE       "\033[4m"
# define BOLD_UNDERLINE  "\033[1;4m"
#endif
