#include "newsgroup.h"
#include "article.h"
#include "dBinterface.h"
#include <vector>
#include <utility>
#include <iostream>
using namespace std;

Newsgroup::Newsgroup(string name, int id): name(name), id(id){}

pair<int, Article> Newsgroup::getArticle(int artid) const{
    Article art;
    return data.count(artid) == 1 ? make_pair(SUCCESS, data.at(artid)) : make_pair(ARTICLE_NOT_FOUND, art);
}

vector<Article> Newsgroup::listArticles() const{
    vector<Article> artList;
    for(auto i : data){
        artList.push_back(i.second);
    }
    return artList;
}

bool Newsgroup::createArticle(string title, string author, string text){
    Article art(title, author, text, artID);
    data.emplace(artID, art);
    artID++;
    return true;
}

bool Newsgroup::deleteArticle(int artid){
    return data.erase(artid) == 1 ? true : false;
}

string Newsgroup::getGroupName() const{
    return name;
}

int Newsgroup::getID() const{
    return id;
}