#pragma once

#include <array>
#include <iostream>
#include "helper_structs.h"

class GameState {
  std::array<Checker, 4> wolves;
  Checker sheep;
  Board board;
  bool wolves_turn; // True - it's wolves' turn, False - sheep's

public:
  GameState();
  GameState(const GameState &);

  bool move(Move);
  GameStatus check_win() const;

  Checker * get(int x, int y) const;
  Checker * get(Point point) const;

  bool is_wolves_turn() const { return wolves_turn; }

private:
  static bool point_valid(Point);
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
