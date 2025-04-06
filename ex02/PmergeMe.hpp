#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <list>
#include <iostream>

class Node_v {
    public:
        // Constructor and Destructor
        Node_v(const int & i);
        ~Node_v();

        // Member functions
        inline Node_v * & getLargerPair() { return _larger_pair; };
        inline Node_v * & getSmallerPair() { return _smaller_pair.back(); };
        inline void setLargerPair(Node_v * n) {_larger_pair = n;};
        inline void setSmallerPair(Node_v * n) {_smaller_pair.push_back(n);};
        inline void eraseSmallerPair() {_smaller_pair.pop_back();}
        inline int const & getNumber() {return _number;};
        inline void sorted() {_sorted = true;};
        inline bool isSorted() {return _sorted;};

    private:
        int _number;
        bool _sorted;
        std::vector<Node_v *> _smaller_pair;
        Node_v* _larger_pair;

        // Copy constructor and assignment operator
        Node_v(void);
        Node_v(const Node_v & src);
        Node_v & operator=(const Node_v & rhs);
};

class Node_l {
    public:
        // Constructor and Destructor
        Node_l(const int & i);
        ~Node_l();

        // Member functions
        inline Node_l * & getLargerPair() { return _larger_pair; };
        inline Node_l * & getSmallerPair() { return _smaller_pair.back(); };
        inline void setLargerPair(Node_l * n) {_larger_pair = n;};
        inline void setSmallerPair(Node_l * n) {_smaller_pair.push_back(n);};
        inline void eraseSmallerPair() {_smaller_pair.pop_back();}
        inline int const & getNumber() {return _number;};
        inline void sorted() {_sorted = true;};
        inline bool isSorted() {return _sorted;};

    private:
        int _number;
        bool _sorted;
        std::list<Node_l *> _smaller_pair;
        Node_l* _larger_pair;

        // Copy constructor and assignment operator
        Node_l(void);
        Node_l(const Node_l & src);
        Node_l & operator=(const Node_l & rhs);
};

void merge_insersion_sort_vector(std::vector<Node_v*> v, std::vector<Node_v*> &res);
void merge_insersion_sort_list(std::list<Node_l*> l, std::list<Node_l*> &res);

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
