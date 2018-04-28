#include "Cli.hpp"

int main(int argc, char const *argv[]) {
  std::vector<pair<long, float>> pagerank;
  Cli::loadJson("pagerank.json", pagerank);

  //Pour avoir les valeurs
  for (const pair<long, float> &edge : pagerank) {
     std::cout << edge.first << " => " << edge.second << endl;
  }

  return 0;
}
