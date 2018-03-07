
all:
	make pagerank
	make collector

pagerank: pagerank.cpp Read_Graph.cpp Cli.cpp Unitval.cpp
	g++ -Wall pagerank.cpp Read_Graph.cpp Cli.cpp Unitval.cpp -o pagerank

collector: Article.cpp Collector.cpp Hashmap.cpp
	g++ -Wall Article.cpp Collector.cpp Hashmap.cpp -o collector

clean:
	find . -maxdepth 1 -type f ! -name "*.cpp" ! -name "*.hpp" ! -name "*.sh" ! -name "Makefile" -delete
