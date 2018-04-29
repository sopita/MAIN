
all:
	make pagerank
	make collector
	make test_load_pagerank
	make test_load_collector
	make recherche
pagerank: pagerank.cpp Read_Graph.cpp Cli.cpp Unitval.cpp
	g++ -Wall pagerank.cpp Read_Graph.cpp Cli.cpp Unitval.cpp -o pagerank -std=c++11

collector: Article.cpp Collector.cpp Hashmap.cpp
	c++ -Wall Article.cpp Collector.cpp Hashmap.cpp -o collector -std=c++11

test_load_pagerank: Cli.cpp Unitval.cpp
	g++ test_load_pagerank.cpp Cli.cpp Unitval.cpp -o test_load_pagerank -std=c++11

test_load_collector: Collector.cpp
	g++ test_load_collector.cpp Collector.cpp -o test_load_collector -std=c++11

recherche: Recherche.hpp Recherche.cpp
	g++ Recherche.cpp Collector.cpp Cli.cpp Unitval.cpp -o recherche -std=c++11

clean:
	find . -maxdepth 1 -type f ! -name "*.cpp" ! -name "*.hpp" ! -name "*.sh" ! -name "Makefile" ! -name "*.txt" ! -name "*.json" -delete
