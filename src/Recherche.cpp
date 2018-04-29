#include "Recherche.hpp"

using namespace std;

Recherche::Recherche(string recherche,string dict_to_exclude){
    //INIT collector from the json file.
    cout << "Starting to load the collector\n";
    Collector::loadJson("collector.json", this->collector);
    cout << "Collector load\n";
    /*
     **INIT the pagerank from a json file
     **THIS CUMPUTE WOULDN'T HAVE NEED IF Cli::loadJson HAD RETURNED A MAP
    */
    cout << "Starting to load the pagerank\n";
    std::vector<pair<long, float>> pagerank;
    Cli::loadJson("pagerank.json", pagerank);
    for (const pair<long, float> &edge : pagerank) {
        this->pagerank[edge.first]=edge.second;
    }
    cout << "Pagerank load\n";
    
    //INIT the recherche set.
    ifstream search_file;
    search_file.open(recherche);
    if(!search_file.is_open()){
        perror("open");
        exit(EXIT_FAILURE);
    }
    string line;
    while(!search_file.eof()){
        getline(search_file, line);
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        this->recherche.insert(line);
    }
    search_file.close();
    cout << "Recherche vector created\n";
    //INIT the set of article to exclude.
    ifstream file;
    file.open(dict_to_exclude);
    if(!file.is_open()){
        perror("open");
        exit(EXIT_FAILURE);
    }
    while(!file.eof()){
        getline(file, line);
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        set<long> * articles_exclude =collector[line];
        if(articles_exclude!=nullptr){
            this->id_exclude_article.insert(articles_exclude->begin(),articles_exclude->end());
        }
    }
    file.close();
   /* cout << "exlude article set created\n";
    for(auto id : this->id_exclude_article){
        cout << id <<",\n";
    }*/
    for(auto str: this->recherche){
        cout << str << endl;
    }
}

void Recherche::compute_result(){
    /*Represente the id of a article and
    the number of word who have found with the research.*/
    unordered_map<long, int> articles_res;
    for(auto str_searched : this->recherche){
        cout << str_searched << endl;
        set<long> * articles =collector[str_searched];
        if(articles==nullptr)
            continue;
        for ( auto id : *articles) {
            //If is not a exclude article
            if(this->id_exclude_article.find(id)==this->id_exclude_article.end()){
                //if it's the first time that a article have matched.
                if(articles_res.find(id)==articles_res.end()){
                    articles_res[id]=1;
                }
                //if we have already match with this article.
                else{
                    articles_res[id]=articles_res[id]+1;
                }
            }
        }
    }
    map<float, long> article_with_nb_word[this->recherche.size()];
    for(auto it : articles_res){
        float score=this->pagerank[it.first];
        article_with_nb_word[it.second][score]=it.first;
    }
    for(int i=0;i<this->recherche.size();i++){
        cout << "---------------------" << i+1 << " Words found"<< "---------------------" << endl;
        for (auto id : article_with_nb_word[i]){
            cout << id.second<< "-> "<< id.first << endl;
        }
    }
}

int main(int args,char * argv[]){
    if(args<3){
        cout << "Ex: ./recherche dict-exclus.txt liste-de-motsv" << endl;
        return 0;
    }
    Recherche recherche=Recherche(argv[1], argv[2]);
    recherche.compute_result();
    return 0;
}
