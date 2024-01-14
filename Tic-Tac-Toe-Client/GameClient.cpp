#include "GameClient.h"
#include <nlohmann/json.hpp>
#include <iostream>

namespace DashLine {
  void DashLines() {
    std::cout << "----------\n";
  }
}
using namespace DashLine;

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


/* ---------------------------------------------------------------------------------
 * CONSTRUCTOR: GameClient
 * ---------------------------------------------------------------------------------
 * @brief Constructs a GameClient object and creates a client socket.
 *
 * The constructor calls the StartClient() function to initialize the client socket.
 * If the socket creation fails, a std::runtime_error is thrown.
 *
 * @throws std:runtime_error if there is an errorf creating the client socket.
 * ---------------------------------------------------------------------------------
 */
GameClient::GameClient() {
  if (StartClient() != 0) {
    throw std::runtime_error("Error! Creating a client socket");
  }
}

GameClient::~GameClient() {
  close(client_socket);
}

/* ------------------------------------------------------------------------
 * FUNCTION NAME: StartClient
 * ------------------------------------------------------------------------
 * @brief Create a socket for the client to establish a connection.
 *
 * This function initialize a socket for the client using the TCP Protocol.
 *
 * @throws std::runtime_error if there is an error during socket creation.
 *
 * @return EXIT_SUCCESS if the client socket is successfully created.
 * ------------------------------------------------------------------------
 */
int GameClient::StartClient() {
  // Create a scoket.
  client_socket = socket(PF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    throw std::runtime_error("Error! Creating a socket");
  }
  
  return EXIT_SUCCESS;  // return 0
}

/* -------------------------------------------------------------------------------------
 * FUNCTION NAME: StartConnection
 * -------------------------------------------------------------------------------------
 * @brief Set up a connection to the game server.
 *
 * This function configures and establishes a connection to the specified game server.
 * It sets up the server address and port, converts the IP address string to a struct,
 * and then initiates a connection using the created client socket.
 *
 * @throws std::runtime_error if there is an error converting the IP address string
 *                            into the struct in_addr or if there is an error connecting
 *                            to the server.
 *
 * @return EXIT_SUCCESS if the connection is successfully established.
 * -------------------------------------------------------------------------------------
 */
int GameClient::StartConnection() {
  // Connect to the server.
  server_address.sin_family = AF_INET;
  server_address.sin_port   = htons(8080);
  if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) == -1) {
    throw std::runtime_error("Error! Converting IP Address string into struct in_addr");
  }
  if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
    throw std::runtime_error("Error! Connecting to server");
  }
  std::cout << "Connected to the server." << std::endl;
  
  return EXIT_SUCCESS;
}

/* -----------------------------------------------------------------------------------------------------------
 * FUNCTION NAME: SendData
 * -----------------------------------------------------------------------------------------------------------
 * @brief Send an serialized JSON-formatted string to the connected server through the specified socket.
 *
 * This function is responsible for sending data to the server, which is expected to be a
 * serialized JSON-formatted string containing information such as row and column numbers.
 *
 * @details The function uses the provided socket to send a serialized JSON-formatted string
 *          to the server. If an error occurs during the sending process, a
 *          std::runtime error is thrown.
 *
 * @param client_move Pointer to an integer array that will be included in the JSON string.
 *
 * @throws std::runtime_error if an error occurs during data reception.
 *
 * @return No explicit return value.
 * -----------------------------------------------------------------------------------------------------------
 */
void GameClient::SendData(int *client_move) {
  Json::json_data["row"]      = client_move[0];
  Json::json_data["column"]   = client_move[1];
  std::string serialized_data = Json::json_data.dump();
  size_t serialized_data_size = serialized_data.size();
  ssize_t data_bytes_sent     = send(client_socket, serialized_data.c_str(), serialized_data_size ,0);
  if (data_bytes_sent == -1) {
    throw std::runtime_error("Error! Sending row and column number of bytes.");
  }
}

/* ------------------------------------------------------------------------------------
 * FUNCTION NAME: ParseWinningInformation
 * ------------------------------------------------------------------------------------
 * @brief Parses combined data into winning information.
 *
 * The ParseWinningInformaion function extracts winning information
 * from combined data. The combined data is expected to have a format
 * where the winning message and game board are stored in a JSON oject.
 *
 * @details The function uses the nlohmann json library to parse the combined
 *          data, which is assumed to be a JSON-formatted string. The JSON object
 *          is expected to have "status_message" and "game_board" fields. The
 *          winning message and game board are then extracted from the JSON object and
 *          copied to the provided buffers.
 *
 * @param received_data The combined data containing winning informaion in JSON format.
 * @param status_messages Buffer to store the winning message.
 * @param status_messages_size Size of the status_message buffer.
 * @param game_board_buffer Buffer to store the game board informaion.
 * @parma game_board_size Size of the game_board_buffer.
 *
 * @note The winning message and game board are expected to be stored in a JSON object.
 *       The function uses the nlohmann json library to parse the JSON-formatted string
 *       and extracts the neccessary informaion.
 * ------------------------------------------------------------------------------------
 */
void GameClient::ParseWinningInformation(char* received_data, char* status_messages,
                                         size_t status_messages_size, char* game_board_buffer,
                                         size_t game_board_size) {
  try {
    Json::json_data = nlohmann::json::parse(received_data);
    std::string status_message  = Json::json_data["status_message"];
    std::string game_board      = Json::json_data["game_board"];
    strncpy(status_messages, status_message.c_str(), status_messages_size);
    strncpy(game_board_buffer, game_board.c_str(), game_board_size);
  } catch (const std::exception &e) {
    std::cerr << "Error parsing JSON: " << e.what() << std::endl;
  }
}

