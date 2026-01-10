#include "../incs/Request.hpp"

Request::Request()
{
	
}

std::string Request::parseRequest(std::string &buffer)
{
	// GET/POST/DELETE
    if (parseMethod(buffer) == "")
    {
        std::cout << "Parse Method failed\n";
		this->is_valid = false;
        return "";
    }
    
    // if (parsePath(buffer) == "")
    // {
    //     std::cout << "Parse PATH fail\n";
    //     this->is_valid = false;
    //     return "";
    // }
    // 
	this->is_valid = true;
	return(buffer);
}


//  Example Input: "GET /index.html HTTP/1.1\r\n"

std::string Request::parseMethod(std::string &buffer)
{	
    if (buffer.length() >= 4)
    {
        if (buffer.compare(0, 4, "GET ") == 0)              //  GET
        {
            std::cout << "You called a GET method ! \n";
            this->method = "GET ";
            buffer.erase(0, 4);                             // Shorten the buffer for faster processing with erase()

            return (buffer);
        }
        else if (buffer.compare(0, 5, "POST ") == 0)        // POST
        {
            std::cout << "You called a POST method !\n";
            this->method = "POST";
            buffer.erase(0, 5);

            return (buffer);
        }
        else if (buffer.compare(0, 7, "DELETE ") == 0)      // DELETE
        {
            this->method = "DELETE";
            buffer.erase(0, 7);
            std::cout << "You called a DELETE method !\n";

            return (buffer);
        }
        else
            return (""); // false
    }
    return ("");
}
//
// bool Request::parsePath(const std::string &buffer)
// {
//
//     return(false);
// }
//


Request::~Request()
{
	
}
