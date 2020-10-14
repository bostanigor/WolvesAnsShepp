#pragma once

#include <string>
#include "game_state.h"
#include "player.h"

class Player;

class WolvesAndSheep {
  GameState state;
  std::string last_message;

  Player * sheep_player;
  Player * wolves_player;

public:
  WolvesAndSheep();

  void print_state();
  void start();

private:
  bool decode(std::string);
};
