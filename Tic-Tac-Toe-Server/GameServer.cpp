#include "GameServer.h"
#include "RequestManager.h"
#include <nlohmann/json.hpp>
#include <iostream>

namespace DashLine {
  void Dashes() {
    std::cout << "----------\n";
  }
}
using namespace DashLine;

/* -------------------------------------------------------------
 * NAMESPACE NAME: GameInfo
 * -------------------------------------------------------------
 * @brief Namespace containing classes and structures related to
 *        game information in the Tic-Tac-Toe application.
 *
 * @note Please refer to each class and structure documentation
 *       for better understanding.
 * -------------------------------------------------------------
 **/
namespace GameInfo {
  IRequestManager *request_manager = new Request_Manager::RequestManager;
  Game game;
  GameManager game_manager;
  Status status;
  PromptingUser prompting;
  Player player;
}
using namespace GameInfo;

/* -------------------------------------------------------------------
 * NAMESPACE NAME: Json
 * -------------------------------------------------------------------
 * @brief Namespace containing utilities for handling JSON data
 *        using the nlohmann::json library.
 *
 * The Json namespace provide a single instance of nlohmann::json,
 * named jsondata, for managing and manipulating JSON data within
 * the application.
 *
 * @note Developers should refer to the [nlohmann::json documentation]
 *       (https://github.com/nlohmann/json) for detailed informaion
 *       on JSON data handling.
 * -------------------------------------------------------------------
 */
namespace Json {
  nlohmann::json json_data;
}


/* ----------------------------------------------------------------------------------------------------------
 * CONSTRUCTOR NAME: GameServer
 * ----------------------------------------------------------------------------------------------------------
 * @brief Initialize the GameServer by creating a server socket and binding it to a specific IP protocol
 *        and port.
 *
 * This constructor is responsible for setting up the GameServer object. It creates an unbound server socket
 * and configures it to listen on a designated port (8080) of the specified IP Protocol (IPv4). The server is
 * designed to accept connections on any available network interface (INADDR_ANY). If the socket creation or
 * server startup encounters errors, it throws a std::runtime_error.
 *
 * @details The constructor sets up the server address structure with the IPv4 family,
 *          port 8080, and INADDR_ANY for the server to listen on all available network interfaces,
 *          It then calls the StartServer() method to perform the socket creation, binding, and
 *          other necessary setup.
 *
 * @throws std::runtime_error if there is an error creating the server socket or starting the server.
 *
 * ----------------------------------------------------------------------------------------------------------
 */
GameServer::GameServer() : client_address_size(sizeof(client_address)) {
  // Assign server address to its address and port.
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8080);
  server_address.sin_addr.s_addr = INADDR_ANY;
  if (StartServer() != 0) {
    throw std::runtime_error("Error! Starting server.");
  }
}

GameServer::~GameServer() {
  close(server_socket);
  close(client_socket);
}

/* -------------------------------------------------------------------------------------------
 * FUNCTION NAME: StartServer
 * -------------------------------------------------------------------------------------------
 * @brief Start the server by creating, configuring, and binding the socket.
 *
 * This method performs the necessary steps to set up the server socket, including
 * socket creation, setting socket options for reuse, and binding the socket to
 * the specified address and port.
 *
 * @details The method creates a socket using PF_INET (IPv4) and SOCK_STREAM (TCP).
 *          It then sets the SO_REUSEADDR option to allow reusing the same port after the
 *          socket is closed. After that, it binds the socket to the specified server address.
 *
 * @throws std::runtime_error if there is an error creating the socket,
 *                            setting socket options, or binding the socket.
 *
 * @return EXIT_SUCCESS if the server setup is successful.
 * -------------------------------------------------------------------------------------------
 */
int GameServer::StartServer() {
  // Create a server socket
  server_socket = socket(PF_INET, SOCK_STREAM, 0);
  if (server_socket == -1) {
    throw std::runtime_error("Error! Creating a socket");
  }
  
  // Reuse the address after closing the socket
  int yes = 1;
  if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
    throw std::runtime_error("Error! Reusing socket after closure.");
  }
  
  // Bind the socket to an address and port
  if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
    throw std::runtime_error("Error! Binding to socket");
  }
  
  return EXIT_SUCCESS;
}

/* ------------------------------------------------------------------------------
 * FUNCTION NAME: StartListen
 * ------------------------------------------------------------------------------
 * @brief Set up the server to listen for incoming client connection.
 *
 * This method sets up the server socket to accept incoming connections
 * by calling the listen function with a backlog value of 1. It's then accepts
 * a client connection using the accept function.
 *
 * @throws std::runtime_error if there is an error during listening or accepting.
 *
 * @return EXIT_SUCCESS if listening and accepting a connection are successful.
 * ------------------------------------------------------------------------------
 */
