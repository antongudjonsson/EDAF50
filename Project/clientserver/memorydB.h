#ifndef MEMORYDB_H
#define MEMORYDB_H

//using namespace std;

#include "dBinterface.h"
#include <string>
#include <unordered_map>
using namespace std;

/*A general database to be used by the client-server program*/
class MemorydB : public DBInterface {
    public:
        MemorydB();

        ~MemorydB();

        /*Returns a list of all News Groups in the database*/
        void list_NG() const;

        /*Creates a new News Group with name groupname and gives it a unique ID  */
        bool create_NG(string groupname);

        /*Deletes the News Group with the given Name/ID*/
        bool delete_NG(int grpid);

        /*Lists all articles in the given News Group*/
        void list_articles(int grpid) const;

        /*Prints the text of the article in News Group groupname with ID articleID*/
        void read_article(string groupname, int articleID) const;

        /*Creates an article with name title and gives it an ID unique to that News Group*/
        bool create_article(int grpid, string title, string author, string text);

        /*Deletes the article in News Group groupname with ID articleID*/
        bool delete_article(int grpid, int articleID);

    private:

};

#endif