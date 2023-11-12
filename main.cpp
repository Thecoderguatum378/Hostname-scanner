// Lisence:MIT
// Author: Imran Memon
//Email: javascriptisthebestlanguage@gmail.com



#include <Winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

int main() {
  // Get data about windows sockets
  WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return 1;
    }
// make a for loop, to scan through ip addresses 192.168.1.1-254
    for (int i = 1; i <= 254; ++i) {
        std::string ipAddress = "192.168.1." + std::to_string(i); // convert the ip address to a string incase of a hostname of valid chars
        sockaddr_in saGNI;
        ZeroMemory(&saGNI, sizeof(saGNI));

        saGNI.sin_family = AF_INET;
        saGNI.sin_port = htons(0);

        // Replace deprecated inet_addr with inet_pton
        if (inet_pton(AF_INET, ipAddress.c_str(), &(saGNI.sin_addr)) != 1) {
            std::cerr << "Invalid address: " << ipAddress << std::endl;
            continue;
        }
          / Now use the forloop and printout the Info
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
     // Clean up memory
    WSACleanup();
    return 0;
}

