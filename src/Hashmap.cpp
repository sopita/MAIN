#include "Collector.hpp"
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
    Collector collector(argv[1]);
    std::vector<std::string> dics;
    collector.create_collector(dicts, argv[args-1]);
    return 0;
}
