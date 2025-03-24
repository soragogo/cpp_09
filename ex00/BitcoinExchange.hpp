#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
class BitcoinExchange {

public:
    BitcoinExchange();
    void exchange(std::string & line);


    private:
    std::map<std::string, float> _data;
    std::string _input;
    void load_data();
    float get_rate(std::string const & date);
    bool is_valid_date(std::string date);
    bool is_number(const std::string& s);
    bool is_on_calendar(int const & year, int const & month, int const & day);
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
