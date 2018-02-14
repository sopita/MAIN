### Méthodes algorithmiques pour l'accès à l'information numérique

##### Compile :

```
cd src
make
```

##### Example of execution :
```
./pagerank -eps 0.0001 -zap 0.15 graph.txt --is_sorted
```

The option **-eps** is the accuracy of the calculation of pagerank algorithm.

The option **-zap** is the dumping factor.

The option **--is_sorted** is in case where the graph is already sorted.

>If you put the option --is_sorted and the file has not been activated, the comportment of the program is undetermined.

**By default** the program will sort the graph given as option and make a new file called *copi_graph.txt*.

>You can re-use this file in the future with the option --is_sorted.

<hz/>

>**Note** : The Sparse Matrix that we have implemented doesn't work with a file who hasn't been sorted. (The complexity will increase otherwhere)

##### **Test on given examples**
* f1g1 = correct
* n3e4 = correct
* n4e4 = correct
* n4e5 = correct
* n4e6 = correct
* n4e7 = correct
* n4e7t = correct
* n35e83 = Doesn't seens good

*We think we have some small error that get bigger when there is more nodes in the graph.*