int GameServer::StartListen() {
  // Listen for incoming connections.
  if (listen(server_socket, 1) == -1) {
    throw std::runtime_error("Error! listening for Client connection.");
  }
  std::cout << "Server is listening for incoming connections..." << std::endl;
  
  // Accept a client connnection.
  client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_size);
  if (client_socket == -1) {
    throw std::runtime_error("Error! Connecting to Client");
  }
  std::cout << "Client connected" << std::endl;
  
  return EXIT_SUCCESS;
}

/* ------------------------------------------------------------------------------------------------
 * FUNCTION NAME: SendData
 * ------------------------------------------------------------------------------------------------
 * @brief Sends a JSON-formatted string to the connected client through the specified socket.
 *
 * This function is responsible for constructing a JSON-formatted string that represents both a
 * status message and game_board updates. The resulting JSON string is then sent to the connected
 * client through the specified socket.
 *
 * @details The function uses nlohmann json library to create a JSON object containing
 *          the provided status message and game board data. This JSON oject is then serialized
 *          into a string and the string is sent to the client. If an errors occurs during the
 *          sending process, a std::runtime_error is thrown.
 *
 * @param status_message A string containing the status message to be included in the JSON string.
 * @param game_board     A string containing the game board data to be included in the JSON string.
 *
 * @throws std::runtime_error if an error occurs during sending.
 *
 * @return No explicit return value.
 * ------------------------------------------------------------------------------------------------
 */
void GameServer::SendData(const char *status_message, const char *game_board) {
  Json::json_data["status_message"] = status_message;
  Json::json_data["game_board"]     = status.game_board;
  std::string serialized_data       = Json::json_data.dump();
  size_t serialized_data_size       = serialized_data.size();
  ssize_t data_bytes_sent = send(client_socket, serialized_data.c_str(), serialized_data_size, 0);
  if (data_bytes_sent == -1) {
    throw std::runtime_error("Error! Sending data to Client");
  }
}

/* ----------------------------------------------------------------------------------------------------
 * FUNCTION NAME: ParseReceivedRowAndColumnNumber
 * ----------------------------------------------------------------------------------------------------
 * @brief Parses a JSON-formatted string to extract row and column numbers.
 *
 * This function is responsible for parsing a JSON-formatted string received from
 * the client. The JSON object is expected to contain "row" and "column" fields,
 * representing the row number and column number, respectively. The parsed values are stored
 * in the specified array.
 *
 * @details The function uses the nlohmann json library to parse the received JSON-formatted string.
 *          If successful, the parsed row and column numbers are stored in the client_move array.
 *          If an error occurs during parsing, the exception is caught, and an error message is printed
 *          to std::cerr.
 *
 * @param received_data A JSON-formatted string containing the row and column numbers.
 * @param client_move Pointer to an array that will store the parsed row and column numbers.
 * @param size The size of the received data (in bytes).
 *
 * @return No explicit return value.
 * ----------------------------------------------------------------------------------------------------
 */
void GameServer::ParseReceivedRowAndColumnNumber(const char *received_data, int *client_move, size_t size) {
  try {
    Json::json_data = nlohmann::json::parse(received_data);
    client_move[0]  = Json::json_data["row"];
    client_move[1]  = Json::json_data["column"];
  } catch (const std::exception& e) {
    std::cerr << "Error parsing JSON: " << e.what() << std::endl;
  }
}

/* -----------------------------------------------------------------------------------------------------------
 * FUNCTION NAME: ReceiveData
 * -----------------------------------------------------------------------------------------------------------
 * @brief Receives an serialized JSON-formatted string from the connected client through the specified socket.
 *
 * This function is responsible for receiving data from the client, which is expected to be a
 * serialized JSON-formatted string containing information such as row and column numbers.
 *
 * @details The function uses the provided socket to receive a serialized JSON-formatted string
 *          from the client. The received data is then parsed using the nlohmann json library to
 *          extract information. If an error occurs during the reception process, a
 *          std::runtime error is thrown.
 *
 * @param client_move Pointer to an array that will store the parsed data (e.g., row and column nubmers).
 *
 * @throws std::runtime_error if an error occurs during data reception.
 *
 * @return No explicit return value.
 * -----------------------------------------------------------------------------------------------------------
 */
void GameServer::ReceiveData(int* client_move) {
  char received_data[256];
  ssize_t buffer_bytes_read = recv(client_socket, received_data, sizeof(received_data), 0);
  if (buffer_bytes_read == -1) {
    throw std::runtime_error("Error! Receiving row and column number from Client.");
  }
  received_data[buffer_bytes_read] = '\0';
  ParseReceivedRowAndColumnNumber(received_data, client_move, buffer_bytes_read);
}

