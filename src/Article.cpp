#include "Article.hpp"

Article::Article(long int id_art): id(id_art) {}

void Article::setId(long int id)
{
  this->id = id;
}

long int Article::getId()
{
  return id;
}

vector<string>& Article::getWords()
{
  return words;
}
