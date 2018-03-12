#include "Hashmap.hpp"

void Hashmap::put(const std::string key){
    auto search = map.find(key);
    if(search==map.end()){
        map[key]=new std::vector<long>();
    }
    else{
        cout << "Not put\n";
    }
}

std::vector<long> * Hashmap::get(std::string key){
    return this->map[key];
}

void Hashmap::delete_dict(std::string dict){
    std::ifstream ifs(dict, std::ifstream::in);
    if(!ifs.is_open()){
        perror("open:");
        exit(EXIT_FAILURE);
    }
    for(std::string word; ifs >> word; ){
        auto search = map.find(word);
        if(search!=map.end()){
            delete search->second;
            map.erase(word);
        }
        else{
            cout << "elem not found\n";
        }
    }
    ifs.close();
}

void Hashmap::add_dictionnary(std::string dict){
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

void Hashmap::show_map(){
    unordered_map<string, vector<long> *>:: iterator itr;
    for (itr=map.begin(); itr!=map.end(); itr++){
        cout << itr->first << "  " << itr->second->size() << endl;
    }
    
}


void Hashmap::create_collector(std::string md,std::vector<std::string> & dicts,std::string exclude_dict){
    Collector collec(md);
    Article * article;
    for (std::vector<std::string>::iterator it = dicts.begin() ; it !=dicts.end(); ++it){
        this->add_dictionnary(*it);
    }
    this->delete_dict(exclude_dict);
    std::string lower_tmp;
    collec.getArticleWords(map);
    /*while ((article=collec.getNewArticle())!=nullptr) {
        std::unordered_map<std::string,int>& words(article->getWords());
        unordered_map<string, int>:: iterator itr;
        for (itr=words.begin(); itr!=words.end(); itr++){
            lower_tmp.resize(itr->first.size());
            std::transform(itr->first.begin(), itr->first.end(), lower_tmp.begin(), ::tolower);
            auto search=map.find(lower_tmp);
            if(search!=map.end()){
                search->second->push_back(article->getId());
            }
        }
        delete article;
    }*/
    ofstream fic("output.txt",ios::trunc | ios::out);
    if(!fic.is_open()){
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    unordered_map<std::string,std::vector<long> *>:: iterator itr;
    for (itr=map.begin(); itr!=map.end(); itr++){
        fic << itr->first << ": "<< *(itr->second);
    }
    fic.close();
    cout << "the output file has been created: output.txt\n";
}

Hashmap::~Hashmap(){
    unordered_map<string, vector<long> *>:: iterator itr;
    for (itr=map.begin(); itr!=map.end(); itr++){
        delete itr->second;
    }
}

int main(int args, char ** argv){
    if(args<4){
        cout << argv[0] <<"Ex: metadonne.txt dict0 dict1 dics2 exclude_dict\n";
        return 0;
    }
    std::vector<std::string> dicts;
    for(int i=2;i<args-1;i++){
        std::string tmp = argv[i];
        dicts.push_back(tmp);
    }
    Hashmap map;
    std::vector<std::string> dics;
    map.create_collector(argv[1], dicts, argv[args-1]);
    return 0;
}