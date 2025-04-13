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
        Node *  getLargerPair();
        Node *  getSmallerPairV();
        Node *  getSmallerPairL();
        void setLargerPair(Node * n);
        void setSmallerPairV(Node * n);
        void setSmallerPairL(Node * n);
        void eraseSmallerPairV();
        void eraseSmallerPairL();
        void sorted();
        bool isSorted();

        operator int() const;

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

Node * access_list(std::list<Node*> &l, int i);

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
