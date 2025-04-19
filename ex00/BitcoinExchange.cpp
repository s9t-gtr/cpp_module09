#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>

// Constructor implementations
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& databasePath) {
    std::ifstream file(databasePath);
    if (!file.is_open())
        throw FileOpenFailed();

    std::string line;
    // Skip header line
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date, value;
        std::getline(ss, date, ',');
        std::getline(ss, value);
        
        if (!date.empty() && !value.empty()) {
            _database[date] = atof(value.c_str());
        }
    }
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
    *this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        _database = other._database;
    }
    return *this;
}

// Helper method implementations
bool BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    
    int year, month, day;
    std::stringstream ss(date);
    char dash;
    
    ss >> year >> dash >> month >> dash >> day;
    
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;
    
    // Basic month day validation
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeap ? 29 : 28))
            return false;
    }
    
    return true;
}

bool BitcoinExchange::isValidValue(const std::string& value) const {
    // Check if the string is a valid number
    std::string::const_iterator it = value.begin();
    bool hasDecimal = false;
    
    // Skip leading whitespace
    while (it != value.end() && std::isspace(*it)) ++it;
    
    // Check for optional sign
    if (it != value.end() && (*it == '+' || *it == '-')) ++it;
    
    // Check for digits
    if (it == value.end()) return false;
    
    while (it != value.end()) {
        if (*it == '.') {
            if (hasDecimal) return false; // More than one decimal point
            hasDecimal = true;
        } else if (!std::isdigit(*it)) {
            return false;
        }
        ++it;
    }
    
    // Convert and check if positive
    float num = atof(value.c_str());
    return num >= 0;
}

float BitcoinExchange::parseValue(const std::string& value) const {
    return atof(value.c_str());
}

std::string BitcoinExchange::findClosestDate(const std::string& date) const {
    if (_database.empty()) return "";
    
    std::map<std::string, float>::const_iterator it = _database.lower_bound(date);
    if (it == _database.begin()) return it->first;
    if (it == _database.end()) return (--it)->first;
    
    std::map<std::string, float>::const_iterator prev = it;
    --prev;
    
    return prev->first;
}

// Main processing methods
void BitcoinExchange::processInputFile(const std::string& inputPath) {
    std::ifstream file(inputPath);
    if (!file.is_open())
        throw FileOpenFailed();

    std::string line;
    // Skip header line
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        try {
            processLine(line);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

void BitcoinExchange::processLine(const std::string& line) {
    std::stringstream ss(line);
    std::string date, value;
    std::getline(ss, date, '|');
    std::getline(ss, value);
    
    // Trim whitespace
    date.erase(0, date.find_first_not_of(" \t"));
    date.erase(date.find_last_not_of(" \t") + 1);
    value.erase(0, value.find_first_not_of(" \t"));
    value.erase(value.find_last_not_of(" \t") + 1);
    
    if (!isValidDate(date))
        throw BadInput(line.c_str());
    
    if (!isValidValue(value))
        throw NotPositiveValue();
    
    float amount = parseValue(value);
    if (amount > 1000)
        throw TooLargeNumber();
    
    std::string closestDate = findClosestDate(date);
    float rate = _database[closestDate];
    float result = amount * rate;
    
    // Format output to match requirements exactly
    std::cout << date << " => ";
    
    // Format input value
    if (amount == static_cast<int>(amount))
        std::cout << static_cast<int>(amount);
    else
        std::cout << amount;
    
    // Format result
    std::cout << " = " << result << std::endl;
}

// Exception implementations
const char* BitcoinExchange::NotPositiveValue::what() const throw() {
    return "not a positive number.";
}

const char* BitcoinExchange::TooLargeNumber::what() const throw() {
    return "too large a number.";
}

const char* BitcoinExchange::FileOpenFailed::what() const throw() {
    return "could not open file.";
}
