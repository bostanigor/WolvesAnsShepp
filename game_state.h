#ifndef WOLVESANDSHEEP_GAME_STATE_H
#define WOLVESANDSHEEP_GAME_STATE_H

#include <array>
#include <iostream>

const int BOARD_WIDTH = 8;
const int BOARD_HEIGHT = 8;

enum CheckerType { WOLF, SHEEP };

struct Checker {
  int x, y;
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

  bool move(int sx, int sy, int dx, int dy);

  Checker * get(int x, int y);

  void print_debug_info() {
    for (auto wolf : wolves)
      std::cout << "WOLF: " << wolf.x << ' ' << wolf.y << ' ' << wolf.type << std::endl;
    std::cout << "SHEEP: " << sheep.x << ' ' << sheep.y << ' ' << sheep.type << std::endl;
    std::cout << "BOARD:" << std::endl;
    for (int y = 0; y < BOARD_HEIGHT; y++)
      for (int x = 0; x < BOARD_WIDTH; x++) {
        auto temp = get(x, y);
        if (temp == nullptr)
          continue;
        auto t = *temp;
        std::cout << t.x << ' ' << t.y << ' ' << t.type << std::endl;
      }
  }
};

#endif //WOLVESANDSHEEP_GAME_STATE_H
