#include "PmergeMe.hpp"

class Node {
public:
    Node(int i) { _number = i;};
    Node() { _number = -1; };
    std::vector<Node *> & getLargerPair() { return _larger_pair; };
    std::vector<Node *> & getSmallerPair() { return _smaller_pair; };
    void setLargerPair(Node * n) {_larger_pair.push_back(n);};
    void setSmallerPair(Node * n) {_smaller_pair.push_back(n);};
    void eraseLargerPair() {_larger_pair.erase(_larger_pair.begin());}
    void eraseSmallerPair() {_smaller_pair.erase(_smaller_pair.begin());}
    int const & getNumber() {return _number;};
private:
    int _number;
    std::vector<Node *> _larger_pair;
    std::vector<Node *> _smaller_pair;

};


void sort(std::vector<Node> &v, std::vector<Node*> &res){

    if (v.size() == 1) {
        res.push_back(&v.front());
        return;
    }

    std::vector < Node > large;
    std::vector < Node > small;
    for (std::vector<Node>::iterator it = v.begin(); it != v.end() - 1; ++it) {
        if (std::distance(it, v.begin()) % 2 == 0) {
            std::vector<Node>::iterator l_it = it->getNumber() > (it + 1)->getNumber() ? it : (it + 1);
            std::vector<Node>::iterator s_it = it->getNumber() < (it + 1)->getNumber() ? it : (it + 1);
            l_it->setSmallerPair(&*s_it);
            s_it->setLargerPair(&*l_it);
            large.push_back(*l_it);
            small.push_back(*s_it);
        }
    }
    if (v.size() % 2 == 1)
        small.push_back(v.back());

    sort(large, res);
}


int main() {
    std::vector<Node> v;
    for (int i = 4; i > 0; --i) {
        v.push_back(Node(i));
    }
    std::vector<Node *> res;
    sort(v, res);

}
