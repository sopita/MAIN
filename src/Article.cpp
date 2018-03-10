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

 std::unordered_map<std::string,int>& Article::getWords()
{
    return words;
}
