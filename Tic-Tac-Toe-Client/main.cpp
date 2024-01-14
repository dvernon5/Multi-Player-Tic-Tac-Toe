#include <iostream>
#include "GameClient.h"
int main(int argc, const char * argv[]) {
  GameClient game_client;
  game_client.StartConnection();
  game_client.LaunchGame();
  
  EXIT_SUCCESS;
}
