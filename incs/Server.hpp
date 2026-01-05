#ifndef SERVER_HPP
# define SERVER_HPP

#include "Client.hpp"
#include <sys/socket.h>
#include <errno.h>
#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <netinet/in.h>
#include <vector>
#include <poll.h>
#include <unistd.h>
#include <cstdio>
#include <map>

class Server
{
	private:
		Server(const Server &c);
		Server &operator=(const Server &c);

		int 						socketfd;
		int 						bindfd;
		int 						listenfd;
		int							acceptfd;
		
		int							max_cons;
		
		ssize_t 					bytes_read;




		char 						buffer[1024];

		struct sockaddr_in          sockaddr;
		struct pollfd               listen_pollfd;
		struct sockaddr_in 			client_addr;
		socklen_t 					client_addr_len;


		std::vector<struct pollfd>	poll_fds;
		std::vector<Client>			client_list;



	public:
		Server();
		~Server();

		void socket_init();
		void bind_init();
		void listen_init();

		void server_loop();
		void cleanup();
};


#endif