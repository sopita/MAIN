#include <vector>
#include <array>

class Cli {
public:
  Cli(int);
  int get_nb_node() { return nb_node; }
  std::vector<float> get_c() { return c; }
  std::vector<int> get_l() { return l; }
  std::vector<int> get_i() { return i; }
private:
  int nb_node;
  std::vector<float> c;
  std::vector<int> l;
  std::vector<int> i;
};
