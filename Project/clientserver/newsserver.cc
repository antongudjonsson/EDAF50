#include "connection.h"
#include "connectionclosedexception.h"
#include "server.h"
#include "protocol.h"
#include "messagehandler.h"

#include "dBinterface.h"
#include <iostream>
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

void list_NG(MessageHandler &msg)
{
        msg.send_code(Protocol::ANS_LIST_NG);


        msg.send_code(Protocol::ANS_END);
}

void create_NG(MessageHandler &msg)
{
        msg.send_code(Protocol::ANS_CREATE_NG);


        msg.send_code(Protocol::ANS_END);
}

void delete_NG(MessageHandler &msg)
{
        msg.send_code(Protocol::ANS_DELETE_NG);


        msg.send_code(Protocol::ANS_END);
}

void list_articles(MessageHandler &msg)
{
        msg.send_code(Protocol::ANS_LIST_ART);


        msg.send_code(Protocol::ANS_END);
}

void create_article(MessageHandler &msg)
{
        msg.send_code(Protocol::ANS_CREATE_ART);


        msg.send_code(Protocol::ANS_END);
}

void delete_article(MessageHandler &msg)
{
        msg.send_code(Protocol::ANS_DELETE_ART);


        msg.send_code(Protocol::ANS_END);
}

void get_article(MessageHandler &msg)
{
        msg.send_code(Protocol::ANS_GET_ART);


        msg.send_code(Protocol::ANS_END);
}

int main(int argc, char *argv[])
{
        auto server = init(argc, argv);
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
                                        list_NG(msg);
                                        break;
                                case Protocol::COM_CREATE_NG:
                                        create_NG(msg);
                                        break;
                                case Protocol::COM_DELETE_NG:
                                        delete_NG(msg);
                                        break;
                                case Protocol::COM_LIST_ART:
                                        list_articles(msg);
                                        break;
                                case Protocol::COM_CREATE_ART:
                                        create_article(msg);
                                        break;
                                case Protocol::COM_DELETE_ART:
                                        delete_article(msg);
                                        break;
                                case Protocol::COM_GET_ART:
                                        get_article(msg);
                                        break;
                                case Protocol::COM_END:
                                        throw ConnectionClosedException();
                                        break;
                                default:
                                        cout << "Unknown command received. Terminating connection." << endl;
                                        server.deregisterConnection(conn);
                                        break;
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