/* ---------------------------------------------------------------------------------------
 * FUNCTION NAME: IsServerMove
 * ---------------------------------------------------------------------------------------
 * @brief Send server data to the client.
 *
 * This function sends game-related data to the client, including the game board
 * and a status message. The status messages can be a server winning message,
 * a tie game message, or an error message in case of an invalid move.
 *
 * @details If the server wins, a winning message and the serialized winning game board
 *          are sent to the client, and the program terminates.
 *
 *          If the game is tied, a tie game message and the serialized game board are sent
 *          to the client, and the program terminates.
 *
 *          If none of the above conditions are met, the serialized updated game board
 *          is sent to the client, and control is given to the client to make a move.
 *
 * @param move_counter The current move counter.
 *
 * @return True if the game is over (either server won or tied), false otherwise.
 * ---------------------------------------------------------------------------------------
*/
bool GameServer::IsServerMove(int move_counter) {
  while (1) {
    std::cout << status.game_board;
    prompting.PlayerTurn('X');
    prompting.UserForRowNumber();
    player.row    = request_manager->GetValidatedUserInput(player.row, 1, 3, 'R');
    prompting.UserForColumnNumber();
    player.column = request_manager->GetValidatedUserInput(player.column, 1, 3, 'C');
    status        = game_manager.MakeMove(player.row, player.column, 'X', move_counter);
    if (status.status_code == "Gameover") {
      if (move_counter == 9 && status.letter == 'T') {
        std::cout << status.game_board;
        std::cout << "TIE GAME" << std::endl;
        const char* tie_game_message = "TIE GAME";
        const char* final_game_board = status.game_board.c_str();
        SendData(tie_game_message, final_game_board);
        
        // Successful sending tie message and game board to Client.
        return true;
      }
      std::cout << status.game_board;
      std::cout << "You win" << std::endl;
      const char* winning_message = "Server won";
      const char* game_board      = status.game_board.c_str();
      SendData(winning_message, game_board);
      
      // Successful sending winning message and game board to Client.
      return true;
    } else if (status.status_code == "Error") {
      std::cerr << "Invalid move. Please try again." << std::endl;
      continue;
    }
    const char* update_message = "Player X move:";
    const char* game_board     = status.game_board.c_str();
    SendData(update_message, game_board);
    std::cout << "Your move was a success." << std::endl;
    std::cout << game_board;
    break;
  }               // End of Server move.
  
  return false;  // Winner was not declared.
}

/* ---------------------------------------------------------------------------------------
 * FUNCTION NAME: IsClientMove
 * ---------------------------------------------------------------------------------------
 * @brief Process a move received from the Client.
 *
 * This function receives an integer array representing a move from the client.
 * consisting of two integers representing the row and column. After receiving
 * and parsing the data, it validates whether the client's chosen location is
 * available and checks if the client is the winner.
 *
 * @details If the client's chosen location is available, the game board is updated, and
 *          a success message is sent to the client. The program continues, and the server
 *          makes a move.
 *
 *          If the chosen location is not available, a message is sent to the client
 *          notifying them of the unavailability, and the client is prompted to enter a
 *          new row and column integer.
 *
 *          If the client is the winner, a game-winning message is sent to the client,
 *          the program terminates.
 *
 * @param  move_counter The current move counter.
 *
 * @return True if the game is over (client won), false otherwise.
 * ---------------------------------------------------------------------------------------
 */
bool GameServer::IsClientMove(int move_counter) {
  while (1) {
    int client_move[2];
    ReceiveData(client_move);
    
    // Convert Network-Byte-Order integer back into Host-Byte-Order.
    int client_row    = ntohs(client_move[0]);
    int client_column = ntohs(client_move[1]);
    status            = game_manager.MakeMove(client_row, client_column, 'O', move_counter);
    if (status.status_code == "Gameover") {
      Dashes();
      std::cout << status.game_board;
      std::cout << "Client Won" << std::endl;
      Dashes();
      const char* winning_message    = "You win";
      const char* winning_game_board = status.game_board.c_str();
      SendData(winning_message, winning_game_board);
      
      // Successful sending winning message and game board to Client.
      return true;
    } else if (status.status_code == "Error") {
      const char* error_message = "Spot unavailable. Please try again.";
      const char* game_board    = status.game_board.c_str();
      SendData(error_message, game_board);
      
      // Successful sending error message to Client.
      continue;
    } else {
      std::cout << "Received player O move." << std::endl;
      const char* success_message = "Your move was a success.";
      const char* game_board      = status.game_board.c_str();
      SendData(success_message, game_board);
      // Successful sending success message to Client.
    }
    break;
  }               // End of Client Move.
  
  return false;  /* Winner was not declared. */
}

void GameServer::LaunchGame() {
  // Assign game_board to initial Game Board.
  status.game_board = game.DisplayGameBoard();
  int count_move = 1;
  while (1) {
    if (IsServerMove(count_move++)) {
      break;
    }
    if (IsClientMove(count_move++)) {
      break;
    }
  }
}
