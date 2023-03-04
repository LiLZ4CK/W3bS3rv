#ifndef PARSE_HPP
#define PARSE_HPP

#include "lexer.hpp"


void    parse_path_location(Lexer &lexer,t_config &config);  
void    parse_location(Lexer &lexer,t_config &config);
bool    isValidDirective(std::string const &str);
bool    isValidMethod(std::string const &str);
void    parse_location_port(Lexer &lexer,t_config &config);
void    parse_location_http_methods(Lexer &lexer,t_config &config);
void    parse_location_http_redirect(Lexer &lexer,t_config &config);
void    parse_location_file_upload_location(Lexer &lexer,t_config &config);
void    parse_location_body_size_limit(Lexer &lexer,t_config &config);
void    parse_location_root(Lexer &lexer,t_config &config);
void    parse_location_index(Lexer &lexer,t_config &config);


#endif