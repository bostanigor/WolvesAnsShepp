#pragma once

#include <string>
#include "game_state.h"
#include "player.h"
#include "helper_structs.h"

class Player;

class WolvesAndSheep {
  GameState state;
  std::string last_message;

  Player * sheep_player;
  Player * wolves_player;

public:
  WolvesAndSheep();

  GameState copy_state();

  void print_state();
  void start();

private:
  static bool decode(const std::string &, Move &);
};
