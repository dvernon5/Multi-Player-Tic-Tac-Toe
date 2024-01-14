#include "GameServer.h"
#include <iostream>

int main(int argc, const char * argv[]) {
  GameServer game_server;
  game_server.StartListen();
  game_server.LaunchGame();

  return EXIT_SUCCESS;
}
