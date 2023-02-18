#include "socket.hpp"

Socket::Socket(std::string h, std::string name, int p)
{
    host = h;
    port = p;
    server_name = name;
}

Socket::Socket(Socket const &cpy)
{
    *this = cpy;
}

Socket &Socket::operator=(const Socket &obj)
{
    (void)obj;
    return (*this);
}

Socket::~Socket()
{

}

void    Socket::Socket_client()
{
    // 1- Creat a Socket
    socket_client = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_client < 0)
        exit(1);
    // 2- Connect A Socket with a Port Server
    struct sockaddr_in SockAddr;
    memset(&SockAddr, 0, sizeof(SockAddr));
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_addr.s_addr = inet_addr(const_cast<char *>(host.c_str()));
    SockAddr.sin_port = htons(port);
    if (connect(socket_client, (struct sockaddr *) &SockAddr, sizeof(SockAddr)))
    {
        std::cout << "Error in Connection\n";
        exit(1);
    }
    else
        std::cout << "Connection\n";
    char msg[1024];
    while (1)
    {
        memset(msg, 0, 1024);
        std::cin.getline(msg, 1024);
        if (!strcmp(msg, "exit"))
        {
            close(socket_client);
            std::cout << "Diconnected Client\n";
            break;
        }
        send(socket_client, msg, strlen(msg), 0);
        recv(socket_client, msg, 1024, 0);
        std::cout << "Receive Data From Server : " << msg << std::endl;
    }
    close(socket_client);
}