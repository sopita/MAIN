#include "Collector.hpp"

Collector::Collector(string name)
{
    this->file.open(name);
    if(!this->file.is_open()){
        perror("open");
        exit(EXIT_FAILURE);
    }
    std::vector<char> tmp {'.','[',']','(',')',',','?','&','|',':'};
    for(unsigned int i=0; i < tmp.size(); i++){
        this->punctuation_to_delete[tmp[i]]=' ';
    }
}

void Collector::getArticleWords(std::unordered_map<std::string,std::set<long> *> & map){
    long id;
    int nb_categories;
    std::string line;
    std::string tmp;
    cout << "Start parsing\n";
    while(!this->file.eof()){

        getline(this->file, line);

        if(line.size() > 3 && line.compare(0, 3, "Id:") == 0){
            id = stol(line.substr(6));
        }

        if(line.size() > 6 && line.compare(2, 6, "title:") == 0){
            tmp=line.substr(9);
            replace_by(tmp,map,id);
        }

        if(line.size() > 11 && line.compare(2, 11, "categories:") == 0){
            nb_categories = stol(line.substr(14));
            for(int i=0;i < nb_categories; i++){
                getline(this->file, line);
                replace_by(line,map,id);
            }
        }
    }
    cout << "End\n";
}

void Collector::replace_by(std::string& str, std::unordered_map<std::string,std::set<long> *> & map,long  id ){
    int start(0);
    int len(0);
    char a('a');
    int len_a(-1);
    for ( std::string::iterator it=str.begin(); it!=str.end(); ++it){
        len++;
        auto search=punctuation_to_delete.find(*it);
        if(search!=punctuation_to_delete.end()){
            *it=' ';
            if(a!=' '){
                auto search=map.find(str.substr(start,len-1));
                if(search!=map.end()){
                    search->second->insert(id);
                }
                start=start+len;
                len=0;
            }
        }
        else{
            *it=std::tolower(*it);
            if((*it==' ' || *it=='\r') && a!=' '){
                auto search=map.find(str.substr(start,len-1));
                if(search!=map.end()){
                    search->second->insert(id);
                }
                start=start+len;
                len=0;
            }
        }
        if(a==' ' && *it==' ' && start-1==len_a){
            start++;
            len--;
        }
        len_a++;
        a=*it;
    }
}
