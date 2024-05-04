#ifndef __BITCOINEXHANGE_HPP
# define __BITCOINEXHANGE_HPP 

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

typedef std::map<std::string, float> dataMap;

class BitcoinExchange{
    private:
        BitcoinExchange();
    public:
        BitcoinExchange(std::string dataBasePath);
        ~BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
    public:
        dataMap *readDataBase(std::string dataBasePath);
        void readInputData(std::string inputFilePath) throw();
        void calcAndOutput() const;
    private:
        std::pair<std::string, float> createPair(std::string& buf);
    private:
        dataMap *dataBase;
        std::string data;
    public:
        class NotPositiveValue: public std::exception{
            public:
                const char* what() const throw();
        };
        class TooLargeNumber: public std::exception{
            public:
                const char* what() const throw();
        };
        class BadInputDate: public std::exception{
            public:
                const std::string errorMessage(std::string inputDate) const throw();
        };
        class BadInputValue: public std::exception{
            public:
                const std::string errorMessage(std::string inputValue) const throw();
        }; 
        class FileOpenFailed: public std::exception{
            public:
                const char* what() const throw();
        };

};
#endif