#include "Read_Graph.hpp"
#include "Cli.hpp"
#include <string>
#include <map>

void get_map_nodes(map<int, bool> & map, const char * path, bool is_sorted) {

  Read_graph graph(path, is_sorted);
  pair<int, int> * p;

  while((p = graph.get_edge())) {
    map.insert(pair<int, bool>(p->first, false));
    map.insert(pair<int, bool>(p->second, false));
  }
}

Cli * make_cli(const char * path, bool is_sorted){
  //Noeud, Seen
  map<int, bool> nodes;
  get_map_nodes(nodes, path, is_sorted);

  Cli * matrix = new Cli(nodes.size());

  Read_graph graph(path, is_sorted);
  int nb_child(0);
  pair<int, int> * p = graph.get_edge();
  int actual_node(p->first);
  Unitval * val=new Unitval();
  matrix->get_l().push_back(0);
  map<int,bool>::iterator it=nodes.begin();

  do {

    if(p->first == actual_node){
      nb_child++;
      matrix->get_c().push_back(val);
      matrix->get_i().push_back(p->second);
      nodes.find(p->first);
    } else {
      val->set_valLine(1.0/nb_child);
      actual_node = p->first;
      val = new Unitval();
      vector<int> & tmp_l(matrix->get_l());
      matrix->get_l().push_back(tmp_l.back() + nb_child);
      nb_child = 1;
      matrix->get_c().push_back(val);
      matrix->get_i().push_back(p->second);
      ++it;
    }

    //cout << "Before while : " << p->first << " " << it->first << endl;

    while(p->first != it->first) {
      vector<int> & tmp_l(matrix->get_l());
      matrix->get_l().push_back(tmp_l.back() + 0);
      ++it;
    }

    /*cout << "After while : " << endl;
    cout << actual_node << endl;
    cout << p->first << " " << it->first << endl;*/

  } while ((p = graph.get_edge()));

  while(actual_node != it->first) {
    vector<int> & tmp_l(matrix->get_l());
    matrix->get_l().push_back(tmp_l.back() + 0);
    ++it;
  }

  vector<int> & tmp_l(matrix->get_l());
  matrix->get_l().push_back(tmp_l.back() + nb_child);
  val->set_valLine(1.0/nb_child);

  while(++it!=nodes.end()) {
    vector<int> & tmp_l(matrix->get_l());
    matrix->get_l().push_back(tmp_l.back() + 0);
  }

  return matrix;
}

int main(int argc, char const *argv[]) {
  Cli * cli = make_cli(argv[1], 0);
  cli->print_cli();
  cli->pagerank(0.15, 0.0001);
  return 0;
}
