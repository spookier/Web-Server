#ifndef REQUEST_HPP
# define REQUEST_HPP

#include <string>
#include <map>
#include <cstdlib>




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
                                                                                            
        // Parse the ENTIRE request
        bool parseRequest(std::string &buffer);


        // Parse the Request line (method+path+version)
        bool parseMethod(std::string &buffer);
        bool parsePath(std::string &buffer);
        bool parseVersion(std::string &buffer);
        

        // Parse all headers in std::map 'headers'
        bool parseHeaders(std::string &buffer);

        // Parse body in std::string 'body' 
        bool parseBody(std::string &body);
        

        // -----------------------------------------

        // GETTERS
        const std::string &getMethod() const;
        const std::string &getPath() const;
        const std::string &getVersion() const;
        const std::map<std::string, std::string> &getHeadersMap() const;
        const std::string &getBody() const;
};

#endif
