# Tic-Tac-Toe Game

## Overview
This C++ Tic-Tac-Toe project embodies a classic game with a modern twist, incorporating a server-client model to enable multiplayer gameplay. The game logic is split between the server and the client, creating a seamless interaction experience for players.

## Server-Side Application  
### GameServer Class  
The **GameServer** class serves as the backbone of the server-side application. It handles incoming connections from clients, manages game instances, and ensures efficient communication between players. The server orchestrates the over-gaming experience, coordinating matches and maintaining a fair and secure environment.   

### GameManager Class  
The **GameManager** class on the server side works in conjunction with the **GameServer**. It manages player turns, validates moves, and determines the game's outcome. The server acts as the central authority, ensuring fair play and enforcing game rules.   

### Game Class  
Working closely with the **GameManager** class, the **Game** class represents the core logic of the Tic-Tac-Toe game. It tracks the game board, evaluates winning conditions, and provides updates to players through the server. 

### RequestManager Class
The **RequestManager** class handles communication with clients, specifically managing user input validation. It interfaces with the client-side components to ensure valid moves from players, contributing to the smooth flow of the game. 

## Client-Side Application
### GameClient Class
The **GameClient** class on the client side establishes a connection with the server, enabling players to participate in the Tic-Tac-Toe game. It manages user input, sends moves to the server, and receives updates on the game state.  

### ResponseManager Class  
Collaborating with the **Game Client**, the **ResponseManager** class validates user input on the client side. It ensures that only valid moves are sent to the server, maintaining the integrity of the game. 

### nlohmann::json Library  
The **nlohmann::json** library handles JSON serialization and deserialization within the application. 

## How to Play
1. **Server Setup:**
   * **Compilation**: To compile the code, use a C++ compiler such as g++. Open a terminal and navigate to the 
     directory containing the source code file ('TicTacToeServer.cpp'). Use the following command to compile the code:
```shell
  g++ -O2 -std=c++11 *.cpp -o executionOutput -Wall
```
2. **Client Setup:**
   * * **Compilation**: To compile the code, use a C++ compiler such as g++. Open a terminal and navigate to the 
     directory containing the source code file ('TicTacClient.cpp'). Use the following command to compile the code:
```shell
  g++ -O2 -std=c++11 *.cpp -o executionOutput -Wall
```
3. **Running the Game: After compilation for both Server and Client, you can run the game using the following command (Make sure you run the server application first. Then run the client application):
```shell
  ./executionOutput
```
4. **Gameplay:**
   * Players take turns making moves by entering row and column numbers.
   * Server and client communicate to update the game board in real-time.

5. **Gameover:**
   * The game concludes when a player wins, the game ties, or an error occurs with the GameServer or GameClient connection.

## Key Features 
* C++ Compiler supporting C++11 or later.
* Server-Client Architecture: Enables multiplayer functionality through a server-client model.
* Real-time Gameplay: Supports dynamic and real-time Tic-Tac-Toe gameplay between connected clients.
* User Input Validation: Ensures that only valid moves are accepted, preventing unfair play.
* JSON Data Handling: Utilizes the **nlohmann::json** library for efficient and structured handling of JSON data in communication between server and client. 

## Acknowledgments
* For more information about nlohmann json please check out the documentation. (https://github.com/nlohmann/json)
* This Tic-Tac-Toe game is a simple demonstration of client-server communication and real-time gameplay.
* Explore and modify the code for learning and experimentation purposes. 
