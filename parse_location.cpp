#include"parse.hpp"

void	init_location(std::list<t_location> &loc)
{
	t_location location;

    location.http_redirect.status_code = "";
    location.http_redirect.url = "";
    location.file_upload_location = "";
    location.body_size_limit = 0;
    location.root = "";
    location.index.clear();
    location.port.clear();
    location.http_methods.clear();
    location.path_location = "";
    
	loc.push_back(location);
}

void    parse_location(Lexer &lexer,t_config &config) {

    std::string types[] = {"port","http_method","http_redirect","file_upload_location",\
    "client_max_body_size","root","index"};
	void	(*foo[]) (Lexer &, t_config &) = {parse_location_port , parse_location_http_methods, parse_location_http_redirect, parse_location_file_upload_location,\
        parse_location_body_size_limit, parse_location_root, parse_location_index};

	init_location(config.locations);

    std::cout << lexer.getvalue(0) << std::endl; 
    parse_path_location(lexer, config);
    while (lexer.brackets.size() == 2)
    {
        lexer.get_token();
        for(int i = 0; i < 7; i++) {
            if(lexer.gettype() == types[i]) {
                foo[i](lexer, config);
                break;
            }
        }
        if(!isValidDirective(lexer.gettype()) && lexer.gettype() != "" && 
            lexer.gettype() != "EOF"){
                throw std::runtime_error("Error: invalid directive");
            }
        // std::cout << lexer.gettype() +  " ==> " + lexer.getvalue(0) << std::endl;
    }
}