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
    void getArticleWords( std::unordered_map<std::string,std::set<long> *> & map);
private:
    void getTokensAndStore(const string &s, std::unordered_map<std::string,std::set<long> *> & map, long id);
    std::string str_tolower(std::string s);
    ifstream file;
    bool dict[CHAR_MAX_VAL];
    std::string str_delimiters;
};

#endif /* Collector_hpp*/
