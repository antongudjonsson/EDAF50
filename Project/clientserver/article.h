#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>

using namespace std;

class Article{
    public:
    Article(string title, string author, string text);

    string read();

    private:
    string title;
    string author;
    string text;
    int id;
};


#endif