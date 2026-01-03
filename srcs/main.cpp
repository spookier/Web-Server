#include "../incs/main.hpp"

void cleanup(std::vector<struct pollfd> &poll_fds)
{
	for(size_t i = 0; i < poll_fds.size(); ++i)
	{
		if(poll_fds[i].fd)
		{
			close(poll_fds[i].fd);
		}
	}
}


void exec_server(int &socketfd, std::vector<struct pollfd> &poll_fds)
{
	int acceptfd;
	char buffer[1024];
	ssize_t bytes_read;

	struct sockaddr_in client_addr;
	socklen_t client_addr_len;


	while (true)
	{
		int ret = poll(&poll_fds[0], poll_fds.size(), -1);		// blocks here until an event happens
		if (ret < 0)
		{
			printf("Poll failed: %s\n", strerror(errno));
			break;
		}

		for (size_t i = 0; i < poll_fds.size(); ++i)
		{
			if (poll_fds[i].revents & POLLIN)						// check return events (response)
			{
				if (poll_fds[i].fd == socketfd)						// RING RING someone wants to join
				{
					client_addr_len = sizeof(client_addr);

					acceptfd = accept(socketfd, (struct sockaddr *)&client_addr, &client_addr_len);
					if (acceptfd < 0)
						printf("Accept failed: %s\n", strerror(errno));
					else								
					{
						struct pollfd new_fd;						// We create a struct for this client and add him to our list

						new_fd.fd = acceptfd;
						new_fd.events = POLLIN;
						new_fd.revents = 0;
						
						fcntl(new_fd.fd, F_SETFL, O_NONBLOCK);
						poll_fds.push_back(new_fd);
					}
				}
				else												// Its not a new connection, so it means its an already existing client
				{
					bytes_read = read(poll_fds[i].fd, buffer, 1024);


					if (bytes_read < 0 && errno != EWOULDBLOCK)			// Error
					{
						printf("Read failed: %s\n", strerror(errno));
						break ;
					}
					else if(bytes_read == 0)							// Disconnection
					{
						printf("User [%d] Disconnected\n\n", poll_fds[i].fd);
						close(poll_fds[i].fd);
						poll_fds.erase(poll_fds.begin() + i);
						//--i;
						break ;
					}
																		// OK, Data received
					buffer[bytes_read] = 0;
					printf("[%d]: %s\n", poll_fds[i].fd, buffer);
				}
			}
		}
	}
}

int main()
{
	struct sockaddr_in addr;

	std::vector<struct pollfd> poll_fds;
	struct pollfd listen_poolfd;


	int socketfd;
	int bindfd;
	int listenfd;


	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketfd < 0)
		printf("Socket failed: %s\n", strerror(errno));

	fcntl(socketfd, F_SETFL, O_NONBLOCK); 
	
	// Clear the structure memory
    memset(&addr, 0, sizeof(addr));

	addr.sin_family 		= AF_INET;          // Use IPv4
    addr.sin_addr.s_addr 	= INADDR_ANY;   	// Accept connections from any interface
    addr.sin_port 			= htons(8080);      // Port 8080 with Big Endian order

	bindfd = bind(socketfd, (struct sockaddr *)&addr, sizeof(addr));
	if(bindfd != 0)
		printf("Bind failed: %s\n", strerror(errno));


	listenfd = listen(socketfd, 5);
	if(listenfd != 0)
		printf("Listen failed: %s\n", strerror(errno));


	listen_poolfd.fd = socketfd;	
	listen_poolfd.events = POLLIN; 
	poll_fds.push_back(listen_poolfd);

	exec_server(socketfd, poll_fds);
	

	// make a cleanup function to close all fds on fail/exit
	if(!poll_fds.empty())
		cleanup(poll_fds);
	
	if(listen_poolfd.fd)
		close(listen_poolfd.fd);
	if(listenfd)
		close(listenfd);
	addr.sin_port 			= htons(0);
	if(bindfd)
		close(bindfd);
	if(socketfd)
		close(socketfd);

	return(0);
}
