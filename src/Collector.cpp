#include "Collector.hpp"

Collector::Collector(string name)
{
  this->file.open(name);

  if(!this->file.is_open()){
    throw string("Name file given doesn't exist");
  }
}

void remove_duplicates(std::vector<string>& vec)
{
  std::sort(vec.begin(), vec.end()); //Performs approximately N*log2(N) (where N is this distance) comparisons of elements, and up to that many element swaps (or moves)
  vec.erase(std::unique(vec.begin(), vec.end()), vec.end()); //For non-empty ranges, linear in one less than the distance between first and last: Compares each pair of consecutive elements, and possibly performs assignments on some of them.
}

Article* Collector::getNewArticle()
{

  if(!this->file.is_open()){
    throw string("Source file doesn't exist (use initCollector)");
  }

  string line;
  int nb_categorie(0);
  Article *current_article = new Article(-1); // Need a more proper maner
  long int id;

  while(!this->file.eof()){

    getline(this->file, line);

    if(nb_categorie > 0) {
      --nb_categorie;
      replace(line.begin(), line.end(), '|', ' ');
      regex e (REGEX);
      stringstream ssin(regex_replace(line, e,"",std::regex_constants::match_not_null));
      do
      {
        for (string word; ssin >> word;) {
          if(word.length() > 1)
            current_article->getWords().push_back(word);
        }
        if (ssin.fail())
        {
            ssin.clear();
            std::string token;
            ssin >> token;
        }
      }
      while (!ssin.eof());

      remove_duplicates(current_article->getWords());

      if(nb_categorie == 0) {
        return current_article;
      }
    }

    if(line.compare(0, 3, "Id:") == 0){
      id = stol(line.substr(6));
      current_article->setId(id);
    }

    if(line.size() > 6 && line.compare(2, 6, "title:") == 0){
      regex e ("[^\\w||\\ ]");

      stringstream ssin(regex_replace(line.substr(9), e, ""));

      do
      {
        for (string word; ssin >> word;) {
          if(word.length() > 1)
            current_article->getWords().push_back(word);
        }
        if (ssin.fail())
        {
            ssin.clear();
            std::string token;
            ssin >> token;
        }
      }
      while (!ssin.eof());

    }

    if(line.size() > 11 && line.compare(2, 11, "categories:") == 0){
      nb_categorie = stol(line.substr(14));
      if(nb_categorie == 0) {
        return current_article;
      }
    }
  }
  delete current_article;
  return nullptr; // Not nice
}
