//
//  Read_Graph.hpp
//  Project_Main
//
//  Created by andres quiroz on 12/02/2018.
//  Copyright © 2018 andres quiroz. All rights reserved.
//

#ifndef Read_Graph_hpp
#define Read_Graph_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sstream>
#include <sys/wait.h>

using namespace std;

class Read_graph{
public:
    pair<int,int> * get_edge();
    Read_graph(const char * path,bool is_sorted);
    virtual ~Read_graph();
private:
    pair<int, int> edge;
    ifstream graph;
};

#endif /* Read_Graph_hpp */
