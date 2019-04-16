#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include <string>
#include "article.h"
#include <map>
#include <vector>

using namespace std;

class Newsgroup {
    public:
    Newsgroup(string name, int id);

    pair<int, Article> getArticle(int id) const;
    
    vector<Article> listArticles() const;

    bool createArticle(string title, string author, string text);

    bool deleteArticle(int artid);

    string getGroupName() const;

    int getID() const;


    private:
    string name;
    int id;
    int artID = 1;

    map<int,Article> data;
};

#endif