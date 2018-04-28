#include "Collector.hpp"

int main(int argc, char const *argv[]) {
  unordered_map<string, set<long> *> collector;
  Collector::loadJson("collector.json", collector);

  unordered_map<std::string, std::set<long> *>:: iterator itr;
  std::set<long>::iterator set_it;

  for (itr=collector.begin(); itr!=collector.end(); itr++){
    cout << itr->first << " : ";
    for (set_it = itr->second->begin(); set_it != itr->second->end(); ++set_it){
      cout << *set_it << ", ";
    }
    cout << endl;
  }
  return 0;
}
