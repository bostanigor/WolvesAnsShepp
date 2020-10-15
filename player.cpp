#include "player.h"

Player::Player(WolvesAndSheep * game, bool wolves_player) {
  this->game = game;
  this->wolves_player = wolves_player;
}

std::string HumanPlayer::ask() {
  std::string message;
  std::cout << "Write your move: ";
  std::getline(std::cin, message);
  return message;
}

std::string AIPlayer::ask() {
  auto move = best_move();
  return move_to_str(move);
}

Move AIPlayer::best_move() {
  auto state = game->copy_state();
  Move result = Move();
  min_max(&state, 10, result);
  return result;
}

int AIPlayer::min_max(GameState * state, int limit, Move & best_move) {
  if (limit == 0)
    return eval_heuristic(*state);

  int result = (state->is_wolves_turn() == wolves_player) ? INT_MIN : INT_MAX;

  auto possible_moves = get_possible_moves(*state);
  for (auto move : possible_moves) {
    try {
      // TODO: Remove validity check from move. Game must process it instead.
      state->move(move);

      auto f = min_max(state, limit - 1, best_move);
      if ((state->is_wolves_turn() != wolves_player && f > result) ||
          (state->is_wolves_turn() == wolves_player && f < result)) {
        result = f;
        best_move = move;
      }

      // Undo the move
      state->move(Move{move.to, move.from});
    }
    catch (GameException & e) {}
  }

  return result;
}

std::vector<Move> AIPlayer::get_possible_moves(const GameState &state) const {
  auto result = std::vector<Move>();
  result.reserve(8);
  if (state.is_wolves_turn()) {
    auto wolves = state.get_wolves();
    for (auto wolf : wolves) {
      auto from = wolf->pos;
      result.emplace_back(Move{from, from + Point {1, 1}});
      result.emplace_back(Move{from, from + Point {-1, 1}});
    }
  }
  else {
    auto sheep = state.get_sheep();
    auto from = sheep->pos;
    result.emplace_back(Move{from, from + Point {1, 1}});
    result.emplace_back(Move{from, from + Point {-1, 1}});
    result.emplace_back(Move{from, from + Point {1, -1}});
    result.emplace_back(Move{from, from + Point {-1, -1}});
  }
  return result;
}

int AIPlayer::eval_heuristic(const GameState & state) const {
  return 0;
}
