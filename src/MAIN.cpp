#include "Read_Graph.hpp"
#include "Cli.hpp"
#include <string.h>
#include <map>

void get_map_nodes(map<int, bool> & map, const char * path, bool is_sorted)
{
    
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
    
    if(nodes.empty()){
        cout << "empty File\n";
        exit(EXIT_SUCCESS);
    }
    
    Cli * matrix = new Cli(nodes.size());
    
    Read_graph graph(path, is_sorted);
    int nb_child(0);
    pair<int, int> * p = graph.get_edge();
    int actual_node(p->first);
    Unitval * val=new Unitval();
    matrix->get_l().push_back(0);
    map<int,bool>::iterator it=nodes.begin();
    do{
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
            tmp_l.push_back(tmp_l.back() + nb_child);
            nb_child = 1;
            matrix->get_c().push_back(val);
            matrix->get_i().push_back(p->second);
            ++it;
        }
        
        
        while(p->first != it->first) {
            vector<int> & tmp_l(matrix->get_l());
            tmp_l.push_back(tmp_l.back());
            ++it;
        }
        
    } while ((p = graph.get_edge()));
    
    vector<int> & tmp_l(matrix->get_l());
    tmp_l.push_back(tmp_l.back() + nb_child);
    val->set_valLine(1.0/nb_child);
    
    //Add the node that not have any edges.
    while(++it!=nodes.end()) {
        vector<int> & tmp_l(matrix->get_l());
        tmp_l.push_back(tmp_l.back() + 0);
    }
    
    return matrix;
}

int main(int argc, char const *argv[])
{
    if(argc >= 6){
        float epsilon(0);
        float zap(0);
        
        if(!strcmp(argv[1], "-eps")) {
            epsilon = stof(argv[2]);
        }
        else if(!strcmp(argv[1], "-zap")) {
            zap = stof(argv[2]);
        }
        if(!strcmp(argv[3], "-eps")) {
            epsilon = stof(argv[4]);
        } else if(!strcmp(argv[3], "-zap")) {
            zap = stof(argv[4]);
        }
        bool is_sorted = (argc>=7 &&  !strcmp(argv[6], "--is_sorted")) ? true : false;
        Cli * cli = make_cli(argv[5], is_sorted);
        cli->print_cli();
        cli->pagerank(zap, epsilon);
    }
    else {
        cout << "Ex: ./pagerank -eps 0.0001 -zap 0.15 graphe.txt --is_sorted\n";
    }
    return 0;
}
