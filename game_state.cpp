#include "game_state.h"

GameState::GameState() {
  wolves = {
    Checker{1, 0, WOLF}, Checker{3, 0, WOLF},
    Checker{5, 0, WOLF}, Checker{7, 0, WOLF}
  };
  sheep = Checker{0, 7, SHEEP};
  board = Board();
  for (int i = 0; i < 4; i++) {
    Checker * wolf = &wolves[i];
    board.board[wolf->x][wolf->y] = wolf;
  }
  board.board[sheep.x][sheep.y] = &sheep;
  wolves_turn = true;
}

GameState::GameState(const GameState & other) {
  wolves = other.wolves;
  sheep = other.sheep;
  board = other.board; // TODO: Check if this copies
  wolves_turn = other.wolves_turn;
}

Checker * GameState::get(int x, int y) {
  return board.board[x][y];
}
