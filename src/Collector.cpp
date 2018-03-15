#include "Collector.hpp"

Collector::Collector(string name): str_delimiters(DELIMITERS)
{
    this->file.open(name);
    if(!this->file.is_open()){
        perror("open");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < CHAR_MAX_VAL; i++) {
      dict[i] = false;
    }
}

void Collector::getArticleWords(std::unordered_map<std::string,std::set<long> *> & map){
    long id;
    int nb_categories;
    std::string line;
    std::string tmp;
    cout << "Start parsing\n";
    while(!this->file.eof()){

        getline(this->file, line);

        if(line.size() > 3 && line.compare(0, 3, "Id:") == 0){
            id = stol(line.substr(6));
        }

        if(line.size() > 6 && line.compare(2, 6, "title:") == 0){
            tmp=line.substr(9);
            getTokensAndStore(line, map, id);
        }

        if(line.size() > 11 && line.compare(2, 11, "categories:") == 0){
            nb_categories = stol(line.substr(14));
            for(int i=0;i < nb_categories; i++){
                getline(this->file, line);
                getTokensAndStore(line, map, id);
            }
        }
    }
    cout << "End\n";
}

/**
As you can imaine the function below is not from me
**/

std::string Collector::str_tolower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),[](unsigned char c){
      return std::tolower(c);
    });
    return s;
}

void Collector::getTokensAndStore(const string &s, std::unordered_map<std::string,std::set<long> *> & map, long id)
{

  for (std::string::iterator it = str_delimiters.begin(); it != str_delimiters.end(); ++it) {
    dict[(int)*it] = true;
  }

  std::string token("");
  for(auto &i : s) {
    if(dict[(int)i]) {
      if(!token.empty()) {
        token = str_tolower(token);
        auto search = map.find(token);
        if(search!=map.end()){
          search->second->insert(id);
        }

        token.clear();
      }
    } else {
      token += i;
    }
  }
  if(!token.empty()) {
    token = str_tolower(token);
    auto search=map.find(token);
    if(search!=map.end()){
      search->second->insert(id);
    }
  }
}
