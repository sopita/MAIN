#include "Article.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <regex>

class Collector {
public:
  Article* getNewArticle();
  Collector(string);
private:
  ifstream file;
};
