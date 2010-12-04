#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <ncursesw/ncurses.h>

using std::string;
using std::cerr;
using std::endl;
using std::cout;

class network
{
	private:
		struct addrinfo *res;
		string currentBuffer;
		int sockfd;
	public:
		//initialiser taking the hostname and port or protocol (as a string)
		network(string hostname, string port);
		//a version of recv with a timeout (in microseconds, will block until then)
		int recvTimeout(int s, char *buf, int len, int timeout);
		//recieve a message from the network (put in the buffer, returns message length)
		int recieveMsg(string &buffer);
		//send a message to the network not including newline (returns the number of bytes sent)
		int sendMsg(string message);
};

#endif
