#include "article.h"

#include <string>

Article::Article(string t, string a, string txt): title(t), author(a), text(txt){}

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