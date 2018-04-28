#ifndef Collector_hpp
#define Collector_hpp

#include "Article.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <regex>
#include <string>
#include <unordered_map>
#include <set>

#define DELIMITERS " ,:|()[]"
#define CHAR_MAX_VAL 256

class Collector {
public:
    Collector(string);
    ~Collector();
    void create_collector(std::vector<std::string> & dicts,std::string exclude_dict);
    void show_map();
    void getArticleWords();
    static void loadJson(const char *, unordered_map<string, set<long> *> &);
private:
    void getTokensAndStore(const string &s, long id);
    std::string str_tolower(std::string s);
    ifstream file;
    bool dict[CHAR_MAX_VAL];
    std::string str_delimiters;
    void add_dictionnary(std::string dict);
    void delete_dict(std::string dict);
    void put(const std::string key);
    std::set<long> * getArticleIds(std::string key);
    std::unordered_map<std::string,std::set<long> *> mot_produits;
};

template<typename T>
std::ostream& operator<<(std::ostream& s, std::vector<T> t) {
    s << "[";
    for (std::size_t i = 0; i < t.size(); i++) {
        s << t[i] << (i == t.size() - 1 ? "" : ",");
    }
    return s << "]" << std::endl;
}


#endif /* Collector_hpp*/
