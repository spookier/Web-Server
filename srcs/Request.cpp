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
    if (parseHeaders(buffer) == false)
    {
        std::cout << "Parse HEADERS fail\n";
        return (false);
    }
    if (parseBody(buffer) == false)
    {
        std::cout << "Parse BDOY fail\n";
        return (false);
    }

	this->is_valid = true;

    // std::cout << this->method << " " << this->path << " " << this->version << std::endl;
   std::cout << "BODY: " << this->body << std::endl;

    // std::map<std::string, std::string>::iterator it;
    // for(it = headers.begin(); it != headers.end(); ++it)
    // {
    //    std::cout << it->first << ' ' << it->second << std::endl;
    // }
    //
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


// Parse ALL headers until we hit empty line (\r\n\r\n)
// Make keys lowercase before saving in map
bool Request::parseHeaders(std::string &buffer)
{
    size_t      colon_pos;
    size_t      end_of_line;
    size_t      value_start_pos;
    std::string tmp_key;
    std::string tmp_value;

    // Loop until we hit empty line (start of body or end of headers)
    while (buffer.compare(0, 2, "\r\n") != 0)
    {
        // Find the colon separator
        colon_pos = buffer.find(':');
        if (colon_pos == std::string::npos || colon_pos == 0)
        {
            return (false);
        }

        // Find end of this header line
        end_of_line = buffer.find("\r\n");
        if (end_of_line == std::string::npos || end_of_line == 0)
        {
            return (false);
        }

        // Extract data (before :) and lowercase it
        tmp_key.assign(buffer.begin(), buffer.begin() + colon_pos);
        std::transform(tmp_key.begin(), tmp_key.end(), tmp_key.begin(), ::tolower);

        // Skip colon + space (after ": ") 
        value_start_pos = colon_pos + 1;

        // Skip whitespace after ': '
        while (value_start_pos < end_of_line && buffer[value_start_pos] == ' ')
        {
            value_start_pos++;
        }

        tmp_value.assign(buffer.begin() + value_start_pos, buffer.begin() + end_of_line);

        // Add to headers map
        headers[tmp_key] = tmp_value;

        // Remove this header line from buffer
        buffer.erase(0, end_of_line + 2);
    }

    // Remove the final \r\n
    buffer.erase(0, 2);

    return (true);
}


bool Request::parseBody(std::string &buffer)
{

    size_t content_length;
    std::map<std::string, std::string>::iterator it;

    // Check if content-length header exists
    it = headers.find("content-length");
    if (it == headers.end())
    {
        // No content-length = no body (typical for GET requests)
        this->body = "";
        return (true);
    }

    // Get the content length value
    content_length = static_cast<size_t>(std::atoi(it->second.c_str()));

    // Check if we have enough data in buffer
    if (buffer.length() < content_length)
    {
        std::cout << "Body incomplete: got " << buffer.length() << ", expected " << content_length << std::endl;
        return (false);
    }

    // Extract the body
    this->body.assign(buffer.begin(), buffer.begin() + content_length);
    buffer.erase(0, content_length);

    return (true);
}

const std::string &Request::getMethod() const
{
    return (this->method);
}

const std::string &Request::getPath() const
{
    return (this->path);
}

const std::string &Request::getVersion() const
{
    return (this->version);
}

const std::map<std::string, std::string> &Request::getHeadersMap() const
{
    return (this->headers);
}

const std::string &Request::getBody() const
{
    return (this->body);
}

Request::~Request()
{

}
