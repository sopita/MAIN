### Méthodes algorithmiques pour l'accès à l'information numérique

## **For more details see the Rapport file**

### Execute all
You can change every argument in the script.
```
cd src
./script
```

### __Compile__

```
cd src
make
```

### Test Json

Json library used : https://github.com/nlohmann/json
Before launching **test_load_collector** or **test_load_pagerank** you need to build json files.
(with **./pagerank** and **./collector**).

### __PageRank__

#### Example of execution
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

#### **Test on given examples**
* f1g1 = correct
* n3e4 = correct
* n4e4 = correct
* n4e5 = correct
* n4e6 = correct
* n4e7 = correct
* n4e7t = correct
* n35e83 = Doesn't seems good

*We think we have some small error that get bigger when there is more nodes in the graph.*

### __Collector__

#### Example of execution
```
./collector metadatas.txt dict0.txt dict1.txt dics2.txt exclude_dict.txt
```

The argument **metadatas.txt** is a file that contains datas that the program will work on. (here this is the amazon-meta file)

The arguments **dict[0-2]** are files that contains dictionaries on which will be indexed the content of the metadatas file.

The argument **exclude_dict.txt** is a file that contains words that will be excluded from the dictionaries.

**To parse the file given in argument, we tried two ways :**
  * The first one was to use regex expression
  * The second one was to do it without regex

### REGEX

**We encountered a lot of problem with regex, the main one is a huge preformance issue.**
**Indeed, for the big amazon-meta file, the execution time is no less than 20 minutes.**

#### Problems encountered

* **Regex expression problem**

We have a problem with regex, indeed some regex expression that works on linux and Windows, doesn't work on macOS.

We have this problem only when we want to catch  **__categories__ of amazon-meta** file with this regex expression :
```
regex e ("[^\\[a-zA-Z ]||\\[||\\]]");
```
**then we replace it with :**
```
regex e (R"([\\-,;:](\\[.*?\\]||&))||(\\[.*?\\]||&)");
```

>**Important** : If you use a Linux or Windows then replace this regex expression with the first one which is more specific.

* **Another regex problem**

>It seems that on MAC **we need** to put a ***R*** before a regex expression.

>The problem is that on Linux and Windows, with this ***R*** symbol the program doesn't work anymore.

**So that's why we choose to put some macros :**

```
/****
  A BETTER REGEX BUT WORKING ONLY ON WIN AND LINUX
  "[^\\[a-zA-Z ]||\\[||\\]]"
****/

#if defined(_WIN32) || defined(__linux__)
  #define REGEX "([\\-,;:](\\[.*?\\]||&))||(\\[.*?\\]||&)"
#elif __APPLE__
  #define REGEX R"([\\-,;:](\\[.*?\\]||&))||(\\[.*?\\]||&)"
#endif
```

**Due to the huge performance issue we talked about, we prefered to give up using regex.**
**Right now the execution time is less than 2 minutes.**

### __Recherche__

#### Example of execution
```
./recherche dict-exclus.txt liste-de-motsv
```
