#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "../Parsing/parse.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>


class Socket {
    private :
        std::string             host;
        int                     port;
        std::string             server_name;
        int                     socket_client;
    public :
        Socket(std::string, std::string, int);
        Socket(Socket const &cpy);
        Socket &operator=(Socket const &obj);
        void Socket_client();
        ~Socket();
};


#endif
