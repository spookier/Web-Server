#include "../incs/Request.hpp"

Request::Request()
{

}

bool Request::parseRequest(std::string &buffer)
{
	// GET/POST/DELETE
    if (parseMethod(buffer) == false)
    {
        std::cout << "Parse METHOD failed\n";
		this->is_valid = false;
        return (false);
    }
    if (parsePath(buffer) == false)
    {
        std::cout << "Parse PATH fail\n";
        this->is_valid = false;
        return (false);
    }
    
	this->is_valid = true;
    
    std::cout << this->method << this->path << std::endl;
	return(true);
}


//  Example Input: "GET /index.html HTTP/1.1\r\n"

bool Request::parseMethod(std::string &buffer)
{	
    if (buffer.length() >= 4)
    {
        if (buffer.compare(0, 4, "GET ") == 0)              //  GET
        {
            std::cout << "You called a GET method ! \n";
            this->method = "GET ";
            buffer.erase(0, 4);                             // Shorten the buffer for faster processing with erase()

            return (true);
        }
        else if (buffer.compare(0, 5, "POST ") == 0)        // POST
        {
            std::cout << "You called a POST method !\n";
            this->method = "POST";
            buffer.erase(0, 5);

            return (true);
        }
        else if (buffer.compare(0, 7, "DELETE ") == 0)      // DELETE
        {
            this->method = "DELETE";
            buffer.erase(0, 7);
            std::cout << "You called a DELETE method !\n";

            return (true);
        }
        else
            return (false); // false
    }
    return (false);
}

bool Request::parsePath(std::string &buffer)
{
    size_t space_position;

    space_position = buffer.find(' ');

    if(space_position == std::string::npos || space_position == 0) // Invalid format
    {
        return (false);
    }
    
    this->path.assign(buffer.begin(), buffer.begin() + space_position);
    buffer.erase(0, space_position + 1);
    return(true);
}



Request::~Request()
{
	
}
