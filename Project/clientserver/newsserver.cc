#include "connection.h"
#include "connectionclosedexception.h"
#include "server.h"
#include "protocol.h"

#include "dBinterface.h"
#include <iostream>
using namespace std;


Server init(int argc, char* argv[]){
     if (argc != 2) {
                cerr << "Usage: myserver port-number" << endl;
                exit(1);
        }

        int port = -1;
        try {
                port = stoi(argv[1]);
        } catch (exception& e) {
                cerr << "Wrong format for port number. " << e.what() << endl;
                exit(2);
        }

        Server server(port);
        if (!server.isReady()) {
                cerr << "Server initialization error." << endl;
                exit(3);
        }
        return server;
}


void list_NG(){

}

void create_NG(){

}

void delete_NG(){

}

void list_articles(){

}

void create_article(){

}

void delete_article(){

}

void get_article(){

}


int main(int argc, char* argv[]){
     auto server = init(argc, argv);

        while (true) {
                auto conn = server.waitForActivity();
                if (conn != nullptr) {
                        try {
                                cout << "Hello, world!" << endl;
                                Protocol cmd;
                                switch (cmd)
                                {
                                    case Protocol::COM_LIST_NG:
                                        list_NG();
                                        break;
                                    case Protocol::COM_CREATE_NG:
                                        create_NG();
                                        break;
                                    case Protocol::COM_DELETE_NG:
                                        delete_NG();
                                        break;
                                    case Protocol::COM_LIST_ART:
                                        list_articles();
                                        break;
                                    case Protocol::COM_CREATE_ART:
                                        create_article();
                                        break;
                                    case Protocol::COM_DELETE_ART:
                                        delete_article();
                                        break;
                                    case Protocol::COM_GET_ART:
                                        get_article();
                                        break;
                                    default:
                                        cout << "Unknown command received: " << endl;
                                        break;
                                }
                               //Activity on open connection
                        } catch (ConnectionClosedException&) {
                                server.deregisterConnection(conn);
                                cout << "Client closed connection" << endl;
                        }
                } else {
                        //Activity on closed connection -> new connection
                        conn = make_shared<Connection>();
                        server.registerConnection(conn);
                        cout << "New client connects" << endl;
                }
        }
        return 0;
}