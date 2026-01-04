#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <string>
#include <iostream>
#include <map>

class Client                    
{
    private:
        Client();
        int fd;
        std::map<int, std::string> client_requests;     // key = fd -> buffer



	public:
        Client(int fd);
        ~Client();
        Client(const Client &c);
        Client &operator=(const Client &other);

};

#endif