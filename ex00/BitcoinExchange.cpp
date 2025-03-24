#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange(){
    load_data();
}

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
    data_file.close();
}

float BitcoinExchange::get_rate(std::string const & date) {
    std::map<std::string, float>::iterator it = _data.begin();

    if (it->first > date)
        throw std::out_of_range("Error: bad input => " + date);
    std::map<std::string, float>::iterator ans = _data.upper_bound(date);
    --ans;
    return ans->second;
}

bool BitcoinExchange::is_number(const std::string& s) {
    if (s.empty())
        return false;

    for (std::string::const_iterator it = s.begin(); it != s.end(); ++it) {
        if (!isdigit(*it))
            return false;
    }
    return true;
}

bool BitcoinExchange::is_on_calendar(int const & year, int const & month, int const & day) {
    const int MONTH_DAYS[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 4 == 0 && month == 2) {
        if (day > 29) return false;
    }
    else if (day > MONTH_DAYS[month])
        return false;
    return true;
}


bool BitcoinExchange::is_valid_date(std::string date) {
    if (date.size() != std::string("YYYY-mm-dd ").size())
        return false;
    else if (date[4] != '-' || date[7] != '-' || date[10] != ' ')
        return false;

    std::istringstream ss(date);
    std::string year_str, month_str, day_str;

    std::getline(ss, year_str, '-');
    std::getline(ss, month_str, '-');
    std::getline(ss, day_str, ' ');

    if (!is_number(year_str) || !is_number(month_str) || !is_number(day_str))
        return false;

    if (year_str < "2009" || "2026" < year_str
        || month_str < "01" || "12" < month_str
        || day_str < "01" || "31" < day_str)
        return false;

    std::istringstream year_ss(year_str), month_ss(month_str), day_ss(day_str);

    int year_num, month_num, day_num;
    year_ss >> year_num;
    month_ss >> month_num;
    day_ss >> day_num;
    if (!is_on_calendar(year_num, month_num, day_num))
        return false;

    return true;
}


void BitcoinExchange::exchange(std::string & line) {
    std::string date;
    float value;

    std::istringstream  ss(line);

    std::getline(ss, date, '|');

    if (!is_valid_date(date))
        throw std::invalid_argument("Error: bad input => " + line);

    std::string value_str;
    std::getline(ss, value_str);

    if (value_str == "") {
        throw std::invalid_argument("Error: bad input => " + line);
    }
    std::istringstream value_ss(value_str);
    value_ss >> value;

    if (value < 0)
        throw std::out_of_range("Error: not a positive number.");
    else if (value > 1000)
        throw std::out_of_range("Error: too large a number.");

    float rate = get_rate(date);

    std::cout << date << " => " << value << " = " << value * rate << std::endl;
}
