#ifndef SOCKETSERVER_HPP
#define SOCKETSERVER_HPP

#include "../Parsing/parse.hpp"
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class SocketServer {
private :
    std::string             host;
    int                     port;
    std::string             server_name;
    int                     socket_server;
public :
    SocketServer(std::string, std::string, int);
    SocketServer(SocketServer const &cpy);
    SocketServer &operator=(SocketServer const &obj);
    void Socket_server();
    ~SocketServer();
};


#endif