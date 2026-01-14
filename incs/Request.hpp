#ifndef REQUEST_HPP
# define REQUEST_HPP

#include <string>
#include <map>
#include <iostream>
#include <algorithm>

class Request
{

    private:
        std::string method;     // (GET, POST, DELETE)
        std::string path;        //(/index.html)
        std::string version;     // (HTTP/1.1)

        std::map<std::string, std::string> headers; // HOST / CONNECTION / CONTENT-LENGTH

        std::string body;        // (POST data)
        bool is_valid;           // (did parsing succeed?)

        Request(const Request &c);                                                                                                               
        Request &operator=(const Request &other);    

    public:
		Request();

        ~Request(); 
                                                                                            

        bool parseRequest(std::string &buffer);

		// GET/POST/DELETE + PATH + VERSION
        bool parseMethod(std::string &buffer);
        bool parsePath(std::string &buffer);
        bool parseVersion(std::string &buffer);
        

        // Parse all headers into map
        bool parseHeaders(std::string &buffer);

};

#endif
