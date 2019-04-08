#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>

using namespace std;

class Article{
    public:
    Article(string title = "", string author = "", string text = "", int id = -1);

    string getText();

    string getTitle();

    string getAuthor();

    int getID();


    private:
    string title;
    string author;
    string text;
    int id;
};


#endif