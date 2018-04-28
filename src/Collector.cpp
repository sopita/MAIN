#include "Collector.hpp"
#include "../include/json.hpp"

using json = nlohmann::json;

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

void Collector::getArticleWords(){
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
            getTokensAndStore(line, id);
        }

        if(line.size() > 11 && line.compare(2, 11, "categories:") == 0){
            nb_categories = stol(line.substr(14));
            for(int i=0;i < nb_categories; i++){
                getline(this->file, line);
                getTokensAndStore(line, id);
            }
        }
    }
    cout << "End\n";
}

/**
As you can imagine the function below is not from me
**/

std::string Collector::str_tolower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),[](unsigned char c){
      return std::tolower(c);
    });
    return s;
}

void Collector::getTokensAndStore(const string &s, long id)
{

  for (std::string::iterator it = str_delimiters.begin(); it != str_delimiters.end(); ++it) {
    dict[(int)*it] = true;
  }

  std::string token("");
  for(auto &i : s) {
    if(dict[(int)i]) {
      if(!token.empty()) {
        token = str_tolower(token);
        auto search = mot_produits.find(token);
        if(search!=mot_produits.end()){
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
    auto search=mot_produits.find(token);
    if(search!=mot_produits.end()){
      search->second->insert(id);
    }
  }
}

void Collector::put(const std::string key){
    auto search = mot_produits.find(key);
    if(search==mot_produits.end()){
        mot_produits[key]=new std::set<long>();
    }
    else{
        cout << "Not put\n";
    }
}

std::set<long> * Collector::getArticleIds(std::string key){
    return this->mot_produits[key];
}

void Collector::delete_dict(std::string dict){
    std::ifstream ifs(dict, std::ifstream::in);
    if(!ifs.is_open()){
        perror("open:");
        exit(EXIT_FAILURE);
    }
    for(std::string word; ifs >> word; ){
        auto search = mot_produits.find(word);
        if(search!=mot_produits.end()){
            delete search->second;
            mot_produits.erase(word);
        }
        else{
            cout << "elem not found\n";
        }
    }
    ifs.close();
}

void Collector::add_dictionnary(std::string dict){
    std::ifstream ifs(dict, std::ifstream::in);
    if(!ifs.is_open()){
        perror("open:");
        exit(EXIT_FAILURE);
    }
    for(std::string word; ifs >> word; ){
        put(word);
    }
    ifs.close();
}

void Collector::show_map(){
    unordered_map<string, set<long> *>:: iterator itr;
    for (itr=mot_produits.begin(); itr!=mot_produits.end(); itr++){
        cout << itr->first << "  " << itr->second->size() << endl;
    }

}


void Collector::create_collector(std::vector<std::string> & dicts,std::string exclude_dict){
    for (std::vector<std::string>::iterator it = dicts.begin() ; it !=dicts.end(); ++it){
        this->add_dictionnary(*it);
    }
    this->delete_dict(exclude_dict);
    std::string lower_tmp;
    getArticleWords();

    unordered_map<std::string, std::set<long> *>:: iterator itr;
    std::set<long>::iterator set_it;
    json j;
    for (itr=mot_produits.begin(); itr!=mot_produits.end(); itr++){
        for (set_it = itr->second->begin(); set_it != itr->second->end(); ++set_it){
             j[itr->first]  += *set_it;
        }
    }

    std::ofstream o("collector.json");
    o << std::setw(4) << j << std::endl;

    cout << "the output file has been created: collector.json\n";
}

Collector::~Collector(){
    unordered_map<string, set<long> *>:: iterator itr;
    for (itr=mot_produits.begin(); itr!=mot_produits.end(); itr++){
        delete itr->second;
    }
}

void Collector::loadJson(const char * path, unordered_map<string, set<long> *> & motProduits){
  std::ifstream i(path);

  if (!i.fail()) {
    json j;
    i >> j;

    for (json::iterator it = j.begin(); it != j.end(); ++it) {
      motProduits[it.key()]=new std::set<long>();
      for(long l: it.value()) {
        motProduits.find(it.key())->second->insert(l);
      }
    }
  }
}
