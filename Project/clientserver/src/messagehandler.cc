#include "messagehandler.h"
#include "connection.h"
#include <vector>
#include <iostream>

using std::shared_ptr;
using namespace std;
using std::cout;
using std::endl;

MessageHandler::MessageHandler(shared_ptr<Connection>& c): conn(c) {}

MessageHandler::MessageHandler(Connection& c): conn(&c) {}

void MessageHandler::send_byte(const char code){
    conn->write(code);
}

void MessageHandler::send_code(Protocol code){
    send_byte(static_cast<const char>(code));
}

void MessageHandler::send_int(int value){
    send_byte((value >> 24) & 0xFF);
    send_byte((value >> 16) & 0xFF);
    send_byte((value >> 8) & 0xFF);
    send_byte(value & 0xFF);
}

void MessageHandler::send_int_parameter(int param){
    send_code(Protocol::PAR_NUM);
    send_int(param);
}

void MessageHandler::send_string_parameter(std::string param){
    send_code(Protocol::PAR_STRING);
    send_int(static_cast<int>(param.length()));
    for(const char c : param){
        send_byte(c);
    }
}

Protocol MessageHandler::receive_cmd(){
    return static_cast<Protocol>(conn->read());
}

int MessageHandler::receive_int(){
    const char byte1 = conn->read();
    const char byte2 = conn->read();
    const char byte3 = conn->read();
    const char byte4 = conn->read();
    return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

int MessageHandler::receive_int_parameter(){
    if(receive_cmd() != Protocol::PAR_NUM){
        throw ConnectionClosedException();
    }
    return receive_int();

}

std::string MessageHandler::receive_string_parameter(){
    if(receive_cmd() != Protocol::PAR_STRING){
        throw ConnectionClosedException();
    }
    int len = receive_int();
    std::string str;
    for(int i = 0; i < len; i++){
        str.push_back(conn->read());
    }
    return str;
}