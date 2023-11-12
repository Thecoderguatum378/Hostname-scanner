# Hostname scannner!


A nice and clean hostname scanner that scans from 192.168.1.1-254 using WinSock
This uses Reverse DNS to search up the hostnames.

Theory:

So in theory,you need to first setup your socket api.
Next, you have to make a forloop and scan through the range with your code.
Now you need to print the host names.

Get the Libraries:

```
#include <Winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib") -> You need to link it with the compiler or else it won't work
```
Now setup the WinSock API.
```

   WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return 1;
    }

```

Loop through IPs on the host:
```
    for (int i = 1; i <= 254; ++i) {
        std::string ipAddress = "192.168.1." + std::to_string(i);
        sockaddr_in saGNI;
        ZeroMemory(&saGNI, sizeof(saGNI));

        saGNI.sin_family = AF_INET;
        saGNI.sin_port = htons(0);

        // Replace deprecated inet_addr with inet_pton
        if (inet_pton(AF_INET, ipAddress.c_str(), &(saGNI.sin_addr)) != 1) {
            std::cerr << "Invalid address: " << ipAddress << std::endl;
            continue;
        }
```

Print the IP with the corresponding hostname:
```c
        char host[NI_MAXHOST];
        int result = getnameinfo(reinterpret_cast<sockaddr*>(&saGNI), sizeof(saGNI),
            host, NI_MAXHOST, nullptr, 0, 0);
        if (result == 0) {
            std::cout << "IP: " << ipAddress << " Hostname: " << host << std::endl;
        }
        else {
            std::cerr << "Unable to resolve IP: " << ipAddress << std::endl;
        }
    }
```

  Now clean up any extra memory:
``` 
  WSAcleanup();
```
  
