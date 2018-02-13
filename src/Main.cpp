#include "Read_Graph.hpp"

int main(int argc, char const *argv[]) {
  Read_graph graph("../examples/tp1-fig1.txt", 0);
  pair<int, int> * p = graph.get_edge();
  std::cout << p->first << "\t" << p->second << std::endl;
  return 0;
}
