#!/bin/bash
make
#Graph
graph="../amazon0302.txt"
#Meta
meta="../amazon-meta.txt"
#Dict
dict="../google-10000-english.txt test.txt"
#Dict exclude
exclude="test.txt"
#research
research="search_test.txt"
research_exclude="test.txt"
./pagerank -eps 0.0001 -zap 0.15 $graph
./collector $meta $dict $exclude
./recherche $research $research_exclude
