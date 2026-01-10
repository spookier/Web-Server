#ifndef REQUEST_HPP
# define REQUEST_HPP

#include <string>
#include <map>
#include <iostream>


class Request
{

    private:
        std::string method;     // (GET, POST, DELETE)
        std::string path;        //(/index.html)
        std::string version;     // (HTTP/1.1)
        std::map<std::string, std::string> headers; // (key-value pairs)
        std::string body;        // (POST data)
        bool is_valid;           // (did parsing succeed?)

        Request(const Request &c);                                                                                                               
        Request &operator=(const Request &other);    

    public:
		Request();

        ~Request(); 
                                                                                            

        bool parseRequest(std::string &buffer);

		// GET/POST/DELETE
        bool parseMethod(std::string &buffer);
        
        // PATH
        bool parsePath(std::string &buffer);
        
        // VERSION
        bool parseVersion(std::string &buffer);

};

#endif
