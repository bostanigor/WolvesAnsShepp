#pragma once

#include <array>
#include <iostream>
#include "helper_structs.h"

class GameState {
  std::array<Checker *, 4> wolves;
  Checker * sheep;
  Board board;
  bool wolves_turn; // True - it's wolves' turn, False - sheep's

public:
  GameState();
  GameState(const GameState &);

  bool move(const Move &);
  GameStatus check_win() const;

  Checker * get(int x, int y) const;
  Checker * get(const Point &) const;

  std::array<Checker *, 4> get_wolves() const;
  Checker * get_sheep() const;

  bool is_wolves_turn() const { return wolves_turn; }

  bool point_empty(const Point &) const;
  static bool point_valid(const Point &);
};
