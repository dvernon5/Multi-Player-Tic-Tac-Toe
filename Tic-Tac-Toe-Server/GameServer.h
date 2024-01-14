/* -------------------------------------------------------------------------------------
 * CLASS NAME: GameServer
 * -------------------------------------------------------------------------------------
 * @brief Set up a Server to accept a client connection and launches a Tic-Tac-Toe game.
 *
 * The GameServer class connects a server socket to the network, allowing
 * server-client communication. After a client connects to server, both
 * server and client send-receive data over the network to determine the winner
 * of the Tic-Tac-Toe game.
 *
 * @note Close server and client socket when Tic-Tac-Toe game terminates.
 * -------------------------------------------------------------------------------------
 */
class GameServer {
  public:
    GameServer();
    int StartServer();
    int StartListen();
    void LaunchGame();
    ~GameServer();
  
  private:
    int server_socket;
    int client_socket;
    struct sockaddr_in client_address;
    socklen_t client_address_size;
    struct sockaddr_in server_address;
    bool IsServerMove(int counter);
    bool IsClientMove(int counter);
    void SendData(const char* status_message, const char* game_board);
    void ReceiveData(int* client_move);
    void ParseReceivedRowAndColumnNumber(const char* received_data, int* client_move, size_t size);
    void CloseServer();
};
#endif /* GameServer_h */
