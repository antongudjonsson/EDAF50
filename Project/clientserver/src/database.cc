#include "database.h"
#include <iostream>
#include <fstream>
#include <newsgroup.h>
#include <regex>
#include <dirent.h>
#include <utility>

using namespace std;
using std::cout;
using std::endl;

Database::Database(){
    if(system("test -d database.db")){
        system("mkdir database.db");
        system("touch database.db/ngList.txt");
    }else if(!system("test -d database.db/ngList.txt")){
        ifstream inFile("database.db/ngList.txt");
        string ngid;
        string artid;
        string ignore;
        while(inFile >> ngid, inFile >> artid, getline(inFile, ignore)){
            artID.emplace(stoi(ngid), stoi(artid));
            ngID = stoi(ngid);
        }
        ngID += 1;
    }else{
        system("touch database.db/ngList.txt");
    }
}

Database::~Database() {}

bool wayToSort(Article a, Article b) { return a.getID() < b.getID(); }

string replace_line(regex lineToReplace, string replacement){
    ifstream inFile("database.db/ngList.txt");
    string file;
    string line;
    while(getline(inFile, line)){
        file.append(line + '\n'); 
    }
    string replacedFile = regex_replace(file, lineToReplace, replacement);
    ofstream outFile("database.db/ngList.txt");
    outFile << replacedFile;
    inFile.close();
    outFile.close();
}   

vector<Newsgroup> Database::list_NG() const{
    ifstream inFile("database.db/ngList.txt");
    string name;
    string ngid;
    vector<Newsgroup> list;
    while(inFile >> ngid, inFile >> name, getline(inFile, name)){
        name = name.substr(1);
        Newsgroup ng(name, stoi(ngid));
        list.push_back(ng);
    }
    return list;
}

bool Database::create_NG(string groupname){
    ifstream inFile("database.db/ngList.txt");
    string line;
    string ignore;
    while(inFile >> ignore, inFile >> ignore, getline(inFile, line)){
        line = line.substr(1);  //Ignores the leading space
        if(line == groupname){
            return false;
        }
    }
    system(("mkdir -p database.db/" + to_string(ngID)).c_str());
    ofstream outFile("database.db/ngList.txt", fstream::app);
    string data = " " + to_string(ngID) + " 1 " + groupname;
    outFile << data << '\n';
    artID.emplace(ngID,1);
    ngID++;
    return true;
}

bool Database::delete_NG(int grpid){
    ifstream inFile("database.db/ngList.txt");
    string line;
    string file;
    string newfile;
    while(getline(inFile, line)){
     file.append(line + '\n');
    }
    regex rgx("( " + to_string(grpid) + " [0-9]* .*\\s)");
    newfile = regex_replace(file, rgx, "");
    if(file != newfile){
        ofstream outFile("database.db/ngList.txt");
        outFile << newfile;
        inFile.close();
        outFile.close();
        artID.erase(grpid);
        system(("rm -r database.db/" + to_string(grpid)).c_str());
        return true;
    }else{
        return false;
    }
}

pair<int, vector<Article>> Database::list_articles(int grpid) const{
    DIR *dir = opendir (("database.db/" + to_string(grpid)).c_str());
    vector<Article> list;
    if(!dir){ return make_pair(NEWSGROUP_NOT_FOUND, list); }
    
    struct dirent *ent;
    while ((ent = readdir (dir)) != NULL) {
        if(ent->d_type == DT_REG){
            string artid = ent->d_name;
            ifstream inFile("database.db/" + to_string(grpid) + "/" + artid);
            string title;
            getline(inFile, title);
            Article art(title, "nullptr", "nullptr", stoi(artid));
            list.push_back(art);
        }
    }
    sort(list.begin(), list.end(), wayToSort);
    closedir(dir);
    return make_pair(SUCCESS, list);
}

pair<int, Article> Database::get_article(int grpid, int articleID) const{
    DIR *dir = opendir (("database.db/" + to_string(grpid)).c_str());
    Article art;
    if(!dir){ return make_pair(NEWSGROUP_NOT_FOUND, art); }
    closedir(dir);
    ifstream inFile(("database.db/" + to_string(grpid) + "/" + to_string(articleID)).c_str());
    string title;
    string author;
    string text;
    string line;
    if(inFile.is_open()){
        getline(inFile, title);
        getline(inFile, author);
        while(getline(inFile, line)){
                text.append(line);
            if(!inFile.eof()){
                text.append("\n");
            }
        }
        Article art(title, author, text, articleID);
        return make_pair(SUCCESS, art);
    }else{
        return make_pair(ARTICLE_NOT_FOUND, art);
    }
}

bool Database::create_article(int grpid, string title, string author, string text){
    DIR* dir = opendir(("database.db/" + to_string(grpid)).c_str());
    if(!dir){
        return false;
    }
    closedir (dir);
    system(("touch database.db/" + to_string(grpid) + "/" + to_string(artID.at(grpid))).c_str());
    ofstream outFile("database.db/" + to_string(grpid) + "/" + to_string(artID.at(grpid)), fstream::app);
    outFile << title << '\n';
    outFile << author << '\n';
    outFile << text;
    regex rgx("( " + to_string(grpid) + " " + to_string(artID.at(grpid)) + " )");
    string replacement = " " + to_string(grpid) + " " + to_string((artID.at(grpid) + 1)) + " "; 
    artID.at(grpid)++;
    replace_line(rgx, replacement);
    return true;
}

int Database::delete_article(int grpid, int articleID){
    DIR* dir = opendir(("database.db/" + to_string(grpid)).c_str());
    if(!dir){
        return NEWSGROUP_NOT_FOUND;
    }
    ifstream inFile("database.db/" + to_string(grpid) + "/" + to_string(articleID));
    if(inFile.is_open()){
        system(("rm -r database.db/" + to_string(grpid) + "/" + to_string(articleID)).c_str());
        return SUCCESS;
    }else{
        return ARTICLE_NOT_FOUND;
    }
}