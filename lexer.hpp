#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include<iostream>
#include<cstring>
#include<fstream>
#include<list>
#include<stack>


class Lexer {
public:
    Lexer(std::string filename);
    ~Lexer();

    Lexer &get_token();
    
    void settype(std::string type);
    void setvalue(std::string value);
    std::string gettype();
    std::string getvalue(int i);
    int get_size_value();
    
    void lex(std::string line);

private:
    std::string filename;
    std::ifstream file;
    std::string type;
    std::vector<std::string> value;
    std::stack<bool> brackets;
    bool type_set;
};

typedef struct s_config {
    std::string host;
    std::list<std::string> port;
	size_t body_size_limit;
	std::list<std::string> index;
	std::string default_error_page;
	std::string root;
	// std::list<t_location> locations;
} t_config ;

bool is_number(const std::string& s);

#endif