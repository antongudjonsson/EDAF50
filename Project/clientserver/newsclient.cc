#include "messagehandler.h"
#include "server.h"
#include "connection.h"
#include <iostream>
#include <istream>
#include <limits>

using namespace std;
using std::cin;

Connection init(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: myclient host port-number" << endl;
        exit(1);
    }

    int port = -1;
    try
    {
        port = stoi(argv[2]);
    }
    catch (exception &e)
    {
        cerr << "Wrong format for port number. " << e.what() << endl;
        exit(2);
    }

    Connection conn(argv[1], port);
    if (!conn.isConnected())
    {
        cerr << "Server initialization error." << endl;
        exit(3);
    }
    return conn;
}

bool handle_ack(MessageHandler &msg)
{
    if (msg.receive_cmd() == Protocol::ANS_ACK)
    {
        return true;
    }
    switch (msg.receive_cmd())
    {
    case Protocol::ERR_NG_ALREADY_EXISTS:
        cerr << "Sorry, a newsgroup with that name already exists." << endl;
        break;
    case Protocol::ERR_NG_DOES_NOT_EXIST:
        cerr << "Sorry, there is no newsgroup with that ID." << endl;
        break;
    case Protocol::ERR_ART_DOES_NOT_EXIST:
        cerr << "Sorry, there is no article with that ID in this newsgroup." << endl;
        break;
    default:
        cerr << "Unknown protocol." << endl;
        break;
    }
    return false;
}

void handle_end(MessageHandler &msg)
{
    if (msg.receive_cmd() != Protocol::ANS_END)
    {
        cerr << "Error! Protocol Violated!" << endl;
    }
}

bool handle_ans(Protocol actual, Protocol expected)
{
    if (actual == expected)
    {
        return true;
    }
    else
    {
        cout << "Protocol violated. Aborting.." << endl;
        return false;
    }
}

void list_NG(MessageHandler &msg)
{
    msg.send_code(Protocol::COM_LIST_NG);
    msg.send_code(Protocol::COM_END);
    int nbrofNG;
    int grpid;
    string grpname;
    if (handle_ans(msg.receive_cmd(), Protocol::ANS_LIST_NG))
    {
        nbrofNG = msg.receive_int_parameter();
        if(nbrofNG != 0){
        cout << "ID: Name" << endl;
        if (nbrofNG != 0)
        {
            for (int i = 0; i < nbrofNG; i++)
            {
                grpid = msg.receive_int_parameter();
                grpname = msg.receive_string_parameter();
                cout << grpid << ": " << grpname << endl;
            }
        }
        }else{
            cout << "There are currently no newsgroups." << endl;
        }
        handle_end(msg);
    }
    else
    {
        cerr << "Error! Protocol Violated!" << endl;
    }
}

void create_NG(MessageHandler &msg)
{
    cout << "Enter the name of the newsgroup: ";
    string ngName;
    cin.ignore();
    getline(cin,ngName);
    msg.send_code(Protocol::COM_CREATE_NG);
    msg.send_string_parameter(ngName);
    msg.send_code(Protocol::COM_END);
    cout << endl;
    if (handle_ans(msg.receive_cmd(), Protocol::ANS_CREATE_NG))
    {
        if (handle_ack(msg))
        {
            cout << "Newsgroup "
                 << "'" << ngName << "'"
                 << " created." << endl;
        };
    }
    handle_end(msg);
}

