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
	Protocol receive_cmd();
	int receive_int();
	int receive_int_parameter();
	std::string receive_string_parameter();
private:
	std::shared_ptr<Connection> conn; // the connection
	unsigned char receive_byte();
  	void send_byte(const char code);
};
