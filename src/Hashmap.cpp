#include "Hashmap.hpp"

void Hashmap::put(const std::string key){
    auto search = map.find(key);
    if(search==map.end()){
        map[key]=new std::set<long>();
    }
    else{
        cout << "Not put\n";
    }
}

std::set<long> * Hashmap::get(std::string key){
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
    unordered_map<string, set<long> *>:: iterator itr;
    for (itr=map.begin(); itr!=map.end(); itr++){
        cout << itr->first << "  " << itr->second->size() << endl;
    }

}


void Hashmap::create_collector(std::string md,std::vector<std::string> & dicts,std::string exclude_dict){
    Collector collec(md);
    for (std::vector<std::string>::iterator it = dicts.begin() ; it !=dicts.end(); ++it){
        this->add_dictionnary(*it);
    }
    this->delete_dict(exclude_dict);
    std::string lower_tmp;
    collec.getArticleWords(map);

    ofstream fic("output.txt",ios::trunc | ios::out);
    if(!fic.is_open()){
        perror("open");
        exit(EXIT_FAILURE);
    }

    unordered_map<std::string, std::set<long> *>:: iterator itr;
    std::set<long>::iterator set_it;

    for (itr=map.begin(); itr!=map.end(); itr++){
        fic << itr->first << ": "; 
        for (set_it = itr->second->begin(); set_it != itr->second->end(); ++set_it){
            fic << *set_it << ", ";
        }
        fic << endl;
    }
    fic.close();
    cout << "the output file has been created: output.txt\n";
}

Hashmap::~Hashmap(){
    unordered_map<string, set<long> *>:: iterator itr;
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
