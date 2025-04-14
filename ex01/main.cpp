#include "RPN.hpp"

#include <csignal>
#include <cstdlib>

void signalHandler(int signalNumber) {
    std::cerr << "signal " << signalNumber << " received" << std::endl;
    exit(signalNumber);
}

int main(int argc, char * argv[]) {

    signal(SIGFPE, signalHandler);

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
