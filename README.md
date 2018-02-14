# Méthodes algorithmiques pour l'accès à l'information numérique

compile :
cd src
make

Ex: ./pagerank -eps 0.0001 -zap 0.15 graphe.txt --is_sorted


The option -eps is the position of the PageRank.

The option -zap is the dumping factor.

The option --is_sorted is in case where the graph has already been sorted by the programme.
By default the programme will do a sort of the graphe.txt and make a new file called copi_graph.txt.
You can reuse this file in the future with the option --is_sorted.
If you put the option --is_sorted and the file has not been activated, the comportment of the programme is undetermined.


Note: 
The Sparse Matrix that we have implemented doesn't work with a file who hasn't been sorted. (The complexity will increase otherwhere)



f1g1 = correct (near)
n3e4 = correct (near)
n4e4 = correct (near)
n4e5 = correct (near)
n4e6 = correct (near)
n4e7 = correct (near)
n4e7t = correct (near)
n35e83 = Wrong

I think we have some small error that get bigger when there is more nodes in the graph.
