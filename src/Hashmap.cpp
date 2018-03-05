#include "Hashmap.hpp"

void Hashmap::put(const std::string key){
    auto search = map.find(key);
    if(search==map.end()){
        map[key]=new std::vector<int>();
    }
    else{
        cout << "Not put\n";
    }
}

std::vector<int> * Hashmap::get(std::string key){
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
    unordered_map<string, vector<int> *>:: iterator itr;
    for (itr=map.begin(); itr!=map.end(); itr++){
        cout << itr->first << "  " << itr->second->size() << endl;
    }

}

void Hashmap::create_collector(std::string md,std::vector<std::string> & dicts,std::string exclude_dict){
    for (std::vector<std::string>::iterator it = dicts.begin() ; it !=dicts.end(); ++it){
        this->add_dictionnary(*it);
    }
    this->delete_dict(exclude_dict);
}

int main(){
    Hashmap map;
    map.add_dictionnary("/Volumes/DD2/Master2/MAIN/MAIN/src/test.txt");
    map.show_map();
    map.add_dictionnary("/Volumes/DD2/Master2/MAIN/MAIN/src/test.txt");
    map.show_map();
    map.delete_dict("/Volumes/DD2/Master2/MAIN/MAIN/src/test.txt");
    map.show_map();
    return 0;
}