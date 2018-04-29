#ifndef Recherche_hpp
#define Recherche_hpp

#include <iostream>
#include <sstream>
#include <string>
#include "Collector.hpp"
#include "Cli.hpp"
#include <set>
#include <unordered_map>
#include <map>
#include <algorithm>

using namespace std;

class Recherche {
public:
    Recherche(string recherche,string dict_to_exclude);
    void compute_result();
private:
    set<string> recherche;
    set<long> id_exclude_article;
    unordered_map<long, float> pagerank;
    unordered_map<string, set<long> *> collector;
};

#endif /* Recherche */
