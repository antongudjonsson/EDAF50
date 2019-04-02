#include "messagehandler.h"
#include "connection.h"

using std::shared_ptr;

MessageHandler::MessageHandler(shared_ptr<Connection>& c){}

MessageHandler::MessageHandler(Connection& c){}

void MessageHandler::send_code(Protocol code){

}

void MessageHandler::send_int(int value){

}

void MessageHandler::send_int_parameter(int param){

}

void MessageHandler::send_string_parameter(std::string param){

}

Protocol MessageHandler::receive_cmd(){

}

int MessageHandler::receive_int(){

}

int MessageHandler::receive_int_parameter(){

}

std::string MessageHandler::receive_string_parameter(){
    
}