void delete_NG(MessageHandler &msg)
{
    cout << "Enter the ID of the newsgroup you wish to delete: ";
    int ngID;
    while(!(cin >> ngID)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.  Try again: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    msg.send_code(Protocol::COM_DELETE_NG);
    msg.send_int_parameter(ngID);
    msg.send_code(Protocol::COM_END);
    if (handle_ans(msg.receive_cmd(), Protocol::ANS_DELETE_NG))
    {
        if (handle_ack(msg))
        {
            cout << "Newsgroup deleted." << endl;
        }
    }
    handle_end(msg);
}

void create_art(MessageHandler &msg)
{
    int grpid;
    string title;
    string author;
    string text;
    msg.send_code(Protocol::COM_CREATE_ART);
    cout << "Please enter the ID of the newsgroup you want to add the article to: ";
    while(!(cin >> grpid)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.  Try again: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    msg.send_int_parameter(grpid);
    cout << "Please provide the following information: " << endl;
    cout << "Title: ";
    cin.ignore();
    getline(cin, title);
    msg.send_string_parameter(title);
    cout << "Author: ";
    getline(cin, author);
    msg.send_string_parameter(author);
    cout << "Contents (text): ";
    getline(cin, text);
    msg.send_string_parameter(text);
    msg.send_code(Protocol::COM_END);
    if (handle_ans(msg.receive_cmd(), Protocol::ANS_CREATE_ART))
    {
        if (handle_ack(msg))
        {
            cout << "Article created." << endl;
        }
    }
    handle_end(msg);
}

void list_art(MessageHandler &msg)
{
    msg.send_code(Protocol::COM_LIST_ART);
    cout << "Please enter the ID of the newsgroup of which you wish to view the articles: ";
    int grpid;
    while(!(cin >> grpid)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.  Try again: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    msg.send_int_parameter(grpid);
    msg.send_code(Protocol::COM_END);
    if (handle_ans(msg.receive_cmd(), Protocol::ANS_LIST_ART))
    {
        if (handle_ack(msg))
        {
            int nbrofart = msg.receive_int_parameter();
            if (nbrofart != 0)
            {
                cout << "ID: Title" << endl;
                for (int i = 0; i < nbrofart; i++)
                {
                    int artid = msg.receive_int_parameter();
                    string title = msg.receive_string_parameter();
                    cout << to_string(artid) + ": " + title << endl;
                }
                cout << endl;
            }
            else
            {
                cout << "This newsgroup currently has no articles. Use cmd '5' to create one." << endl;
            }
        }
    }
    handle_end(msg);
}

void delete_art(MessageHandler &msg)
{
    msg.send_code(Protocol::COM_DELETE_ART);
    int grpid;
    int artid;
    cout << "Please provide the following: " << endl;
    cout << "ID of the article's newsgroup: ";
    while(!(cin >> grpid)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.  Try again: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    msg.send_int_parameter(grpid);
    cout << "ID of the article: ";
    while(!(cin >> artid)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.  Try again: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    msg.send_int_parameter(artid);
    msg.send_code(Protocol::COM_END);
    if (handle_ans(msg.receive_cmd(), Protocol::ANS_DELETE_ART))
    {
        if (handle_ack(msg))
        {
            cout << "Article deleted." << endl;
        }
    }
    handle_end(msg);
}

void get_art(MessageHandler &msg){
    msg.send_code(Protocol::COM_GET_ART);
    int grpid;
    int artid;
    cout << "Please provide the following: " << endl;
    cout << "ID of the article's newsgroup: ";
    while(!(cin >> grpid)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.  Try again: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "ID of the article: ";
    while(!(cin >> artid)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.  Try again: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    msg.send_int_parameter(grpid);
    msg.send_int_parameter(artid);
    msg.send_code(Protocol::COM_END);
    if (handle_ans(msg.receive_cmd(), Protocol::ANS_GET_ART))
    {
        if (handle_ack(msg))
        {
            string title = msg.receive_string_parameter();
            string author = msg.receive_string_parameter();
            string text = msg.receive_string_parameter();
            cout << "\nTitle: " << title << endl;
            cout << "Author: " << author << endl;
            cout << text << endl;
        }
    }
    handle_end(msg);

}

void list_options()
{
    cout << "1. List all current newsgroups." << endl;
    cout << "2. Create new newsgroup." << endl;
    cout << "3. Delete a newsgroup." << endl;
    cout << "4. List all articles of a newsgroup." << endl;
    cout << "5. Create a new article in a newsgroup." << endl;
    cout << "6. Delete an article." << endl;
    cout << "7. Read an article." << endl;
    cout << "8. Exit." << endl;
}

int main(int argc, char *argv[])
{
    auto conn = init(argc, argv);
    int cmd;
    cout << "Welcome to our client!" << endl;
    cout << "Please choose one of these options:" << endl;
    list_options();
    MessageHandler msg(conn);
    while (true)
    {
        if (cin >> cmd)
        {
            cout << "---------------------------" << endl;
            try
            {
                switch (cmd)
                {
                case 1:
                    list_NG(msg);
                    break;
                case 2:
                    create_NG(msg);
                    break;
                case 3:
                    delete_NG(msg);
                    break;
                case 4:
                    list_art(msg);
                    break;
                case 5:
                    create_art(msg);
                    break;
                case 6:
                    delete_art(msg);
                    break;
                case 7:
                    get_art(msg);
                    break;
                case 8:
                    cout << "Exiting. Thank you for using our program." << endl;
                    exit(0);
                    break;
                }
                cin.clear();
                cin.sync();
                cout << "---------------------------" << endl;
                cout << "\nPlease choose another command. " << endl;
                list_options();
            }
            catch (ConnectionClosedException &)
            {
                cout << "Not following proper protocol. Terminating.." << endl;
            }
        }
    }
}