#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include "../incs/Client.hpp"

// - Next Step: Static File Serving                                                                                                                              
//
//   right now server responds 200 OK with no content                                                                                        
//
//   1. need to use parsed path to find file on disk                                                                                                               
//   
//   example:
//      Client requests: GET /index.html                                                                                                                            
//      Server looks for: ./www/index.html (some root directory)                                                                                                    
//
//   2. read the file contents                                                                                                                                   
//
//   need to use std::ifstream to open and read the file




class Response
{

    private:
       Client; 
    
    public:
        Response();
        ~Response();



};


#endif
