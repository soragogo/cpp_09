#include "RPN.hpp"

int main(int argc, char * argv[]) {
    if (argc != 2) {
        std::cerr << "You must pass one argument." << std::endl;
        return 1;
    }
    try {
        std::string f(argv[1]);
        RPN rpn(f);
        rpn.caliculate();
    }
    catch (std::exception & e){
        std::cerr << e.what() << std::endl;
    }
}