/* ------------------------------------------------------------------------------------------------
 * FUNCTION NAME: ReceiveData
 * ------------------------------------------------------------------------------------------------
 * @brief Receive a JSON-formatted message from the connected server through the specified socket.
 *
 * This function is responsible for receiving a JSON-formatted message from the server, which can include
 * game board updates and various status messages.
 *
 * @details The function uses the provided socket to receive the specified message from the server.
 *          The receive data is expected to be in a JSON format, combining both status messages and
 *          game board updates. The function then utilizes the ParseWinningInformation function to
 *          extract the winning information from the received JSON-formatted string. If an error occurs
 *          during the reception process or parsing process, a std::runtime error is thrown.
 *
 * @param status_messages Buffer to store the received status message.
 * @param status_messages_size Size of the status_messages buffer.
 * @param game_board_buffer Buffer to store the received game board information.
 * @param game_board_size Size of the game_board_buffer.
 *
 * @throws std::runtime_error if an error occurs during the reception process.
 *
 * @return No explicit return value.
 *
 * @note This function complements the ParseWinningInformation function document above.
 * ------------------------------------------------------------------------------------------------
 */
void GameClient::ReceiveData(char* status_messages, size_t status_messages_size,
                             char* game_board_buffer, size_t game_board_size) {
  // Receive the combined data
  char received_data[512];
  ssize_t data_bytes_read = recv(client_socket, received_data, sizeof(received_data), 0);
  if (data_bytes_read == -1) {
    throw std::runtime_error("Error! Receiving data from Server");
  }
  received_data[data_bytes_read] = '\0';
  ParseWinningInformation(received_data, status_messages, status_messages_size,
                          game_board_buffer, game_board_size);
}

/* ---------------------------------------------------------------------------------------
 * FUNCTION NAME: IsServerMove
 * ---------------------------------------------------------------------------------------
 * @brief Receive server data.
 *
 * This function receives game-related data from the server, including the game board
 * and a status message. The status messages can be a server winning message,
 * a tie game message, or an error message in case of an invalid move.
 *
 * @details If the server wins, a winning message and the serialized winning game board
 *          are receive from the server, and the program terminates.
 *
 *          If the game is tied, a tie game message and the serialized game board are receive
 *          from the server, and the program terminates.
 *
 *          If none of the above conditions are met, the serialized updated game board
 *          is receive from the server, and control is given to the client to make a move.
 *
 * @return True if the game is over (either server won or tied), false otherwise.
 * ---------------------------------------------------------------------------------------
*/
bool GameClient::IsServerMove() {
  while (1) {
    char server_data[256];
    char game_board[256];
    ReceiveData(server_data, sizeof(server_data), game_board, sizeof(game_board));
    if (strcmp(server_data, "Server won") == 0 ||
        strcmp(server_data, "TIE GAME")   == 0)
    {
      DashLines();
      std::cout << game_board;
      std::cout << server_data << std::endl;
      DashLines();
      return true;
    }
    std::cout << server_data << std::endl;
    std::cout << game_board;
    break;
  }              // End of Server Move.
  
  return false; // Winner was not declared.
}

/* -----------------------------------------------------------------------------------------
 * FUNCTION NAME: IsClientMove
 * -----------------------------------------------------------------------------------------
 * @brief Process a move, and send to Server.
 *
 * This function send an integer array representing a move from the client.
 * consisting of two integers representing the row and column. After sending data
 * server will validates whether the client's chosen location is available and checks
 * if the client is the winner.
 *
 * @details If the client's chosen location is available, the game board is updated, and
 *          a success message is received from the server. The program continues, and the
 *          control is given to the server to make a move.
 *
 *          If the chosen location is not available, a message is received from the server
 *          notifying client of the unavailability, and the client is prompted to enter a
 *          new row and column integer.
 *
 *          If the client is the winner, a game-winning message is received from the server,
 *          the program terminates.
 *
 * @return True if the game is over (client won), false otherwise.
 * -----------------------------------------------------------------------------------------
 */
bool GameClient::IsClientMove() {
  while (1) {
    prompting.PlayerTurn('O');
    prompting.UserForRowNumber();
    int row_number_to_send      = 0;
    row_number_to_send          = response_manager.GetValidatedUserInput(row_number_to_send, 1, 3, 'R');
    int converted_row_number    = htons(row_number_to_send);      // Convert Host-Byte-Order to Network-Byte-Order
    prompting.UserForColumnNumber();
    int column_number_to_send   = 0;
    column_number_to_send       = response_manager.GetValidatedUserInput(column_number_to_send, 1, 3, 'C');
    int converted_column_number = htons(column_number_to_send);  // Convert Host-Byte-Order to Network-Byte-Order
    int client_move[2]          = { converted_row_number, converted_column_number };
    SendData(client_move);
    // Successfully send row and column intergers to server.
    
    // Receive a status message from Server:
    char status_message[256];
    char game_board[256];
    ReceiveData(status_message, sizeof(status_message), game_board, sizeof(game_board));
    if (strcmp(status_message,"Spot unavailable. Please try again.") == 0) {
      std::cerr << status_message << std::endl;
      std::cout << game_board;
      continue;                                       // Go back to the user input process.
    } else if (strcmp(status_message, "You win") == 0) {
      // Receive The winning game board.
      DashLines();
      std::cout << game_board;
      std::cout << status_message << std::endl;
      DashLines();
      return true;
    }
    // Receive Successful Move Message
    std::cout << status_message << std::endl;
    std::cout << game_board;
    break;
  }               // End of Client Move.
  
  return false;  // Winner was not declared.
}

void GameClient::LaunchGame() {
  while (1) {
    if (IsServerMove()) {
      break;
    }
    if (IsClientMove()) {
      break;
    }
  }
}
