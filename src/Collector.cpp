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
  Article *current_article = new Article(-1); // Pas fou
  long int id;

  while(!this->file.eof()){

    getline(this->file, line);

    if(nb_categorie > 0) {
      //cout << "(" << line.substr(3) << ")" << endl;
      --nb_categorie;
      replace(line.begin(), line.end(), '|', ' ');
      regex e (R"([\\-,;:](\\[.*?\\]||&))||(\\[.*?\\]||&)");
      //cout << regex_replace(line, e, "") << endl;
      //cout << "(" << line.substr(3) << ")" << endl;
      stringstream ssin(regex_replace(line, e,""));
      do
      {
        // read as many numbers as possible.
        for (string number; ssin >> number;) {
            current_article->getWords().push_back(number);
        }
        // consume and discard token from stream.
        if (ssin.fail())
        {
            ssin.clear();
            std::string token;
            ssin >> token;
        }
      }
      while (!ssin.eof());

      remove_duplicates(current_article->getWords());
      //cout << "size : " << current_article->getWords().size() << endl;

      if(nb_categorie == 0) {
        return current_article;
      }
    }

    if(line.compare(0, 3, "Id:") == 0){

      /*
      If no conversion could be performed, an invalid_argument exception is thrown.
      If the value read is out of the range of representable values by a long int,
      either an invalid_argument or an out_of_range exception is thrown.
      */

      //cout << "[" << line.substr(6) << "]" << endl;
      id = stol(line.substr(6));
      //cout << "--[" << line.substr(6) << "]--" << endl;
      current_article->setId(id);
    }

    if(line.size() > 6 && line.compare(2, 6, "title:") == 0){
      regex e ("[^\\w||\\ ]");   // matches words beginning by "sub"

      stringstream ssin(regex_replace(line.substr(9), e, ""));
      //stringstream ssin(line.substr(9));

      do
      {
        // read as many numbers as possible.
        for (string number; ssin >> number;) {
            current_article->getWords().push_back(number);
        }
        // consume and discard token from stream.
        if (ssin.fail())
        {
            ssin.clear();
            std::string token;
            ssin >> token;
        }
      }
      while (!ssin.eof());

      //cout << "size : " << current_article->getWords().size() << endl;
    }

    if(line.size() > 11 && line.compare(2, 11, "categories:") == 0){
      //cout << "<" << line.substr(14) << ">" << endl;
      nb_categorie = stol(line.substr(14));
      if(nb_categorie == 0) {
        return current_article;
      }
      //cout << "--<" << line.substr(14) << ">--" << endl;
    }
  }
  delete current_article;
  return nullptr; //Pas très beau (faire une exception)
}
