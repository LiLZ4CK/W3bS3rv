#include"lexer.hpp"
#include"parse.hpp"


bool isValidMethod(std::string const &str) {
  return (str == "GET" ||
          str == "POST" ||
          str == "DELETE");
}

bool isValidDirective(std::string const &str) {
  return (str == "host" ||
          str == "port" ||
          str == "root" ||
          str == "client_max_body_size" ||
          str == "error_page" ||
          str == "http_methods" ||
          str == "http_redirect" ||
          str == "file_upload_location" ||
          str == "upload" ||
          str == "autoindex" ||
          str == "index" ||
          str == "cgi" ||
          str == "cgi_bin");
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}