#include "article.h"

#include <string>

Article::Article(string t, string a, string txt): title(t), author(a), text(txt){}

string Article::read(){
    return text;
}