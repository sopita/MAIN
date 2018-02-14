# MAIN
Méthodes algorithmiques pour l'accès à l'information numérique

compile : g++ Main.cpp Read_Graph.cpp Cli.cpp Unitval.cpp -o Main

launch : Main graph.txt

goal : pagerank -eps 0,001 -zap 0,13 graphe.txt

-eps : precision
-zap : zap factor

f1g1 = correct (near)
n3e4 = correct (near)
n4e4 = correct (near)
n4e5 = correct (near)
n4e6 = correct (near)
n4e7 = correct (near)
n4e7t = correct (near)
n35e83 = Wrong

When i say 'near', it means that what we get is similar to the result given until the third number after the comma.

I think we have some small error that get bigger when there is more nodes in the graph.
