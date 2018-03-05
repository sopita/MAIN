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
private:
    void put(const std::string key);
    std::vector<long> * get(std::string key);
    std::unordered_map<std::string,std::vector<long> *> map;
};

template<typename T>
std::ostream& operator<<(std::ostream& s, std::vector<T> t) {
    s << "[";
    for (std::size_t i = 0; i < t.size(); i++) {
        s << t[i] << (i == t.size() - 1 ? "" : ",");
    }
    return s << "]" << std::endl;
}