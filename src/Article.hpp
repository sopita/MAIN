#include <vector>
#include <string>
using namespace std;

class Article {
public:
  long getId();
  vector<string> getWords();
private:
  long id;
  vector<string> words;
};
