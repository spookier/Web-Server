#include "../incs/Request.hpp"

Request::Request()
{
	
}


//  Example Input: "GET /index.html HTTP/1.1\r\n"

std::string Request::parseRequest(const std::string &buffer)
{
	// only for GET
    if (parseMethod(buffer) == false)
    {
        std::cout << "FAIL\n";
		this->is_valid = false;
        return "";
    }
	this->is_valid = true;
	return(buffer);
}


bool Request::parseMethod(const std::string &buffer)
{	
	if (buffer.length() >= 4 && buffer.compare(0, 4, "GET ") == 0)
	{
        std::cout << "You called a GET method ! \n";
		this->method = "GET ";
        return (true);
    }
    else if (method == "POST")
    {
        std::cout << "You called a POST method !\n";
        return (true);
    }
    else if (method == "DELETE")
    {
        return (true);
    }
    else
    {
        return (false);
    }
}


Request::~Request()
{
	
}
