#include "PmergeMe.hpp"


#ifdef DEBUG
void print_vector(std::vector<PmergeMe *> v, std::string str) {
    std::cout << "   " << str << " ";
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << "[" <<*v[i] << "] ";
    }
    std::cout << std::endl;
}
#endif

PmergeMe * access_list(std::list<PmergeMe*> &l, int i) {
    std::list<PmergeMe*>::iterator it = l.begin();
    if ((size_t)i < 0 || (size_t)i >= l.size()) {
        std::cerr << "Index out of range" << std::endl;
        return NULL;
    }
    std::advance(it, i);
    return *it;
}

// PmergeMe class constructor and destructor
PmergeMe::PmergeMe(const int & i) : _number(i), _sorted(false), _larger_pair(NULL){}

PmergeMe::PmergeMe(void) : _number(-1), _sorted(false) {}

PmergeMe::PmergeMe(const PmergeMe & src) {
    *this = src;
}

PmergeMe::~PmergeMe() {}

PmergeMe * PmergeMe::getLargerPair() {
    return _larger_pair;
}

PmergeMe * PmergeMe::getSmallerPairV() {
    if (_smaller_pair_v.empty()) return NULL;
    return _smaller_pair_v.back();
}

PmergeMe * PmergeMe::getSmallerPairL() {
    if (_smaller_pair_l.empty()) return NULL;
    return _smaller_pair_l.back();
}

void PmergeMe::setLargerPair(PmergeMe * n) {
    _larger_pair = n;
}

void PmergeMe::setSmallerPairV(PmergeMe * n) {
    _smaller_pair_v.push_back(n);
}

void PmergeMe::setSmallerPairL(PmergeMe * n) {
    _smaller_pair_l.push_back(n);
}

void PmergeMe::eraseSmallerPairV() {
    if (!_smaller_pair_v.empty()) {
        _smaller_pair_v.pop_back();
    }
}

void PmergeMe::eraseSmallerPairL() {
    if (!_smaller_pair_l.empty()) {
        _smaller_pair_l.pop_back();
    }
}

void PmergeMe::sorted() {
    _sorted = true;
}

bool PmergeMe::isSorted() {
    return _sorted;
}

PmergeMe::operator int() const {
    return _number;
}

