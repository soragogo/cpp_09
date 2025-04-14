#ifndef PMERGEME_HPP
# define PMERGEME_HPP

// # define DEBUG 0

#include <vector>
#include <deque>
#include <list>
#include <iostream>

class PmergeMe {
    public:
        // Constructor and Destructor
        PmergeMe(const int & i);
        ~PmergeMe();

        // Member functions
        PmergeMe *  getLargerPair();
        PmergeMe *  getSmallerPairV();
        PmergeMe *  getSmallerPairL();
        void setLargerPair(PmergeMe * n);
        void setSmallerPairV(PmergeMe * n);
        void setSmallerPairL(PmergeMe * n);
        void eraseSmallerPairV();
        void eraseSmallerPairL();
        void sorted();
        bool isSorted();

        operator int() const;

    private:
        int _number;
        bool _sorted;
        std::vector<PmergeMe *> _smaller_pair_v;
        std::list<PmergeMe *> _smaller_pair_l;
        PmergeMe* _larger_pair;

        // Copy constructor and assignment operator
        PmergeMe(void);
        PmergeMe(const PmergeMe & src);
        PmergeMe & operator=(const PmergeMe & rhs);
};

PmergeMe * access_list(std::list<PmergeMe*> &l, int i);

void merge_insersion_sort_vector(std::vector<PmergeMe*> v, std::vector<PmergeMe*> &res);
void merge_insersion_sort_list(std::list<PmergeMe*> v, std::list<PmergeMe*> &res);

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
