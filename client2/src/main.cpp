#define _WIN32_WINNT 0x0601 // Windows 7 and later
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include<thread>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

void SendMessages(SOCKET s){

    cout<<"ENTER YOUR CHAT NAME:"<<endl;
    string name;
    getline(cin,name);
    string message;
    while(1){
        getline(cin,message);
        string msg= name+ ":"+message;
        int bytesent=send(s,msg.c_str(),msg.length(),0);
        if(bytesent==SOCKET_ERROR){
            cout<<"Error Sending Message "<<endl;
            break;
        }
        if(message=="quit"||message=="Quit"||message=="QUIT"){
            cout<<"Stopping the Application"<<endl;
            break;
        }


    }
    closesocket(s);
    WSACleanup();
}

void RecieveMessages(SOCKET s) {
    char buffer[4096];
    int recvlength;

    while (1) {
        recvlength = recv(s, buffer, sizeof(buffer), 0);
        if (recvlength <= 0) {
            cout << "Disconnected from Server" << endl;
            break;
        }
        // Print the received message
        cout << string(buffer, recvlength) << endl;
    }
    // Close the socket here but avoid WSACleanup
    closesocket(s);
}



bool InitializeWinSock() {
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

int main() {
    cout << "Client Program Started" << endl;

    if (!InitializeWinSock()) {
        cout << "WinSock initialization failed with error: " << WSAGetLastError() << endl;
        return 1;
    }

    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        cout << "Socket creation failed with error: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }

    int port = 12345;
    string serveraddress = "127.0.0.1";
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);

    if (inet_pton(AF_INET, serveraddress.c_str(), &(serveraddr.sin_addr)) != 1) {
        cout << "inet_pton failed with error: " << WSAGetLastError() << endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    if (connect(s, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR) {
        cout << "Failed to connect to server with error: " << WSAGetLastError() << endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    cout << "Successfully Connected to Server" << endl;

    thread sender(SendMessages, s);
    thread receiver(RecieveMessages, s);

    sender.join();
    receiver.join();

    WSACleanup(); // Cleanup after both threads are done
    return 0;
}
