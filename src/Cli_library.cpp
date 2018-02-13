#include "Cli_library.hpp"

std::vector<float> Cli_library::produit_direct(Cli * sparse_matrix, std::vector<int> x) {
  std::vector<float> y;
  for(int i = 0; i < sparse_matrix->get_nb_node(); i++) {
    y[i] = 0;
    for(int k = sparse_matrix->get_l()[i]; k < sparse_matrix->get_l()[i+1]; k++) {
      y[i] += sparse_matrix->get_c()[k] * x[sparse_matrix->get_i()[k]];
    }
  }

  return y;
}

std::vector<float> Cli_library::produit_transpose(Cli * sparse_matrix, std::vector<int> x) {
  std::vector<float> y;
  for(int i = 0; i < sparse_matrix->get_nb_node(); i++) y[i] = 0;
  for(int i = 0; i < sparse_matrix->get_nb_node(); i++) {
    for(int j = sparse_matrix->get_l()[i]; j < sparse_matrix->get_l()[i+1]; j++) {
      y[sparse_matrix->get_i()[j]] += sparse_matrix->get_c()[j] * x[i];
    }
  }

  return y;
}
