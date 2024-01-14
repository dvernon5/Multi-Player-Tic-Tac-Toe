#ifndef GameClient_h
#define GameClient_h
#include "ResponseManager.h"
#include "PromptingUser.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

/* -------------------------------------------------------------------------------------
 * CLASS NAME: GameClient
 * -------------------------------------------------------------------------------------
 * @brief Set up a Client to connect a server connection and create the logic to launch a Tic-Tac-Toe game.
 *
 * The GameClient class connects a client socket to the network, allowing
 * server-client communication. After a server accepts client request, both
 * server and client send-receive data over the network to determine the winner
 * of the Tic-Tac-Toe game.
 *
 * @note Close server and client socket when Tic-Tac-Toe game terminates.
 * -------------------------------------------------------------------------------------
 */
class GameClient {
  public:
    GameClient();
    int StartClient();
    int StartConnection();
    void LaunchGame();
    ~GameClient();
  
  private:
    int client_socket;
    struct sockaddr_in server_address;
    ResponseManager response_manager;
    PromptingUser prompting;
    bool IsServerMove();
    bool IsClientMove();
    void SendData(int* client_move);
    void ReceiveData(char* status_messages, size_t status_messages_size,
                     char* game_board_buffer, size_t game_board_size);
    void ParseWinningInformation(char* combined_data, char* status_messages, size_t status_messages_size,
                                 char* game_board_buffer, size_t game_board_size);
};
#endif /* GameClient_h */
