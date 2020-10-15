#pragma once

const int BOARD_WIDTH = 8;
const int BOARD_HEIGHT = 8;

struct Point {
  int x, y;
};

struct Move {
  Point from;
  Point to;
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
