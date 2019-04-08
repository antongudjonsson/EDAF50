#include "article.h"

#include <string>

Article::Article(string t, string a, string txt, int id): title(t), author(a), text(txt), id(id){}

string Article::getText(){
    return text;
}

string Article::getAuthor(){
    return author;
}

string Article::getTitle(){
    return title;
}

int Article::getID(){
    return id;
}