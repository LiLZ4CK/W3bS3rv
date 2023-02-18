#include "socket.hpp"

int main()
{
    std::list<t_config> gnf;
    parse_config_file("../Parsing/config.conf",gnf);
    std::cout <<"host ===>"<< gnf.back().host << std::endl;
    std::cout <<"port ===>" << gnf.back().port.back() << std::endl;
    std::cout <<"name ===>"<< gnf.back().server_name << std::endl;
    std::cout << "============================\n";
    std::list<std::string>::iterator it = gnf.back().port.end();
    --it;
    std::string str = *it;
    char *p = const_cast<char *>(str.c_str());
    int port = atoi(p);
    Socket skt(gnf.back().host, gnf.back().server_name, port);
    skt.Socket_client();
    return 0;
}
