## Client-Server application in C++

The goal of this project is to write simple client-server application in C++ 
using windows sockets. 

**NOTE:** The project is still depply in development.

Useful links: [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/split/index.html)

To test the program on the current state put this into your `launch.json` file.

```json
    {
        "args": [
            "localhost",
            "127.0.0.1",
            "www.google.com",
            "2001:db8:63b3:1::3490",
            "10.12.110.57"
        ]
    }
```