PmergeMe & PmergeMe::operator=(const PmergeMe & rhs) {
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

void merge_insersion_sort_vector(std::vector<PmergeMe*> v, std::vector<PmergeMe*> &res){

    #ifdef DEBUG
    std::cout << "----------------------------" << std::endl;
    std::cout << "ソートが呼ばれた" << std::endl;
    print_vector(v, "初期値");
    #endif

    if (v.size() < 2) {
        #ifdef DEBUG
        std::cout << "size < 2" << std::endl;
        std::cout << "push_back [" << v[0] << "]"<< std::endl;
        #endif
        res.push_back(v[0]);
        #ifdef DEBUG
        std::cout << "............................" << std::endl;
        #endif
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
        #ifdef DEBUG
        print_vector(res, "size == 2の処理結果");
        std::cout << "............................" << std::endl;
        #endif
        return;
    }

    std::vector < PmergeMe * >large;
    std::vector < PmergeMe * >small;
    for (std::vector<PmergeMe*>::iterator it = v.begin(); it != v.end() - 1; ++it) {
        if (std::distance(it, v.begin()) % 2 == 0) {
            std::vector<PmergeMe *>::iterator l_it;
            std::vector<PmergeMe *>::iterator s_it;
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

    #ifdef DEBUG
    print_vector(large, "大きい組の数字");
    #endif

    PmergeMe * leaf = NULL;
    if (v.size() % 2 == 1)
    leaf = v.back();
    merge_insersion_sort_vector(large, res);
    #ifdef DEBUG
    std::cout << "再起から抜けた" << std::endl;
    print_vector(res, "再起から得た結果");
    #endif
    for (std::vector<PmergeMe *>::iterator it = res.begin(); it != res.end(); ++it) {
        if ((*it)->getSmallerPairV() != NULL) {
            small.push_back((*it)->getSmallerPairV());
            (*it)->eraseSmallerPairV();
        }
    }
    if (leaf != NULL) small.push_back(leaf);

    #ifdef DEBUG
    print_vector(small, "小さい組の数字  ");
    #endif

    #ifdef DEBUG
    std::cout << std::endl;
    #endif
    std::vector<int> indices = generate_indices(small.size());
    int small_end = small.size() - 1;
    for (size_t i = 0; i < small.size(); ++i) {
        if (i == 0) {
            small[0]->sorted();
            res.insert(res.begin(), small[0]);
            #ifdef DEBUG
            std::cout << "    1番目の数字["<< *small[0] << "]を処理"<< std::endl;
            std::cout << std::endl;
            print_vector(res, "現在のソート結果");
            std::cout << std::endl;
            #endif
            continue;
        }
        
        int geta = (indices[i] - 1) > small_end ? small_end-- : indices[i] - 1;
        std::vector<PmergeMe*>::iterator it = (small.begin() + geta);
        PmergeMe* smaller_pair = *it;
        PmergeMe* larger_pair = smaller_pair->getLargerPair();
        
        std::vector<PmergeMe*>::iterator res_pos;

        #ifdef DEBUG
        std::cout << "    " << indices[i] << "番目の数字[" << *smaller_pair << "]を処理"<< std::endl;
        #endif

        for (res_pos = res.begin(); res_pos != res.end(); ++res_pos) {
            if (*res_pos == larger_pair) break;
        }
        #ifdef DEBUG
        std::vector<PmergeMe*>::iterator debug_it = res.begin();
        std::cout << "    [" << *smaller_pair  << "]と比較対象の数字は ";
        while (debug_it != res_pos) {
            std::cout << "[" << *(*debug_it) << "] ";
            ++debug_it;
        }
        std::cout << std::endl;
        #endif



        std::vector<PmergeMe*>::iterator begin = res.begin();
        std::vector<PmergeMe*>::iterator end = res_pos - 1;
        std::vector<PmergeMe*>::iterator mid;
        while (begin <= end) {
            mid = begin + (end - begin) / 2;
            // count
            count_vector++;
            #ifdef DEBUG
            std::cout << "     [" << *(*mid) << "]と比較" << std::endl;
            #endif
            if (*(*mid) > *smaller_pair) {
                end = mid - 1;
            } else {
                begin = mid + 1;
            }
        }

        smaller_pair->sorted();
        #ifdef DEBUG
        if (begin == res.end()) {
            std::cout << "    [" << *smaller_pair << "]を[" << *(*(begin - 1)) << "]の後に挿入" << std::endl;
        } else {
            std::cout << "    [" << *smaller_pair << "]を[" << *(*begin) << "]の前に挿入" << std::endl;
        }
        #endif
        res.insert(begin, smaller_pair);
        #ifdef DEBUG
        std::cout << std::endl;
        print_vector(res, "現在のソート結果");
        std::cout << std::endl;
        #endif
    }
    #ifdef DEBUG
    std::cout << "............................" << std::endl;
    #endif
}


void merge_insersion_sort_list(std::list<PmergeMe*> l, std::list<PmergeMe*> &res){

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

    std::list < PmergeMe * >large;
    std::list < PmergeMe * >small;
    for (std::list<PmergeMe*>::iterator it = l.begin(); it != l.end(); ++it) {
        if (std::distance(l.begin(), it) % 2 == 0) {
            std::list<PmergeMe *>::iterator l_it;
            std::list<PmergeMe *>::iterator s_it;

            std::list<PmergeMe *>::iterator next_it = it;
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
    PmergeMe * leaf = NULL;
    if (l.size() % 2 == 1)
        leaf = l.back();

    merge_insersion_sort_list(large, res);
    for (std::list<PmergeMe *>::iterator it = res.begin(); it != res.end(); ++it) {
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
        std::list<PmergeMe*>::iterator it = small.begin();
        std::advance(it, geta);
        PmergeMe* smaller_pair = *it;
        PmergeMe* larger_pair = smaller_pair->getLargerPair();

        std::list<PmergeMe*>::iterator res_pos;
        for (res_pos = res.begin(); res_pos != res.end(); ++res_pos) {
            if (*res_pos == larger_pair) break;
        }

        std::list<PmergeMe*>::iterator begin = res.begin();
        std::list<PmergeMe*>::iterator end = res_pos;
        --end;

        std::list<PmergeMe*>::iterator mid;

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

