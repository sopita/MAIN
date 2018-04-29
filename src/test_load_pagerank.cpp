#include "Cli.hpp"

int main(int argc, char const *argv[]) {
  unordered_map<long, float>  pagerank;
  Cli::loadJson("pagerank.json", pagerank);

  //Pour avoir les valeurs
  for(const auto& n : pagerank) {
       std::cout << n.first << " => " << n.second << endl;
  }

  return 0;
}
