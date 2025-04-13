#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <string>
#include <stack>
class RPN {
public:
    RPN(std::string const & f);
    ~RPN();
    void caliculate();
private:
    std::string _f;
    std::stack<int> _s;
    RPN();
    RPN(RPN const & rpn);
    RPN & operator=(RPN const & rpn);
    void arithmetic(char const & c);
};



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
