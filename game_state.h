#pragma once

#include <array>
#include <iostream>
#include "helper_structs.h"

const int BOARD_WIDTH = 8;
const int BOARD_HEIGHT = 8;

enum CheckerType { WOLF, SHEEP };

struct Checker {
  Point pos;
  CheckerType type;
};

struct Board {
  std::array<std::array<Checker *, BOARD_HEIGHT>, BOARD_WIDTH> board;
};

class GameState {
  std::array<Checker, 4> wolves;
  Checker sheep;
  Board board;
  bool wolves_turn; // True - it's wolves' turn, False - sheep's

public:
  GameState();
  GameState(const GameState &);

  bool move(Move);

  Checker * get(int x, int y);
  Checker * get(Point point);

private:
  static bool point_valid(Point);
};
