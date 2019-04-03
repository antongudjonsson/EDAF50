#ifndef DBINTERFACE_H
#define DBINTERFACE_H

//using namespace std;

#include <string>
#include "newsgroup.h"
#include "article.h"
#include <vector>
using namespace std;

const int SUCCESS = 0;              //Returned after successful creation/deletion
const int ARTICLE_NOT_FOUND = 1;    //Returned when attempting creation/deletion but no such article ID was found
const int NEWSGROUP_NOT_FOUND = -1; //Returned when attempting creation/deletion but no such newsgroup ID was found

/*A general database to be used by the client-server program*/
class DBInterface {
    public:
        virtual ~DBInterface() = default;

        /*Returns a list of all News Groups in the database*/
        virtual vector<Newsgroup> list_NG() const = 0;

        /*Creates a new News Group with name groupname and gives it a unique ID  */
        virtual bool create_NG(string groupname) = 0;

        /*Deletes the News Group with the given Name/ID*/
        virtual bool delete_NG(int grpid) = 0;

        /*Lists all articles in the given News Group*/
        virtual vector<Article> list_articles(int grpid) const = 0;

        /*Prints the text of the article in News Group groupname with ID articleID*/
        virtual pair<int, Article> get_article(int grpid, int articleID) const = 0;

        /*Creates an article with name title and gives it an ID unique to that News Group*/
        virtual int create_article(int grpid, string title, string author, string text) = 0;

        /*Deletes the article in News Group groupname with ID articleID*/
        virtual int delete_article(int grpid, int articleID) = 0;

};

#endif