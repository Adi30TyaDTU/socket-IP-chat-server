# Socket Chat App

## Description
This is a chat application server using sockets for real-time communication.

## Features
- Multi-client support
- Real-time message exchange

## Installation
1. Clone the repository
2. Navigate to the project directory
3. Compile and run the server and client applications

## Usage
- Run the server first, then run one or more clients.
- Follow the on-screen prompts to start chatting.

## License
This project is licensed under the MIT License.



# Socket Chat Application

## Description

The **Socket Chat Application** is a server-based communication system that enables real-time messaging between multiple clients connected to a specific server IP. Built using socket programming, this application allows users to send and receive messages instantly, making it suitable for various chat scenarios. The architecture supports scalability and can be extended to accommodate more advanced features.

## Features

- **Multi-User Support**: Allows multiple clients to connect to the same server IP, facilitating group chats and individual messaging.
- **Real-Time Communication**: Messages are exchanged in real time, ensuring seamless interaction.
- **Cross-Platform Compatibility**: The application can be run on different platforms, given that they support socket programming.
- **Easy to Use**: Simple command-line interface for sending and receiving messages.

## Installation

1. **Clone the repository**:

   ```bash
   git clone https://github.com/your-username/socket-chat-app.git


2. **Navigate to the project directory**:

    ```bash
   cd socket-chat-app


3. **Compile the code (Make sure to have a C++ compiler installed)**:

    ```bash
   g++ -o server server/main.cpp
   g++ -o client client/main.cpp


4. **Run the server**:

    ```bash
   ./server



5. **Run the client**:

    ```bash
   ./client


## Usage

- **Starting the Server**: Launch the server application first. It will listen for incoming client connections.
  
- **Connecting Clients**: Run one or more client applications. Enter the server IP address and port number to connect. Once connected, clients can send and receive messages.

- **Sending Messages**: Type your message in the client terminal and press Enter to send it. All connected clients will see the message.

## Future Improvements

The current implementation serves as a basic chat application. Future improvements could include:

- **User Authentication**: Implement user registration and login functionalities to secure access to the chat system.
  
- **Message History**: Store messages in a database to allow users to view past conversations.
  
- **Group Chat Functionality**: Enable users to create and join different chat rooms.
  
- **File Transfer**: Allow users to send files, images, or multimedia content.
  
- **WebSocket Support**: Extend the application to use WebSockets for better real-time communication in web environments.
  
- **Graphical User Interface (GUI)**: Develop a user-friendly GUI to enhance user experience.
