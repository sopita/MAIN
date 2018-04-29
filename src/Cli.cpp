#include "Cli.hpp"

unsigned int Cli::getNbNode() {
    return nb_node;
}

vector<Unitval*> & Cli::getC() {
    return c;
}

vector<int> & Cli::getL() {
    return l;
}

vector<int> & Cli::getI() {
    return i;
}

vector<float> & Cli::getRanking() {
    return ranking;
}

vector<float> Cli::produit_transpose(vector<float> x, float zap) {
    vector<float> y;
    //init y
    for(size_t i = 0; i < this->nb_node; i++){
        y.push_back(0);
    }
    //calcule y
    for(size_t i = 0; i < this->nb_node; i++) {
        for(int j = this->getL()[i]; j < this->getL()[i+1]; j++) {
            y[this->getI()[j]] += this->getC()[j]->get_valLine() * x[i];
        }
    }
    //calcule Zap
    for (size_t i = 0; i < y.size(); i++) {
        y[i] = (zap/this->nb_node) + ((1.0-zap) * y[i]);
    }

    return y;
}

void Cli::pagerank(float d, float e) {
    for (size_t i = 0; i < this->nb_node; i++) {
        this->ranking.push_back(1.0/nb_node);
    }

    vector<float> tmp = this->produit_transpose(this->ranking, d);

    while(check_if_continue(tmp, e)) {
        this->ranking = tmp;

        tmp = this->produit_transpose(this->ranking, d);
    }
}

bool Cli::check_if_continue(vector<float> r, float e) {
    float mv = 0.0;

    for (size_t i = 0; i < this->nb_node; i++) {
        mv += abs(r[i] - this->ranking[i]);
    }

    return (mv > e);
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

    cout << endl;
}

void Cli::loadJson(const char * path, unordered_map<long, float> & pagerank){
  std::ifstream i(path);
  if (!i.fail()) {
    json j;
    i >> j;

    for(unsigned int i = 0; i < j.size(); i++)
      pagerank[j[i]["id"]] = j[i]["value"];

  }
}
