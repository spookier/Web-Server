#include "../incs/Request.hpp"


Request::Request()
{

}


// TO-DO
// +PERFORMANCE: Pass an index instead of using buffer.erase()

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
    if (parseHost(buffer) == false)
    {
        std::cout << "Parse HOST fail\n";
        return(false);
    }

	this->is_valid = true;

    std::cout << this->method << " " << this->path << " " << this->version << std::endl;
   // std::cout << "The rest: " << buffer << std::endl;

    std::map<std::string, std::string>::iterator it;
    for(it = headers.begin(); it != headers.end(); ++it)
    {
       std::cout << it->first << ' ' << it->second << std::endl;
    }

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
    if (end_pos == std::string::npos || end_pos == 0) // Invalid format
    {
        return (false);
    }
    
    this->path.assign(buffer.begin(), buffer.begin() + end_pos);
    buffer.erase(0, end_pos + 1);
    return (true);
}


bool Request::parseVersion(std::string &buffer)
{
    size_t end_pos;

    end_pos = buffer.find("\r\n");
    if (end_pos == std::string::npos || end_pos == 0)
    {
        return (false);
    }

    this->version.assign(buffer.begin(), buffer.begin() + end_pos);
    buffer.erase(0, end_pos + 2); 
    return (true);
}


// Serve default website for HTTP/1.0 | 404 for HTTP/1.1
// Make them lowercase before saving in map
bool Request::parseHost(std::string &buffer)
{
    size_t      end_pos;
    size_t      newline_pos;
    std::string tmp_key;
    std::string tmp_value;
    

    // key "HOST"
    end_pos = buffer.find(':');
    if (end_pos == std::string::npos || end_pos == 0)
    {
        return (false);
    }
    
    // Extract and lowercase the key
    tmp_key.assign(buffer.begin(), buffer.begin() + end_pos);                   
    std::transform(tmp_key.begin(), tmp_key.end(), tmp_key.begin(), ::tolower);
    

    // value "localhost:8080"
    newline_pos = buffer.find("\r\n", end_pos);
    if (newline_pos == std::string::npos || newline_pos == 0)
    {
        return (false);
    }

    tmp_value.assign(buffer.begin() + end_pos + 2, buffer.begin() + newline_pos);
    std::transform(tmp_value.begin(), tmp_value.end(), tmp_value.begin(), ::tolower);
    

    // Add key-value
    headers[tmp_key] = tmp_value;

    buffer.erase(0, newline_pos + 2);
    return (true);
}


Request::~Request()
{
	
}
