#include"parse.hpp"

void    parse_path_location(Lexer &lexer,t_config &config) {
    if(lexer.get_size_value() != 1)
        throw std::runtime_error("Error: path location take one value");
    config.locations.back().path_location = lexer.getvalue(0);
}

void    parse_location_port(Lexer &lexer,t_config &config) {
    
    if(lexer.get_size_value() > 3 || lexer.get_size_value() == 0)
        throw std::runtime_error("Error: port take between one and three values");
    for(int i = 0; i < lexer.get_size_value(); i++) {
        if(!is_number(lexer.getvalue(i)))
            throw std::runtime_error("Error: port take just numbers");
        config.locations.back().port.push_back(lexer.getvalue(i));
    }
}

void    parse_location_http_methods(Lexer &lexer,t_config &config) {
    if(lexer.get_size_value() < 1 || lexer.get_size_value() > 3)
        throw std::runtime_error("Error: http method take between one and three values");
    for(int i = 0; i < lexer.get_size_value(); i++) {
        if(!isValidMethod(lexer.getvalue(i)))
            throw std::runtime_error("Error: http method take just GET, POST, DELETE");
        config.locations.back().http_methods[lexer.getvalue(i)] = true;
    }
}

void  parse_location_http_redirect(Lexer &lexer,t_config &config) {
    if(lexer.get_size_value() != 2)
        throw std::runtime_error("Error: http redirect take status code and url");
    if(!is_number(lexer.getvalue(0)))
        throw std::runtime_error("Error: http redirect status code take just numbers");
    config.locations.back().http_redirect.status_code = lexer.getvalue(0);
    config.locations.back().http_redirect.url = lexer.getvalue(1);
}

void    parse_location_file_upload_location(Lexer &lexer,t_config &config) {
    if(lexer.get_size_value() != 1)
        throw std::runtime_error("Error: file upload location take one value");
    config.locations.back().file_upload_location = lexer.getvalue(0);
}

void    parse_location_body_size_limit(Lexer &lexer,t_config &config) {
    if(lexer.get_size_value() != 1)
        throw std::runtime_error("Error: body size limit take one value");
    if(!is_number(lexer.getvalue(0)))
        throw std::runtime_error("Error: body size limit take just numbers");
    config.locations.back().body_size_limit = std::stoi(lexer.getvalue(0));
}

void    parse_location_root(Lexer &lexer,t_config &config) {
    if(lexer.get_size_value() != 1)
        throw std::runtime_error("Error: root take one value");
    config.locations.back().root = lexer.getvalue(0);
}

void  parse_location_index(Lexer &lexer,t_config &config) {
    if(lexer.get_size_value() < 1)
        throw std::runtime_error("Error: index take at least one value");
    for(int i = 0; i < lexer.get_size_value(); i++) {
        config.locations.back().index.push_back(lexer.getvalue(i));
    }
}