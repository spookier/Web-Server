<div align="center">
<img src="https://github.com/user-attachments/assets/dcceb154-1873-4421-a28f-d52a57e2c4e2" width="500" />



  
## A fully functional HTTP/1.1 server written from scratch in **C++98**  
  
  Non-blocking I/O, configuration file parsing, static file serving, file uploads, CGI execution, and more


</div>


## What It Does

### The Real Stuff
- **HTTP/1.1**: GET, POST, DELETE. That's all you need
- **Non-blocking I/O**: One thread, poll()/epoll/kqueue
- **Multi-port**: Because why not serve different sites on different ports?
- **Static Files**: HTML, CSS, JS, images. The basics that actually matter
- **File Upload**: Clients can send you files. Revolutionary
- **CGI**: Run PHP, Python, whatever. Fork, exec, pipe. Unix as intended
- **Config File**: NGINX-style because their config syntax is actually good

### More Features (that people actually use)
- **Per-route Config**: Different rules for different URLs
- **HTTP Redirects**: 301s, 302s... etc
- **Directory Listing**: Auto-generate indexes when you're too lazy to make index.html
- **Custom Error Pages**: Your 404 can look better than the default
- **Request Size Limits**: Because people will try to upload 10GB files
- **Default Files**: index.html for directories. Common sense.


## Building

```bash
make
```

## Usage

```bash
./webserv [configuration_file]
```

If no configuration file is provided, the server will look for a default configuration


## Testing

### With curl (the right way)

```bash
# GET request
curl http://localhost:8080/

# POST some data
curl -X POST -d "data=value" http://localhost:8080/form

# Upload a file
curl -X POST -F "file=@image.jpg" http://localhost:8080/uploads

# DELETE something
curl -X DELETE http://localhost:8080/uploads/file.txt
```

### With a Browser (the easy way)

Go to `http://localhost:8080`

### Stress Testing (the fun way)

Break it. Seriously, try to break it.

```bash
# Siege it
siege -c 100 -t 30s http://localhost:8080

# Apache Bench it
ab -n 10000 -c 100 http://localhost:8080/

# Or write your own script
# Python, Go, Rust, whatever
# Just hammer it with concurrent connections
```
---

## Notes

- HTTP is just text over TCP
- Non-blocking I/O is the only way that scales  
- poll() is your best friend
- The RFCs are actually readable (mostly)
- You don't need a framework to build real software
- System calls are beautiful in their simplicity

- [RFC 2616](https://tools.ietf.org/html/rfc2616) - HTTP/1.1 (it's long but worth it)
- [RFC 3875](https://tools.ietf.org/html/rfc3875) - CGI
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/) - Best intro to sockets
- man 2 socket, man 2 poll, man 2 fork = The real docs
- Build it yourself. Understand it completely. Then decide what abstractions are worth it
- *"What I cannot create, I do not understand." - Richard Feynman*
