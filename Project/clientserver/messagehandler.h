#include "connection.h"
#include "connectionclosedexception.h"
#include "protocol.h"

#include <string>
#include <memory>

class MessageHandler {
	public:
	MessageHandler(std::shared_ptr<Connection>& c);
	MessageHandler(Connection& c);
	void send_code(Protocol code);
	void send_int(int value);
	void send_int_parameter(int param);
	void send_string_parameter(std::string param);
	Protocol recv_code();
	int recv_int();
	int recv_int_parameter();
	std::string recv_string_parameter();
private:
	std::shared_ptr<Connection> conn; // the connection
	unsigned char recv_byte();
  void send_byte(int code);
};
