#include "Cli.hpp"

unsigned int Cli::get_nb_node() {
    return nb_node;
}

vector<Unitval*> & Cli::get_c() {
    return c;
}

vector<int> & Cli::get_l() {
    return l;
}

vector<int> & Cli::get_i() {
    return i;
}

vector<float> Cli::produit_transpose(vector<float> x, float zap) {
    vector<float> y;
    //init y
    for(size_t i = 0; i < this->nb_node; i++){
        y.push_back(0);
    }
    //calcule y
    for(size_t i = 0; i < this->nb_node; i++) {
        for(int j = this->get_l()[i]; j < this->get_l()[i+1]; j++) {
            y[this->get_i()[j]] += this->get_c()[j]->get_valLine() * x[i];
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
    
    cout << "Initial R: ";
    for (vector<float>::iterator it = this->ranking.begin() ; it != this->ranking.end(); ++it)
        cout << (*it) << " ";
    
    cout << endl;
    
    vector<float> tmp = this->produit_transpose(this->ranking, d);
    
    while(check_if_continue(tmp, e)) {
        this->ranking = tmp;
        
        cout << "R: ";
        for (vector<float>::iterator it = this->ranking.begin() ; it != this->ranking.end(); ++it)
            cout << (*it) << '\t';
        
        cout << endl;
        
        tmp = this->produit_transpose(this->ranking, d);
    }
}

bool Cli::check_if_continue(vector<float> r, float e) {
    float mv = 0.0;
    
    for (size_t i = 0; i < this->nb_node; i++) {
        mv += abs(r[i] - this->ranking[i]);
    }
    cout << "difference avec precedant R : " << mv << endl;
    
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
