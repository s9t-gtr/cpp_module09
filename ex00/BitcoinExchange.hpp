#ifndef __BITCOINEXHANGE_HPP
# define __BITCOINEXHANGE_HPP 

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <stdexcept>

#define DATABASE_PATH "cpp_09/data.csv"

typedef std::map<std::string, float> dataMap;

class BitcoinExchange {
private:
    std::map<std::string, float> _database;
    
    // Private helper methods
    bool isValidDate(const std::string& date) const;
    bool isValidValue(const std::string& value) const;
    float parseValue(const std::string& value) const;
    std::string findClosestDate(const std::string& date) const;
    
public:
    BitcoinExchange();
    BitcoinExchange(const std::string& databasePath);
    ~BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);

    void processInputFile(const std::string& inputPath);
    void processLine(const std::string& line);

    // Exception classes
    class NotPositiveValue : public std::exception {
        public: const char* what() const throw();
    };
    
    class TooLargeNumber : public std::exception {
        public: const char* what() const throw();
    };
    
    class BadInput : public std::exception {
    private:
        std::string _error;
    public:
        BadInput(const std::string& input) : _error("bad input => " + input) {}
        virtual ~BadInput() throw() {}
        const char* what() const throw() { return _error.c_str(); }
    };
    
    class FileOpenFailed : public std::exception {
        public: const char* what() const throw();
    };
};

#endif
