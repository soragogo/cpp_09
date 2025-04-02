#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <list>
#include <iostream>

class Node {
    public:
        // Constructor and Destructor
        Node(const int & i);
        ~Node();

        // Member functions
        inline std::vector<Node *> & getLargerPair() { return _larger_pair; };
        inline std::vector<Node *> & getSmallerPair() { return _smaller_pair; };
        inline void setLargerPair(Node * n) {_larger_pair.push_back(n);};
        inline void setSmallerPair(Node * n) {_smaller_pair.push_back(n);};
        inline void eraseLargerPair() {_larger_pair.pop_back();}
        inline void eraseSmallerPair() {_smaller_pair.pop_back();}
        inline int const & getNumber() {return _number;};
        inline void sorted() {_sorted = true;};
        inline bool isSorted() {return _sorted;};

        //debug
        void printNode(void);
        private:
        int _number;
        bool _sorted;
        std::vector<Node *> _smaller_pair;
        std::vector<Node *> _larger_pair;

        // Copy constructor and assignment operator
        Node(void);
        Node(const Node & src);
        Node & operator=(const Node & rhs);
};

void merge_insersion_sort(std::vector<Node*> v, std::vector<Node*> &res);

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
