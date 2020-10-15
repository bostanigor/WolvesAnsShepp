#include "game_state.h"

GameState::GameState() {
  wolves = {
    new Checker{1, 0, WOLF}, new Checker{3, 0, WOLF},
    new Checker{5, 0, WOLF}, new Checker{7, 0, WOLF}
  };
  sheep = new Checker{0, 7, SHEEP};
  board = Board();
  for (int i = 0; i < 4; i++) {
    Checker * wolf = wolves[i];
    board.board[wolf->pos.x][wolf->pos.y] = wolf;
  }
  board.board[sheep->pos.x][sheep->pos.y] = sheep;
  wolves_turn = false;
}

GameState::GameState(const GameState & other) {
  wolves = other.wolves;
  sheep = other.sheep;
  board = other.board; // TODO: Check if this copies
  wolves_turn = other.wolves_turn;
}

bool GameState::move(const Move & move) {
  if (!point_valid(move.from))
    throw GameException("No checker at the point");
  auto checker = get(move.from);
  if (checker == nullptr)
    throw GameException("No checker at the point");
  if (checker->type == WOLF != wolves_turn) // If wrong player's checker
    throw GameException("Wrong player's checker");
  if (abs(move.from.x - move.to.x) != 1 ||
      abs(move.from.y - move.to.y) != 1)
    throw GameException("Invalid move");
  if (!point_valid(move.to))
    throw GameException("Destination out of bounds");
  auto to = get(move.to);
  if (to != nullptr)
    throw GameException("Destination is not empty");

  checker->pos.x = move.to.x;
  checker->pos.y = move.to.y;
  std::swap(board.board[move.from.x][move.from.y],
            board.board[move.to.x][move.to.y]);

  wolves_turn =! wolves_turn;
  return true;
}

GameStatus GameState::check_win() const {
  if (sheep->pos.y == 0)
    return SHEEP_WON;
  Point points[4] = {
    Point{sheep->pos.x + 1, sheep->pos.y + 1},
    Point{sheep->pos.x + 1, sheep->pos.y - 1},
    Point{sheep->pos.x - 1, sheep->pos.y + 1},
    Point{sheep->pos.x - 1, sheep->pos.y - 1}
  };
  for (auto point : points)
    if (point_valid(point) && get(point) == nullptr)
      return GAME_CONTINUES;
  return WOLVES_WON;
}

Checker * GameState::get(int x, int y) const {
  return board.board[x][y];
}

Checker * GameState::get(Point point) const {
  return board.board[point.x][point.y];
}

bool GameState::point_valid(Point point) {
  return point.x >= 0 && point.x < BOARD_WIDTH &&
         point.y >= 0 && point.y < BOARD_HEIGHT;
}

std::array<Checker *, 4> GameState::get_wolves() const {
  return wolves;
}

Checker * GameState::get_sheep() const {
  return sheep;
}
