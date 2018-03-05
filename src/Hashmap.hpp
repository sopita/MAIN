#include "Collector.hpp"
//#include "Article.hpp"
#include <unordered_map>
#include <fstream>
#include <iostream>

class Hashmap{
public:
    void show_map();
    void create_collector(std::string md,std::vector<std::string> &dicts,std::string exclude_dict);
    void add_dictionnary(std::string dict);
    void delete_dict(std::string dict);
    std::unordered_map<std::string,std::vector<int>> getMap();
private:
    void put(const std::string key);
    std::vector<int> * get(std::string key);
    std::unordered_map<std::string,std::vector<int> *> map;
};