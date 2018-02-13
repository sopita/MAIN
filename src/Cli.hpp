#ifndef Cli_hpp
#define Cli_hpp

#include <vector>
#include <array>
#include <vector>
#include "Unitval.hpp"

using namespace std;

class Cli {
public:
  int get_nb_node() { return nb_node; }
  vector<Unitval*> get_c() { return c; }
  vector<int> get_l() { return l; }
  vector<int> get_i() { return i; }
  vector<float> produit_direct(Cli &, vector<int>);
  vector<float> produit_transpose(Cli &, vector<int>);
private:
  int nb_node;
  vector<Unitval*> c;
  vector<int> l;
  vector<int> i;
};
#endif /* Cli_hpp */
