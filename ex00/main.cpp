#include "BitcoinExchange.hpp"

#define SPECIFY_FILENAME 2
#define FILENAME 1
#define DATABASE_PATH "cpp_09/data.csv"

int main(int argc, char **argv){
    if(argc == SPECIFY_FILENAME){
        BitcoinExchange Bitcoin(DATABASE_PATH);
        Bitcoin.readInputData(argv[FILENAME]);

    }else
        std::cerr << "Error: could not open file." << std::endl;
}

// void func(std::map<std::string, int>* map){
//     map->insert(std::make_pair("hoge", 0));
//     map->insert(std::make_pair("ho", 1));
//     map->insert(std::make_pair("he", 2));
//     map->insert(std::make_pair("hoe", 3));
// }
// int main(){
//     std::map<std::string, int> map;
//     func(&map);
//     std::cout << &map["he"] << std::endl;

//     std::map<std::string, int> map1;
//     map1 = map;
//     std::cout << &map1["he"] << std::endl;

// }