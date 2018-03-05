#include <vector>
#include <string>
using namespace std;

class Article {
public:
  Article():id(-1){};
  Article(long int);
  long int getId();
  void setId(long int);
  vector<string>& getWords();
private:
  long int id;
  vector<string> words;
};
