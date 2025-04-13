#include "RPN.hpp"

RPN::RPN() : _f("") {}

RPN::RPN(std::string const & f) : _f(f) {};

RPN::~RPN() {};

RPN::RPN(RPN const & rpn) {
    (void)rpn;
}

RPN & RPN::operator=(RPN const & rpn) {
    (void)rpn;
    return (*this);
}

void RPN::arithmetic(char const & c) {
    if (_s.size() < 2) throw std::runtime_error("Error");

    int a = _s.top();
    _s.pop();
    int b = _s.top();
    _s.pop();

    if (c == '/' && a == 0) throw std::runtime_error("Error");

    if (c == '+') _s.push(b+a);
    else if (c == '-') _s.push(b-a);
    else if (c == '*') _s.push(b*a);
    else if (c == '/') _s.push(b/a);
}

void RPN::caliculate() {
    std::string::iterator it = _f.begin();
    for (; it != _f.end(); ++it) {
        if (*it == ' ') continue;

        if (isdigit(*it))
            _s.push(*it - '0');
        else if (*it == '+' || *it == '-' || *it == '*' || *it == '/') {
            arithmetic(*it);
        }
        else throw std::runtime_error("Error");
    }
    if (_s.size() != 1) throw std::runtime_error("Error");

    std::cout << _s.top() << std::endl;
}
