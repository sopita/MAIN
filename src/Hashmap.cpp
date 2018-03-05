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
    
    try{
        Collector collec(md);
        Article * article;
        for (std::vector<std::string>::iterator it = dicts.begin() ; it !=dicts.end(); ++it){
            this->add_dictionnary(*it);
        }
        this->delete_dict(exclude_dict);
        std::string lower_tmp;
        while ((article=collec.getNewArticle())!=nullptr) {
            vector<string>& words(article->getWords());
            for(std::vector<std::string>::iterator it=words.begin();it !=words.end(); ++it){
                lower_tmp.resize(it->size());
                std::transform(it->begin(), it->end(), lower_tmp.begin(), ::tolower);
                auto search=map.find(lower_tmp);
                if(search!=map.end()){
                    search->second->push_back(article->getId());
                }
            }
        }
    }
    catch (const exception& e) {
        cerr << e.what();
        exit(EXIT_FAILURE);
    }
    ofstream fic("/Volumes/DD2/Master2/MAIN/MAIN/test_output.txt");
    if(!fic.is_open()){
        perror("open");
        exit(EXIT_FAILURE);
    }
    unordered_map<std::string, vector<long> *>:: iterator itr;
    for (itr=map.begin(); itr!=map.end(); itr++){
        if(itr->second->size()>0){
            cout << itr->first << ": " << *(itr->second);
            fic << itr->first << ": "<< *(itr->second);
        }
        //cout << itr->first << ": " << *(itr->second);
    }
    fic.close();
}

int main(){
    Hashmap map;
    /*map.add_dictionnary("/Volumes/DD2/Master2/MAIN/MAIN/src/test.txt");
    map.show_map();
    map.add_dictionnary("/Volumes/DD2/Master2/MAIN/MAIN/src/test.txt");
    map.show_map();
    map.delete_dict("/Volumes/DD2/Master2/MAIN/MAIN/src/test.txt");
    map.show_map();*/
    std::vector<std::string> dics;
    dics.push_back("/Volumes/DD2/Master2/MAIN/MAIN/google-10000-english.txt");
    map.create_collector("/Volumes/DD2/Master2/MAIN/MAIN/amazon-small.txt", dics, "/Volumes/DD2/Master2/MAIN/MAIN/src/test.txt");
    return 0;
}