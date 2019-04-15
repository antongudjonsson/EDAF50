#include "memorydB.h"

#include <unordered_map>
#include <iostream>
#include <utility>
#include <vector>
using std::cout;
using std::endl;

MemorydB::MemorydB(){}

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
    for(auto i : data){
        if(i.second.getGroupName() == groupname){
            return false;
        }
    }
    Newsgroup ng(groupname, ngID);
    data.emplace(ngID, ng);
    ngID++;
    return true;
}

bool MemorydB::delete_NG(int grpid){
    if(data.erase(grpid) == 1){
        return true;
    }else{
        return false;
    }   
}

pair<int,vector<Article>> MemorydB::list_articles(int grpid) const {
    pair<int, vector<Article>> p;
    try{
        p = make_pair(SUCCESS, data.at(grpid).listArticles());
        return p;
    }catch(const out_of_range &oor){
        return p;
    }
}

pair<int,Article> MemorydB::get_article(int grpid, int articleID) const {
    Article art;
    return data.count(grpid) == 1 ? data.at(grpid).getArticle(articleID) : make_pair(NEWSGROUP_NOT_FOUND, art);
}

bool MemorydB::create_article(int grpid, string title, string author, string text){
    try{
        data.at(grpid).createArticle(title, author, text);
        return true;
    }catch(out_of_range &oor){
        return false;
    }
}

int MemorydB::delete_article(int grpid, int articleID){
    return data.count(grpid) == 1 ? 
        (data.at(grpid).deleteArticle(articleID) ? SUCCESS : ARTICLE_NOT_FOUND) : NEWSGROUP_NOT_FOUND;
}