#include "connection.h"
#include "connectionclosedexception.h"
#include "server.h"
#include "protocol.h"
#include "messagehandler.h"

#include "dBinterface.h"
#include "memorydB.h"
#include "newsgroup.h"
#include "article.h"
#include <iostream>
#include <vector>
using namespace std;

Server init(int argc, char *argv[])
{
        cout << "Booting up server...";
        if (argc != 2)
        {
                cerr << "Usage: myserver port-number" << endl;
                exit(1);
        }

        int port = -1;
        try
        {
                port = stoi(argv[1]);
        }
        catch (exception &e)
        {
                cerr << "Wrong format for port number. " << e.what() << endl;
                exit(2);
        }

        Server server(port);
        if (!server.isReady())
        {
                cerr << "Server initialization error." << endl;
                exit(3);
        }
        cout << " Done!" << endl;
        return server;
}

void list_NG(MessageHandler &msg, MemorydB &db)
{
        msg.send_code(Protocol::ANS_LIST_NG);

        vector<Newsgroup> ngList = db.list_NG();
        msg.send_int_parameter(ngList.size());

        if(ngList.size() != 0){
                for(Newsgroup ng : ngList){
                        msg.send_int_parameter(ng.getID());
                        msg.send_string_parameter(ng.getGroupName());
                }
        }
        msg.send_code(Protocol::ANS_END);
}

void create_NG(MessageHandler &msg, DBInterface &db)
{
        msg.send_code(Protocol::ANS_CREATE_NG);

        if(db.create_NG(msg.receive_string_parameter())){
                msg.send_code(Protocol::ANS_ACK);
        }else{
                msg.send_code(Protocol::ANS_NAK);
                msg.send_code(Protocol::ERR_NG_ALREADY_EXISTS);
        }

        msg.send_code(Protocol::ANS_END);
}

void delete_NG(MessageHandler &msg, DBInterface &db)
{
        msg.send_code(Protocol::ANS_DELETE_NG);

        if(db.delete_NG(msg.receive_int_parameter())){
                msg.send_code(Protocol::ANS_ACK);
        }else{
                msg.send_code(Protocol::ANS_NAK);
                msg.send_code(Protocol::ERR_NG_DOES_NOT_EXIST);
        }

        msg.send_code(Protocol::ANS_END);
}

void list_articles(MessageHandler &msg, DBInterface &db)
{
        msg.send_code(Protocol::ANS_LIST_ART);

        pair<int, vector<Article>> artList = db.list_articles(msg.receive_int_parameter());

        if(artList.first == 1){
                msg.send_code(Protocol::ANS_ACK);
                msg.send_int_parameter(artList.second.size());
                for(Article a : artList.second){
                        msg.send_int_parameter(a.getID());
                        msg.send_string_parameter(a.getTitle());
                }
        }else{
                msg.send_code(Protocol::ANS_NAK);
                msg.send_code(Protocol::ERR_NG_DOES_NOT_EXIST);
        }

        msg.send_code(Protocol::ANS_END);
}

void create_article(MessageHandler &msg, DBInterface &db)
{
        msg.send_code(Protocol::ANS_CREATE_ART);
        int ngID = msg.receive_int_parameter();
        string title = msg.receive_string_parameter();
        string author = msg.receive_string_parameter();
        string text = msg.receive_string_parameter();

        if(db.create_article(ngID, title, author, text)){
                msg.send_code(Protocol::ANS_ACK);
        }else{
                msg.send_code(Protocol::ANS_NAK);
                msg.send_code(Protocol::ERR_NG_DOES_NOT_EXIST);
        }

        msg.send_code(Protocol::ANS_END);
}

void delete_article(MessageHandler &msg, DBInterface &db)
{
        msg.send_code(Protocol::ANS_DELETE_ART);

        int outcome = db.delete_article(msg.receive_int_parameter(), msg.receive_int_parameter());

        if(outcome == SUCCESS){
                msg.send_code(Protocol::ANS_ACK);
        }
        if(outcome == ARTICLE_NOT_FOUND){
                msg.send_code(Protocol::ANS_NAK);
                msg.send_code(Protocol::ERR_ART_DOES_NOT_EXIST);
        }
        else if(outcome == NEWSGROUP_NOT_FOUND){
                msg.send_code(Protocol::ANS_NAK);
                msg.send_code(Protocol::ERR_NG_DOES_NOT_EXIST);
        }

        msg.send_code(Protocol::ANS_END);
}

void get_article(MessageHandler &msg, DBInterface &db)
{
        msg.send_code(Protocol::ANS_GET_ART);

        pair<int,Article> anArticle = db.get_article(msg.receive_int_parameter(), msg.receive_int_parameter());
        int outcome = anArticle.first;
        string author = anArticle.second.getAuthor();
        string text = anArticle.second.getText();
        string title = anArticle.second.getTitle();

        if(outcome == SUCCESS){
                msg.send_code(Protocol::ANS_ACK);
                msg.send_string_parameter(title);
                msg.send_string_parameter(author);
                msg.send_string_parameter(text);
        }

        if(outcome == ARTICLE_NOT_FOUND){
                msg.send_code(Protocol::ANS_NAK);
                msg.send_code(Protocol::ERR_ART_DOES_NOT_EXIST);        
        }
        else if(outcome == NEWSGROUP_NOT_FOUND){
                msg.send_code(Protocol::ANS_NAK);
                msg.send_code(Protocol::ERR_NG_DOES_NOT_EXIST);
        }



        msg.send_code(Protocol::ANS_END);
}

int main(int argc, char *argv[])
{
        auto server = init(argc, argv);
        MemorydB db;
        while (true)
        {
                auto conn = server.waitForActivity();
                if (conn != nullptr)
                {
                        MessageHandler msg(conn);
                        try
                        {
                                Protocol cmd = msg.receive_cmd();
                                switch (cmd)
                                {
                                case Protocol::COM_LIST_NG:
                                        list_NG(msg, db);
                                        break;
                                case Protocol::COM_CREATE_NG:
                                        create_NG(msg, db);
                                        break;
                                case Protocol::COM_DELETE_NG:
                                        delete_NG(msg, db);
                                        break;
                                case Protocol::COM_LIST_ART:
                                        list_articles(msg, db);
                                        break;
                                case Protocol::COM_CREATE_ART:
                                        create_article(msg, db);
                                        break;
                                case Protocol::COM_DELETE_ART:
                                        delete_article(msg, db);
                                        break;
                                case Protocol::COM_GET_ART:
                                        get_article(msg, db);
                                        break;
                                default:
                                        cout << "Unknown command received. Terminating connection." << endl;
                                        throw ConnectionClosedException();
                                        break;
                                }
                                if(msg.receive_cmd() != Protocol::COM_END){
                                        cout << "Expected end of communication. Terminating connection." << endl;
                                        throw ConnectionClosedException();
                                }
                        }
                        catch (ConnectionClosedException &)
                        {
                                server.deregisterConnection(conn);
                                cout << "Client closed connection" << endl;
                        }
                }
                else
                {
                        //Activity on closed connection -> new connection
                        conn = make_shared<Connection>();
                        server.registerConnection(conn);
                        cout << "New client connects" << endl;
                }
        }
        return 0;
}