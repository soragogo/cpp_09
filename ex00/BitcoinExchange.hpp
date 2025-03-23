#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
class BitcoinExchange {

public:
    BitcoinExchange(std::string input);
    void exchange();
    float return_price();
    float get_rate();
    void load_data();


private:
    std::map<std::string, float> _data;
    std::string _input;
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
