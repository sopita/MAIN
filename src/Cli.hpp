#ifndef Cli_hpp
#define Cli_hpp

#include <vector>
#include <array>
#include <vector>
#include <iostream>
#include <cmath>
#include "Unitval.hpp"

using namespace std;

class Cli {
public:
  Cli(int size): nb_node(size){}
  int get_nb_node() { return nb_node; }
  vector<Unitval*> & get_c() { return c; }
  vector<int> & get_l() { return l; }
  vector<int> & get_i() { return i; }
  vector<float> produit_direct(vector<float>);
  vector<float> produit_transpose(vector<float>);
  void print_cli();
  void pagerank(float, float);
  bool check_if_continue(vector<float>, float);
private:
  unsigned int nb_node;
  vector<Unitval*> c;
  vector<int> l;
  vector<int> i;
  vector<float> ranking;
};
#endif /* Cli_hpp */
