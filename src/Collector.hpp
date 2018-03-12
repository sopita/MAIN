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


/****
 A BETTER REGEX BUT WORKING ONLY ON WIN AND LINUX
 "[^\\[a-zA-Z ]||\\[||\\]]"
 ****/

#if defined(_WIN32) || defined(__linux__)
#define REGEX "([\\-,;:](\\[.*?\\]||&))||(\\[.*?\\]||&)"
#elif __APPLE__
#define REGEX R"([\\-,;:](\\[.*?\\]||&))||(\\[.*?\\]||&)"
#endif

class Collector {
public:
    Collector(string);
    void getArticleWords( std::unordered_map<std::string,std::set<long> *> & map);
private:
    void replace_by(std::string& str, std::unordered_map<std::string,std::set<long> *> & map,long id );
    std::unordered_map<char,char> punctuation_to_delete;
    ifstream file;
};

#endif /* Collector_hpp*/
