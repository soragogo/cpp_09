#include "BitcoinExchange.hpp"

int main() {
    std::ifstream input_file("input.txt");
    try
    {
        if(!input_file) {
            throw std::runtime_error("Error: could not open file.");
        }

        BitcoinExchange btc;
        std::string line;
        std::getline(input_file, line);
        if (line.compare("date | value")){
            throw std::runtime_error("Error: invalid syntax of the imput file.");
        }
        while (std::getline(input_file, line)) {
            try{
                btc.exchange(line);
            }
            catch (std::exception & e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() <<std::endl;
    }

    input_file.close();
}
