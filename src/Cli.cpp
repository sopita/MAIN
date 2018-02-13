#include "Cli.hpp"

vector<float> Cli::produit_direct(Cli & sparse_matrix, vector<int> x) {
  vector<float> y;
  for(int i = 0; i < sparse_matrix.get_nb_node(); i++) {
    y[i] = 0;
    for(int k = sparse_matrix.get_l()[i]; k < sparse_matrix.get_l()[i+1]; k++) {
      //y[i] += sparse_matrix.get_c()[k]->get_valLine() * x[sparse_matrix.get_i()[k]];
    }
  }

  return y;
}

vector<float> Cli::produit_transpose(Cli & sparse_matrix, vector<int> x) {
  vector<float> y;
  for(int i = 0; i < sparse_matrix.get_nb_node(); i++) y[i] = 0;
  for(int i = 0; i < sparse_matrix.get_nb_node(); i++) {
    for(int j = sparse_matrix.get_l()[i]; j < sparse_matrix.get_l()[i+1]; j++) {
      //y[sparse_matrix.get_i()[j]] += sparse_matrix.get_c()[j]->get_valLine() * x[i];
    }
  }

  return y;
}

void Cli::print_cli() {
    cout << "C: ";
    for (vector<Unitval*>::iterator it = c.begin() ; it != c.end(); ++it)
      cout << (*it)->get_valLine() << " ";

    cout << endl << "L: ";
    for (vector<int>::iterator it = l.begin() ; it != l.end(); ++it)
      cout << (*it) << " ";

    cout << endl << "I: ";
    for (vector<int>::iterator it = i.begin() ; it != i.end(); ++it)
      cout << (*it) << " ";
}
