#include "memorydB.h"

#include <unordered_map>

MemorydB::MemorydB(){

}

MemorydB::~MemorydB(){
    
}

vector<Newsgroup> MemorydB::list_NG() const{
    vector<Newsgroup> ngList;
    for (auto i = data.begin(); i != data.end(); i++){
        ngList.push_back(i->second);
    }
    return ngList;
}

bool MemorydB::create_NG(string groupname){
    return 0;
}

bool MemorydB::delete_NG(int grpid){
    return 0;
}

vector<Article> MemorydB::list_articles(int grpid) const {

}

pair<int,Article> MemorydB::get_article(int grpid, int articleID) const {

}

int MemorydB::create_article(int grpid, string title, string author, string text){
    return 0;
}

int MemorydB::delete_article(int grpid, int articleID){
    return 0;
}