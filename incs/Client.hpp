#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <string>
#include <iostream>

class Client                    
{
	private:
		int 		fd;
		std::string buffer;
		bool 		request_complete;

		Client();

	public:
		Client(int fd);
		Client(const Client &c);
		Client &operator=(const Client &other);

		~Client();




		int getFd() const;
		bool isRequestComplete() const;
		std::string getBuffer() const;

		void save_buffer(std::string data);

};

#endif