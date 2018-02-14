//
//  Read_Graph.cpp
//  Project_Main
//
//  Created by andres quiroz on 12/02/2018.
//  Copyright © 2018 Andres Quiroz . All rights reserved.
//

#include "Read_Graph.hpp"

Read_graph::Read_graph(const char * path,bool is_sorted):edge(1,10){
    int pid;
    if(!is_sorted){
        int pipefd[2];
        long len;
        char * buf=new char[PATH_MAX];
        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        switch ( pid = fork() ) {
            case -1:
                perror("fork");
                exit(EXIT_FAILURE);
            case 0:
                close(pipefd[0]);

                if(dup2(pipefd[1],1)<0){
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }

                if(execl("sort_graph.sh", "sort_graph.sh", path, NULL)<0){
                    perror("execlp");
                    exit(EXIT_FAILURE);
                }

            default:
                close(pipefd[1]);
                wait(NULL);
                len=read(pipefd[0], buf, PATH_MAX);
                if(len<0){
                    perror("read");
                    exit(EXIT_FAILURE);
                }
                close(pipefd[0]);
        }
        buf[len-1]='\0';

        graph.open((const char *)buf);
        delete[] buf;
    }

    else {
        graph.open((const char *)path);
    }
};

pair<int,int> * Read_graph::get_edge(){
    string line;
    stringstream ss;
    while(!graph.eof()){
        getline(graph,line);
        for(string::iterator it=line.begin(); it!=line.end(); ++it){
            if(*it=='\n' || *it=='#' || *it==' '){
                break;
            }
            ss << line;
            ss >> edge.first >> edge.second;
            return &edge;
        }
    }
    return nullptr;
}


Read_graph::~Read_graph(){
    //cout << "delete\n";
    graph.close();
}
