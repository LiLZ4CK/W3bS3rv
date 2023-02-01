#ifndef PARSE_HPP
#define PARSE_HPP

#include<iostream>
#include<cstring>
#include<fstream>
#include<list>

typedef struct s_config 
{
    std::string host;
    std::list<std::string> port;
    std::string server_name;
} t_config ;

void    parse_config_file(std::string path,std::list<t_config> &gnf);

#endif