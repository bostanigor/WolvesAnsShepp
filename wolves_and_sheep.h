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

  GameStatus status;

public:
  WolvesAndSheep();
  WolvesAndSheep(Player * sheep_player, Player * wolves_player);

  GameState copy_state();

  void print_state();
  void start();

  GameStatus get_status() { return status; }

private:
  static bool decode(const std::string &, Move &);
  bool check_move(const Move &) const;
};

class GameException {
  std::string message;

public:
  GameException(const std::string & message) {
    this->message = message;
  }

  std::string what() const{
    return message;
  }
};
