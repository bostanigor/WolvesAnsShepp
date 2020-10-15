#pragma once

#include <sstream>

const int BOARD_WIDTH = 8;
const int BOARD_HEIGHT = 8;

struct Point {
  int x, y;
};

static Point operator+(const Point & left, const Point & right) {
  return Point{left.x + right.x, left.y + right.y};
};

struct Move {
  Point from;
  Point to;
};

static std::string move_to_str(const Move & move) {
  std::stringstream ss;
  ss << move.from.x << " " << move.from.y << " -> " << move.to.x << " " << move.to.y;
  return ss.str();
};

enum CheckerType { WOLF, SHEEP };

struct Checker {
  Point pos;
  CheckerType type;
};

struct Board {
  std::array<std::array<Checker *, BOARD_HEIGHT>, BOARD_WIDTH> board;
};

enum GameStatus { SHEEP_WON, WOLVES_WON, GAME_CONTINUES };
