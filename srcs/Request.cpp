#include "../incs/Request.hpp"

Request::Request()
{

}

bool Request::parseRequest(std::string &buffer)
{
	// GET/POST/DELETE

    this->is_valid = false;
    if (parseMethod(buffer) == false)
    {
        std::cout << "Parse METHOD failed\n";
        return (false);
    }
    if (parsePath(buffer) == false)
    {
        std::cout << "Parse PATH fail\n";
        return (false);
    }
    if (parseVersion(buffer) == false)
    {
        std::cout << "Parse VERSION fail\n";
        return (false);
    }   
    
	this->is_valid = true;
    
    std::cout << " " << this->method << " " << this->path << " " << this->version << std::endl;
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
            this->method = "GET";
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
    size_t end_pos;

    end_pos = buffer.find(' ');
    if(end_pos == std::string::npos || end_pos == 0) // Invalid format
    {
        return (false);
    }
    
    this->path.assign(buffer.begin(), buffer.begin() + end_pos);
    buffer.erase(0, end_pos + 1);
    return(true);
}


bool Request::parseVersion(std::string &buffer)
{
    size_t end_pos;

    end_pos = buffer.find("\r\n");
    if(end_pos == std::string::npos || end_pos == 0)
    {
        return(false);
    }

    this->version.assign(buffer.begin(), buffer.begin() + end_pos);
    buffer.erase(0, end_pos + 1); // check this
    return(true);
}


Request::~Request()
{
	
}
