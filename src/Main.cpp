#include "Read_Graph.hpp"
#include "Cli.hpp"
#include <string>

Cli * make_cli(const char * path, bool is_sorted){

  Cli * matrix = new Cli();
  Read_graph graph(path, is_sorted);
  int nb_child(0);
  pair<int, int> * p = graph.get_edge();
  int actual_node(p->first);
  Unitval * val=new Unitval();
  matrix->get_l().push_back(0);

  do {

    cout << "P : " << p->first << " " << p->second << endl;

    if(p->first == actual_node){
      nb_child++;
      matrix->get_c().push_back(val);
      matrix->get_i().push_back(p->second);
    } else{
      val->set_valLine(1.0/nb_child);
      actual_node = p->first;
      val = new Unitval();
      vector<int> & tmp_l(matrix->get_l());
      matrix->get_l().push_back(tmp_l.back() + nb_child);
      nb_child = 1;
      matrix->get_c().push_back(val);
      matrix->get_i().push_back(p->second);
    }

  } while ((p = graph.get_edge()));

  vector<int> & tmp_l(matrix->get_l());
  matrix->get_l().push_back(tmp_l.back() + nb_child);
  val->set_valLine(1.0/nb_child);

  return matrix;
}


int main(int argc, char const *argv[]) {
  //Read_graph graph("../examples/tp1-fig1.txt", 0);
  //pair<int, int> * p = graph.get_edge();
  //std::cout << p->first << "\t" << p->second << std::endl;
  make_cli("../examples/fig_cour.txt", 0)->print_cli();
  return 0;
}
