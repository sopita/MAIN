#include "Collector.hpp"

Collector::Collector(string name)
{
    this->file.open(name);
    if(!this->file.is_open()){
        perror("open");
        exit(EXIT_FAILURE);
    }
    std::vector<char> tmp {'.','[',']','(','(',',','?','&','|',':'};
    for(int i=0;i<tmp.size();i++){
        this->punctuation_to_delete[tmp[i]]=' ';
    }
}

Article* Collector::getNewArticle()
{
    
    if(!this->file.is_open()){
        throw string("Source file doesn't exist (use initCollector)");
    }
    
    string line;
    int nb_categorie(0);
    Article *current_article = new Article(-1); // Need a more proper maner
    //getArticleWords();
    long int id;
    return current_article;
    /*
    while(!this->file.eof()){
        
        getline(this->file, line);
        
        if(nb_categorie > 0) {
            --nb_categorie;
            replace(line.begin(), line.end(), '|', ' ');
            regex e (REGEX);
            stringstream ssin(regex_replace(line, e,"",std::regex_constants::match_not_null));
            do
            {
                for (string word; ssin >> word;) {
                    if(word.length() > 1)
                        current_article->getWords()[word]=1;
                }
                if (ssin.fail())
                {
                    ssin.clear();
                    std::string token;
                    ssin >> token;
                }
            }
            while (!ssin.eof());
            
            if(nb_categorie == 0) {
                return current_article;
            }
        }
        
        if(line.compare(0, 3, "Id:") == 0){
            id = stol(line.substr(6));
            current_article->setId(id);
        }
        
        if(line.size() > 6 && line.compare(2, 6, "title:") == 0){
            regex e ("[^\\w||\\ ]");
            
            stringstream ssin(regex_replace(line.substr(9), e, ""));
            
            do
            {
                for (string word; ssin >> word;) {
                    if(word.length() > 1)
                        current_article->getWords()[word]=1;
                }
                if (ssin.fail())
                {
                    ssin.clear();
                    std::string token;
                    ssin >> token;
                }
            }
            while (!ssin.eof());
            
        }
        
        if(line.size() > 11 && line.compare(2, 11, "categories:") == 0){
            nb_categorie = stol(line.substr(14));
            if(nb_categorie == 0) {
                return current_article;
            }
        }
    }
    delete current_article;
    return nullptr; // Not nice*/
}

void Collector::getArticleWords(std::unordered_map<std::string,std::vector<long> *> & map){
    long id;
    int nb_categories;
    std::string line;
    std::string tmp;
    getline(this->file, line);
    getline(this->file, line);
    getline(this->file, line);
    getline(this->file, line);
    cout << "start\n";
    while(!this->file.eof()){
        if(line.compare(0, 3, "Id:") == 0){
            id = stol(line.substr(6));
            //std::cout << "Id: " << id << endl;
        }
        else{
            std::cout << "1 )File has a error.\n";
            exit(EXIT_FAILURE);
        }
        getline(this->file, line);
        getline(this->file, line);
        if(line.compare(2, 6, "title:") == 0){
            tmp=line.substr(9);
            replace_by(tmp,map,id);
            //std::cout << "title: "<<tmp << endl;
        }
        else{
            getline(this->file, line);
            getline(this->file, line);
            continue;
        }
        getline(this->file, line);
        getline(this->file, line);
        getline(this->file, line);
        getline(this->file, line);
        if( line.compare(2, 11, "categories:") == 0){
            nb_categories = stol(line.substr(14));
            for(int i=0;i <= nb_categories; i++){
                getline(this->file, line);
                replace_by(line,map,id);
                //std::cout << line << endl;
            }
            getline(this->file, line);
            while(line.compare("\r")!= 0 ){
                getline(this->file, line);
            }
        }
        else{
            std::cout << "2)File has a error.\n";
            exit(EXIT_FAILURE);
        }
        getline(this->file, line);
        while(line.compare("\r")== 0 ){
            getline(this->file, line);
        }
    }
    cout << "end\n";
}

void Collector::replace_by(std::string& str, std::unordered_map<std::string,std::vector<long> *> & map,long  id ){
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
                //cout << str.substr(start,len-1) << endl;
                auto search=map.find(str.substr(start,len-1));
                if(search!=map.end()){
                    search->second->push_back(id);
                }
                start=start+len;
                len=0;
            }
        }
        else{
            *it=std::tolower(*it);
            if((*it==' ' || *it=='\r') && a!=' '){
                //cout << str.substr(start,len-1) << endl;
                auto search=map.find(str.substr(start,len-1));
                if(search!=map.end()){
                    search->second->push_back(id);
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
