#include"parse.hpp"

bool    check_line(std::string const line ,std::string const &comp)
{
    char *tok;

    tok = strtok((char *)line.c_str()," \t\r\f\v");
    while(tok)  
    {
        if(comp == "server" && comp.compare(tok) == 0)
        {
            tok = strtok(NULL," \t\r\f\v");
            if(tok == NULL)
                return false;
            if(tok[0] == '{')
                return true;
            return false;
        }
        else if(comp.compare(tok) == 0)
            return true;
        tok = strtok(NULL," \t\r\f\v");
    }
    return false;
}

// bool    getlinecut(std::ifstream &fd, std::string &line)
// {
// 	if (!std::getline(fd, line))
// 		return false;
// 	line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
//     std::cout << line << std::endl;
// 	return true;
// }

// int main()
// {
//     // std::string path = "server ";
//     // std::string str = "server";
//     // std::cout << check_line(path,str) << std::endl;
//     std::string line = "host    -   128.231.1.1";	
//     line.erase(0, line.find_first_not_of(" \t\n\r\f\v-"));
//     std::cout << line << std::endl;
//     return 0;
// }

std::string get_value(const std::string &line,const std::string &key)
{
    std::string value;
    value = line.substr(line.find(key) + key.length(),line.find_last_not_of(" \t\n\r\f\v"));
    value.erase(0, value.find_first_not_of(" \t\n\r\f\v"));
    value.erase(value.find_last_not_of(" \t\n\r\f\v") + 1);
    return value;
}

void    parse_server(t_config &config, std::ifstream &fd)
{
    std::string line;
    while (std::getline(fd, line) && line[0] != '}')
    {
        if(check_line(line,"host"))
            config.host = (get_value(line,"host") == "" ? "0.0.0.0" : get_value(line,"host"));
        else if(check_line(line,"port"))
            config.port.push_back((get_value(line,"port") == "" ? "80" : get_value(line,"port")));
        else if(check_line(line,"server_name"))
            config.server_name = (get_value(line,"server_name") == "" ? "localhost" : get_value(line,"server_name"));
    }
}


void init_config(std::list<t_config> &gnf)
{
    t_config config;

    config.host = "0.0.0.0";
    config.port.push_back("80");
    config.server_name = "localhost";
    gnf.push_back(config);
}

void    parse_config_file(std::string path,std::list<t_config> &gnf)
{
    std::ifstream fd(path.c_str());
    std::string line;

    if(!fd.is_open())
    {
        fd.close();
		// if (errno == 2)
		// 	P("Error: no such file or directory");
		// else if (errno == 13)
		// 	P("Error: permission denied");
		// exit(1);   
        std::cout << "Error: Can't open config file" << std::endl;
        exit(1);
    }
    while(std::getline(fd,line))
    {
        if(line[0] == '#')
            continue;
        if(check_line(line,"server"))
        {
            init_config(gnf);
            parse_server(gnf.back(),fd);
        }
        
    }
}
