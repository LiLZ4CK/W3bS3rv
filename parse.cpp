#include"lexer.hpp"

bool    is_type(std::string type) {
    std::string types[] = {"host", "port", "client_max_body_size", "index", "error_page", "root", "location", "autoindex"};
    int i = 0;
    while(i < 9)
    {
        if(types[i] == type)
            return true;
        i++;
    }
    return false;
}

void parse_host(Lexer &lexer,t_config &config) {

    if(lexer.get_size_value() > 1)
        throw std::runtime_error("Error: host can only have one value");
    config.host = lexer.getvalue(0);
}

void parse_port(Lexer &lexer,t_config &config) {

    if(lexer.get_size_value() > 3)
        throw std::runtime_error("Error: port can only have three values");
    
    for(int i = 0; i < lexer.get_size_value(); i++)
    {
        if(!is_number(lexer.getvalue(i)) && lexer.getvalue(i) != "")
        {
            if(lexer.getvalue(i) == "")
            throw std::runtime_error("Error: port can only have numbers");
        }
        config.port.push_back(lexer.getvalue(i));
    }
}

void parse_client_max_body_size(Lexer &lexer,t_config &config) {

    if(lexer.get_size_value() > 1)
        throw std::runtime_error("Error: client_max_body_size can only have one value");
    if(!is_number(lexer.getvalue(0)))
        throw std::runtime_error("Error: client_max_body_size can only have numbers");
    config.body_size_limit = std::stoi(lexer.getvalue(0));
}

void parse_index(Lexer &lexer,t_config &config) {

    if(lexer.get_size_value() > 3)
        throw std::runtime_error("Error: index can only have three values");
    
    for(int i = 0; i < lexer.get_size_value(); i++)
        config.index.push_back(lexer.getvalue(i));
}

void parse_error_page(Lexer &lexer,t_config &config) {

    if(lexer.get_size_value() > 1)
        throw std::runtime_error("Error: error_page can only have one value");
    config.default_error_page = lexer.getvalue(0);
}

void parse_root(Lexer &lexer,t_config &config) {

    if(lexer.get_size_value() > 1)
        throw std::runtime_error("Error: root can only have one value");
    config.root = lexer.getvalue(0);
}

void init_config(std::list<t_config> &cfg) {
    t_config config;

    config.host = "";
    config.body_size_limit = 0;
    config.default_error_page = "";
    config.root = "";
    cfg.push_back(config);
}

std::list<t_config>    parse_config(std::string filename) {

    Lexer lexer(filename);
    std::list<t_config> config;

    std::string types[] = {"host", "port", "client_max_body_size", "index", "error_page", "root", "location"};
    void    (*foo[]) (Lexer &,t_config &) = {parse_host , parse_port, parse_client_max_body_size, parse_index, parse_error_page, parse_root};
    
    while (lexer.gettype() != "EOF"){
        lexer.get_token();
        if(lexer.gettype() == "" ||lexer.gettype() == "server")
        {
            if(lexer.gettype() == "server")
                init_config(config);
            continue;
        }
        for(int i = 0 ; i < 6; i++)
        {
            if(lexer.gettype() == types[i]){
                foo[i](lexer, config.back());
            }
        }
    }
    return config;
}

int main( ){

    int i = 0;
    std::list<t_config> config;
    try
    {
       config = parse_config("newfile.conf");
       for(int i = 0; i < config.size(); i++)
       {
           std::cout << "host: " << config.front().host << std::endl;
           std::cout << "port: " << config.front().port.front() << std::endl;
           std::cout << "client_max_body_size: " << config.front().body_size_limit << std::endl;
           std::cout << "index: " << config.front().index.front() << std::endl;
           std::cout << "error_page: " << config.front().default_error_page << std::endl;
           std::cout << "root: " << config.front().root << std::endl;
           config.pop_front();
       }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}