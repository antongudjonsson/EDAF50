#ifndef DBINTERFACE_H
#define DBINTERFACE_H

//using namespace std;

#include <string>
using namespace std;

/*A general database to be used by the client-server program*/
class DBInterface {
    public:
        virtual ~DBInterface() = default;

        /*Returns a list of all News Groups in the database*/
        virtual void list_NG() const;

        /*Creates a new News Group with name groupname and gives it a unique ID  */
        virtual bool create_NG(string groupname);

        /*Deletes the News Group with the given Name/ID*/
        virtual bool delete_NG(string groupname);

        /*Lists all articles in the given News Group*/
        virtual void list_articles(string groupname) const;

        /*Prints the text of the article in News Group groupname with ID articleID*/
        virtual void read_article(string groupname, int articleID) const;

        /*Creates an article with name title and gives it an ID unique to that News Group*/
        virtual bool create_article(string title, string text);

        /*Deletes the article in News Group groupname with ID articleID*/
        virtual bool delete_article(string groupname, int articleID);

    private:
};

#endif