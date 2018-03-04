#include <iostream>
#include <fstream>
#include <string>
#include <map>

class infos{
  public:
    int nb_id = 0;
    std::map <std::string, int> groups;
};

class article{
  int id;
}

int main(int argc, char const *argv[])
{
  infos * info_graphe = new infos();
  std::string line;

  if(argc != 2)
  {
    std::cout << "usage: ./stats file" << std::endl;
    return 1;
  }

  std::ifstream source(argv[1]);

  if(!source.is_open()){
    std::cout << "Fichier n'existe pas" << std::endl;
    return 1;
  }

  while(std::getline(source, line))
  {
    if(line.compare(0, 2, "Id") == 0){
      info_graphe->nb_id++;
    }
    if(line.size() > 6 && line.compare(2, 5, "group") == 0){
      if(info_graphe->groups.find(line.substr(9)) != info_graphe->groups.end()){
        std::map<std::string, int>::iterator it = info_graphe->groups.find(line.substr(9));
        if(it != info_graphe->groups.end()){
          it->second += 1;
        }
      } else {
	      info_graphe->groups.insert(std::pair<std::string, int>(line.substr(9), 1));
      }
    }
  }

  std::cout << info_graphe->nb_id << std::endl;

  std::map<std::string, int>::iterator it = info_graphe->groups.begin();

  while (it != info_graphe->groups.end())
  {
  	std::string word = it->first;

  	int count = it->second;

  	std::cout << word << "\t\t" << count << std::endl;

  	it++;
  }

  source.close();
  return 0;
}
