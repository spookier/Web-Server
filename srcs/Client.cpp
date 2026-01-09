#include "../incs/Client.hpp"

Client::Client(int _fd) : fd(_fd), request_complete(false)
{
    // @ DEBUG
    std::cout << "Client created for fd: " << this->fd << std::endl;
}

Client::Client(const Client &c) : fd(c.fd), buffer(c.buffer), request_complete(c.request_complete)
{
    std::cout << "Client copy constructor called for fd: " << this->fd << std::endl;
}

Client &Client::operator=(const Client &other)
{
    if (this != &other)
    {
        this->fd = other.fd;
        this->buffer = other.buffer;
        this->request_complete = other.request_complete;
    }
    return *this;
}

void Client::save_buffer(std::string _buffer)
{
    buffer.append(_buffer);

    // Check for end of HTTP header
    if (buffer.find("\r\n\r\n") != std::string::npos)
    {
        request_complete = true;
    }
}

int Client::getFd() const
{
    return(this->fd);
}

bool Client::isRequestComplete() const
{
    return(this->request_complete);
}

std::string Client::getBuffer() const
{
	return (this->buffer);
}


std::string Client::getRequest()
{
	this->buffer = request.parseRequest(this->buffer);
	return(this->buffer);
}





Client::~Client()
{
        std::cout << "Client copy DECONSTRUCTOR called for fd: " << this->fd << std::endl;
}
