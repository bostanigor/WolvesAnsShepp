#ifndef WOLVESANDSHEEP_WOLVES_AND_SHEEP_H
#define WOLVESANDSHEEP_WOLVES_AND_SHEEP_H

#include <string>
#include "game_state.h"
#include "player.h"

class WolvesAndSheep {
  GameState state;
  std::string last_move;

  Player sheep_player;
  Player wolves_player;

public:
  WolvesAndSheep();

  void print_state();
  void start();

private:
  void decode(std::string);
};

#endif //WOLVESANDSHEEP_WOLVES_AND_SHEEP_H
