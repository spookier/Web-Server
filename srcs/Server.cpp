#include "../incs/Server.hpp"

Server::Server()
{

	this->max_cons = 5;

	socket_init();
	bind_init();
	listen_init();
	//server_loop();
}

void Server::socket_init()
{
	this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socketfd < 0)
	{
		printf("Socket failed: %s\n", strerror(errno));
		return ;
	}
	fcntl(this->socketfd, F_SETFL, O_NONBLOCK);
}

void Server::bind_init()
{
	// Clear the structure memory
	memset(&this->sockaddr, 0, sizeof(this->sockaddr));

	this->sockaddr.sin_family 		= AF_INET;          // Use IPv4
	this->sockaddr.sin_addr.s_addr 	= INADDR_ANY;   	// Accept connections from any interface
	this->sockaddr.sin_port 		= htons(8080);      // Port 8080 with Big Endian order

	this->bindfd = bind(socketfd, (struct sockaddr *)&this->sockaddr, sizeof(this->sockaddr));
	if(this->bindfd != 0)
	{
		printf("Bind failed: %s\n", strerror(errno));
		return ;
	}
}

void Server::listen_init()
{

	this->listenfd = listen(socketfd, max_cons);
	if(this->listenfd != 0)
	{
		printf("Listen failed: %s\n", strerror(errno));
		return ;
	}

	this->listen_pollfd.fd = this->socketfd;
	this->listen_pollfd.events = POLLIN;
	poll_fds.push_back(listen_pollfd);
}

void Server::server_loop()
{
	while (true)
	{
		int ret = poll(&poll_fds[0], poll_fds.size(), -1); 			// blocks here until an event happens
		if (ret < 0)
		{
			printf("Poll failed: %s\n", strerror(errno));
			break;
		}

		for (size_t i = 0; i < poll_fds.size(); ++i)
		{
			if (poll_fds[i].revents & POLLIN)					 	// Check responses
			{
				if (poll_fds[i].fd == socketfd) 					// RING RING someone wants to join
				{
					client_addr_len = sizeof(client_addr);

					acceptfd = accept(socketfd, (struct sockaddr *)&client_addr, &client_addr_len);
					if (acceptfd < 0)
						printf("Accept failed: %s\n", strerror(errno));
					else
					{
						struct pollfd new_fd; 					// We create a struct for this client and add him to our list

						new_fd.fd = acceptfd;
						new_fd.events = POLLIN;
						new_fd.revents = 0;

						fcntl(new_fd.fd, F_SETFL, O_NONBLOCK);
						poll_fds.push_back(new_fd);
					}
				}
				else													// not a new connection, so it means its an already existing client
				{
					bytes_read = recv(poll_fds[i].fd, buffer, sizeof(buffer), 0);
					if (bytes_read < 0 && errno != EWOULDBLOCK)			// error case
					{
						printf("Read failed: %s\n", strerror(errno));
						break ;											
					}
					else if(bytes_read == 0)							// user disconnected case
					{
						printf("User [%d] Disconnected\n\n", poll_fds[i].fd);
						close(poll_fds[i].fd);
						poll_fds.erase(poll_fds.begin() + i);
						--i;
						break ;
					}
																		
					buffer[bytes_read] = 0;								// OK case, data received
					printf("[%d]: %s\n", poll_fds[i].fd, buffer);	
				}
			}
		}
	}
}


void Server::cleanup()
{
	for(size_t i = 0; i < poll_fds.size(); ++i)
	{
		if(poll_fds[i].fd)
		{
			close(poll_fds[i].fd);
		}
	}
	if(acceptfd)
		close(acceptfd);
	if(listen_pollfd.fd)
		close(listen_pollfd.fd);
	if(bindfd)
		close(bindfd);
	if(socketfd)
		close(socketfd);
}



Server::~Server()
{
	cleanup();
}