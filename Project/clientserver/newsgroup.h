#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include <string>
#include "article.h"

using namespace std;

class Newsgroup {
    public:
    Newsgroup(string name);

    Article getArticle(int id);
    
    void listArticles();

    private:
    string name;
    int id;
    //Article datastructure
};

#endif