#ifndef Article_hpp
#define Article_hpp

#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class Article {
public:
    Article():id(-1){};
    Article(long int);
    long int getId();
    void setId(long int);
    std::unordered_map<std::string,int>& getWords();
private:
    long id;
    std::unordered_map<std::string,int> words;
};

#endif /* Article_hpp */