#ifndef Cli_hpp
#define Cli_hpp

#include <vector>
#include <array>
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include "Unitval.hpp"
#include "../include/json.hpp"

using json = nlohmann::json;
using namespace std;

class Cli {
public:
  Cli(unsigned int size): nb_node(size){}
  unsigned int getNbNode();
  vector<Unitval*> & getC();
  vector<int> & getL();
  vector<int> & getI();
  vector<float> & getRanking();
  vector<float> produit_transpose(vector<float>, float);
  void print_cli();
  void pagerank(float, float);
  bool check_if_continue(vector<float>, float);
  static void loadJson(const char * path, vector<pair<long, float>> &);
private:
  unsigned int nb_node;
  vector<Unitval*> c;
  vector<int> l;
  vector<int> i;
  vector<float> ranking;
};
#endif /* Cli_hpp */
