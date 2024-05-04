#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(std::string dataBasePath){
    dataBase = readDataBase(dataBasePath);
}

BitcoinExchange::~BitcoinExchange(){
    delete [] dataBase; 
    
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other){
    if(this != &other){
        *this = other;
    }
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other){
    if(this != &other){
        dataBase = other.dataBase;
    }
    return *this;
}


/*=======================================================================
            member functions
=======================================================================*/

std::pair<std::string, float> BitcoinExchange::createPair(std::string& buf){
    std::string::size_type commaPos = buf.find(",");
    std::string key = buf.substr(0, commaPos);
    std::stringstream ss(buf.substr(commaPos+1));
    float value;
    ss >> value;
    return std::make_pair(key, value);
}

dataMap* BitcoinExchange::readDataBase(std::string dataBasePath){
    /*
        dataのsizeを知る。
        mapの生配列を確保する
        csvからデータをmapに入れる
    */
    dataMap *map = new dataMap;
    std::ifstream ifs(dataBasePath);
    if(!ifs)
        throw BitcoinExchange::FileOpenFailed();
    std::string buf;
    while(!ifs.eof()){
        std::getline(ifs, buf);
        map->insert(createPair(buf));
    }
    return map;
}

void readInputData(std::string inputFilePath) throw(){
    
}
/*==============================================
        exception what()
==============================================*/
const char* BitcoinExchange::NotPositiveValue::what() const throw(){
    return "NotPositiveValue";
}
const char* BitcoinExchange::TooLargeNumber::what() const throw(){
    return "TooLargeNumbe";
}
const std::string BitcoinExchange::BadInputValue::errorMessage(std::string inputValue) const throw(){
    return "BadInputValue" + inputValue;
}
const std::string BitcoinExchange::BadInputDate::errorMessage(std::string inputDate) const throw(){
    return "BadInputDate:" + inputDate;
}
const char* BitcoinExchange::FileOpenFailed::what() const throw(){
    return "FileOpenFailed";
}