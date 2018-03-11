#ifndef Collector_hpp
#define Collector_hpp

#include "Article.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <regex>

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
    Article* getNewArticle();
    Collector(string);
private:
    ifstream file;
};

#endif /* Collector_hpp*/