#define _WIN32_WINNT 0x0601 // Windows 7 and later
#include<iostream>
#include<WinSock2.h>
#include<WinSock.h>
#include<thread>
#include<ws2tcpip.h>
#include<tchar.h>
#include<vector>
#include<algorithm>
using namespace std;

#pragma comment(lib,"ws2_32.lib")


bool Initialize(){
    WSADATA data;
    return WSAStartup(MAKEWORD(2,2),&data)==0;
}


void InteractWithClient(SOCKET clientSocket, vector<SOCKET>&clients){
    //send and recieve here so that main thread there gets free for new connection
    cout<<"Client Connected"<<endl;
    char buffer[4096];
    while(1){
        int byterecvd=recv(clientSocket,buffer, sizeof(buffer),0);
        if(byterecvd<=0){
            cout<<"Client Disconnected"<<endl;
            break; 
        }
        string message(buffer,byterecvd);
        cout<<"Message Recieved from Client: "<<message<<endl;
        for(auto client:clients){
            if(client!=clientSocket){
                send(client,message.c_str(),message.length(),0);
            }
        }
    }
    auto it=find(clients.begin(),clients.end(),clientSocket);
    if(it!=clients.end()){
        clients.erase(it); 
    }

    closesocket(clientSocket);
}

int main(){

    if(!Initialize()){
        cout<<" Winsock Initialization Failed "<<endl;
    }



    cout<<"Server Program"<<endl;


    SOCKET listenSocket=socket(AF_INET,SOCK_STREAM,0);//TCP Kind of Stream for making a TCP Socket

    if(listenSocket==INVALID_SOCKET){
        cout<<"Socket Creation Failed"<<endl;
        return 1;
    }

    //create address structure
    int port=12345;
    sockaddr_in serveraddr;
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(port);

    //convert IP Address(0.0.0.0) and put it inside sin_family in binary format
    if(InetPton(AF_INET,_T("0.0.0.0"),&serveraddr.sin_addr)!=1){
        cout<<"Setting Address Structure Failed"<<endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    //Bind ListenSocket and Server Address Structure
    if(bind(listenSocket,reinterpret_cast<sockaddr*>(&serveraddr),sizeof(serveraddr))==SOCKET_ERROR){
        cout<<"Bind Failed"<<endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    //Listen
    if(listen(listenSocket,SOMAXCONN)==SOCKET_ERROR){
        cout<<"Listen Failed"<<endl;
    }

    cout<<"Server has Started Listening to Port: "<<port<<endl;

    vector<SOCKET>clients;

    while(1){
        //Start accepting connections

        SOCKET clientSocket=accept(listenSocket,nullptr,nullptr);
        if(clientSocket==INVALID_SOCKET){
            cout<<"Invalid Client Socket"<<endl;
        }
        clients.push_back(clientSocket);
        thread t1(InteractWithClient,clientSocket,std::ref(clients));
        t1.detach();
        
    }

    closesocket(listenSocket);
    

    WSACleanup();
    return 0;
}