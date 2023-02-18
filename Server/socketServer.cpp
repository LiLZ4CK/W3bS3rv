#include "socketServer.hpp"

SocketServer::SocketServer(std::string h, std::string name, int p)
{
    host = h;
    port = p;
    server_name = name;
}

SocketServer::SocketServer(SocketServer const &cpy)
{
    *this = cpy;
}

SocketServer &SocketServer::operator=(SocketServer const &obj)
{
    (void)obj;
    return (*this);
}

SocketServer::~SocketServer()
{

}

void    SocketServer::Socket_server()
{
    // 1- Creat a Socket for Server
    socket_server = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_server < 0)
        exit(1);
    // 1-1 Option Socket
//    int opt = true;
//    setsockopt(socket_server, SOL_SOCKET, SO_REUSEADDR, (void *) &opt, sizeof(opt));
    // 2- Bind A Socket with a Port number
    struct sockaddr_in ServerAddr;
    memset(&ServerAddr, 0, sizeof(ServerAddr));
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    ServerAddr.sin_port = htons(port);
    if (bind(socket_server, (struct sockaddr *) &ServerAddr, sizeof(ServerAddr)))
    {
        std::cout << "Error In Bind Server\n";
        exit(1);
    }

    // 3- Listen to the Clients connection request
    if (listen(socket_server, 128))
    {
        std::cout << "No listen\n";
        exit(1);
    }
    // 4- here synchronous I/O multiplexing
    struct timeval time;
    fd_set fds, cp_fds;
    FD_ZERO(&fds);
    FD_SET(socket_server, &fds);
    int fd_select = socket_server;
    int numSelect;
    char msg[1024];
    struct sockaddr_in Server;
    int connectServerFd;
    socklen_t lengthClients = sizeof(Server);
    memset(&Server, 0, sizeof(Server));

    while (1)
    {
        cp_fds = fds;
        time.tv_sec = 4;
        time.tv_usec = 0;
        numSelect = select(fd_select + 1, &cp_fds, 0, 0, &time);
        if (numSelect < 0)
        {
            std::cout << "Error In SELECT\n";
            break;
        }
        else if (numSelect == 0)
            continue;
        else
        {
            int i = 0;
            while (i < fd_select + 1)
            {
                if (FD_ISSET(i, &cp_fds))
                {
                    if (i == socket_server)
                    {
                        connectServerFd = accept(socket_server, (struct sockaddr *) &Server, &lengthClients);
                        FD_SET(connectServerFd, &fds);
                        if (connectServerFd < 0)
                        {
                            std::cout << "Error in Connection\n";
                            continue;
                        }
                        else if (fd_select < connectServerFd)
                            fd_select = connectServerFd;
                        std::cout << "Client Num : " << connectServerFd << " is Connected\n";
                    }
                    else
                    {
                        memset(msg, 0, 1024);
                        recv(i, msg, 1024, 0);
                        std::cout << "From Client " << i << ": " << msg << std::endl;
                        if (strlen(msg) == 0)
                        {
                            FD_CLR(i, &fds);
                            close(i);
                            std::cout << "Client Num " << i << " is Diconnected\n";
                        }
                        else
                            send(i, msg, strlen(msg), 0);
                    }
                }
                i++;
            }
        }
    }
    close(connectServerFd);
}