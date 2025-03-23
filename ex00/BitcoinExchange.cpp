#include "BitcoinExchange.hpp"

void BitcoinExchange::load_data() {
    std::ifstream data_file("data.csv");
    std::string line;
    std::getline(data_file, line);
    if (line != "date,exchange_rate")
        throw std::runtime_error("Error: data file is broken");
    while (std::getline(data_file, line)) {
        std::string date;
        float rate;

        std::istringstream ss(line);

        std::getline(ss, date, ',');

        std::string rate_str;
        std::getline(ss, rate_str);

        std::istringstream rate_ss(rate_str);
        rate_ss >> rate;

        _data[date] = rate;
    }
    //debug
    std::map<std::string, float>::iterator it;
    for (it = _data.begin(); it != _data.end(); ++it)
        std::cout << "1: " << it->first << ", 2: " << it->second << std::endl;

    data_file.close();
}

BitcoinExchange::BitcoinExchange(std::string input) : _input(input) {
    std::ifstream input_file(_input);
    if(!input_file)
        throw std::runtime_error("Error: could not open file.");

    //debug
    std::cout << "input file: " << _input << std::endl;
    load_data();
}
