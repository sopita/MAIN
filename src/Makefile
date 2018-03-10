
all:
	make pagerank
	make collector

pagerank: pagerank.cpp Read_Graph.cpp Cli.cpp Unitval.cpp
	g++ -Wall pagerank.cpp Read_Graph.cpp Cli.cpp Unitval.cpp -o pagerank -std=c++11

collector: Article.cpp Collector.cpp Hashmap.cpp
	c++ -Wall Article.cpp Collector.cpp Hashmap.cpp -o collector -std=c++11

clean:
	find . -maxdepth 1 -type f ! -name "*.cpp" ! -name "*.hpp" ! -name "*.sh" ! -name "Makefile" -delete
