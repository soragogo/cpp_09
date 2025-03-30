#include "PmergeMe.hpp"

class Node {
public:
    Node(int i) { _number = i; _sorted = false; };
    Node() { _number = -1; _sorted = false; };
    std::vector<Node *> & getLargerPair() { return _larger_pair; };
    std::vector<Node *> & getSmallerPair() { return _smaller_pair; };
    void setLargerPair(Node * n) {_larger_pair.push_back(n);};
    void setSmallerPair(Node * n) {_smaller_pair.push_back(n);};
    void eraseLargerPair() {_larger_pair.pop_back();}
    void eraseSmallerPair() {_smaller_pair.pop_back();}
    int const & getNumber() {return _number;};
    void sorted() {_sorted = true;};
    bool isSorted() {return _sorted;};
    //debug
    void printNode() {
        std::cout << "Node: " << _number << std::endl;
        std::cout << "Larger pair: ";
        for (std::vector<Node *>::iterator it = _larger_pair.begin(); it != _larger_pair.end(); ++it) {
            std::cout << (*it)->getNumber() << " ";
        }
        std::cout << std::endl;
        std::cout << "Smaller pair: ";
        for (std::vector<Node *>::iterator it = _smaller_pair.begin(); it != _smaller_pair.end(); ++it) {
            std::cout << (*it)->getNumber() << " ";
        }
        std::cout << std::endl;
    }
private:
    int _number;
    std::vector<Node *> _larger_pair;
    bool _sorted;
    std::vector<Node *> _smaller_pair;

};

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
            std::vector<Node *>::iterator s_it = (*it)->getNumber() < (*(it + 1))->getNumber() ? it : (it + 1);
            (*l_it)->setSmallerPair(*s_it);
            (*s_it)->setLargerPair(*l_it);
            large.push_back(*l_it);
            small.push_back(*s_it);
        }
    }
    if (v.size() % 2 == 1)
        large.push_back(v.back());

    merge_insersion_sort(large, res);
    for (std::vector<Node *>::iterator it = large.begin(); it != large.end(); ++it) {
        if (!(*it)->isSorted()) {
            (*it)->sorted();
            res.push_back(*it);
        }

        // smallerPairがあれば処理
        if (!(*it)->getSmallerPair().empty()) {
            Node* smaller_pair = (*it)->getSmallerPair().back();
            (*it)->eraseSmallerPair(); // 末尾の要素を削除

            // largeの要素の位置をresの中で見つける
            std::vector<Node*>::iterator res_pos;
            for (res_pos = res.begin(); res_pos != res.end(); ++res_pos) {
                if (*res_pos == *it) {
                    break; // 見つかった位置
                }
            }

            // 適切な挿入位置を見つける（res_posから前方向に探索）
            std::vector<Node*>::iterator insert_pos = res_pos;
            while (insert_pos != res.begin()) {
                --insert_pos;
                if ((*insert_pos)->getNumber() <= smaller_pair->getNumber()) {
                    // 適切な位置を見つけたら一つ後ろに
                    ++insert_pos;
                    break;
                }
            }

            // smaller_pairを適切な位置に挿入
            smaller_pair->sorted();
            res.insert(insert_pos, smaller_pair);
        }
    }
}


int main() {
    std::vector<Node *> v;
    for (int i = 10; i > 0; --i) {
        v.push_back(new Node(i));
    }
    std::vector<Node *> res;
    merge_insersion_sort(v, res);
    for (std::vector<Node *>::iterator it = res.begin(); it != res.end(); ++it) {
        std::cout << (*it)->getNumber() << " ";
    }

}

