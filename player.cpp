#include "player.h"
#include <queue>

Player::Player(WolvesAndSheep * game) {
  this->game = game;
}

std::string HumanPlayer::ask() {
  std::string message;
  std::cout << "Write your move: ";
  std::getline(std::cin, message);
  return message;
}

std::string AIPlayer::ask() {
  auto move = best_move();
  std::cout << "I called evaluation function "
    << heuristic_call_count << " times" << std::endl;
  auto str = move_to_str(move);
  std::cerr << str << std::endl;
  std::cout << str << std::endl;
  return str;
}

Move AIPlayer::best_move() {
  auto state = game->copy_state();
  heuristic_call_count = 0;
  return min_max(&state, difficulty_level, INT_MIN, INT_MAX).move;
}

MoveWithF AIPlayer::min_max(GameState * state, int limit, int alpha, int beta) {
  auto best_move = Move();
  if (limit == 0)
    return MoveWithF{best_move, eval_heuristic(*state)};

  bool wolves_turn = state->is_wolves_turn();
  int result = (wolves_turn) ? INT_MAX : INT_MIN;
  auto status = state->check_win();
  if (status != GAME_CONTINUES)
    return MoveWithF{best_move, status == SHEEP_WON ? 100 : -100};

  auto possible_moves = get_possible_moves(*state);
  for (auto move : possible_moves) {
    if (!(state->point_valid(move.to)) ||
        !(state->point_empty(move.to)))
        continue;
    state->move(move);

    auto temp = min_max(state, limit - 1, alpha, beta);
    auto f = temp.f;
    // Undo the move
    state->move(Move{move.to, move.from});

    if ((wolves_turn && f < result) ||
        (!wolves_turn && f > result)) {
      result = f;
      best_move = move;
    }
    if (wolves_turn) {
      if (f < beta)
        beta = f;
    }
    else if (f > alpha)
      alpha = f;
    if (alpha > beta)
      break;
  }

  return {best_move, result};
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
    result.emplace_back(Move{from, from + Point {1, -1}});
    result.emplace_back(Move{from, from + Point {-1,-1}});
    result.emplace_back(Move{from, from + Point {1,  1}});
    result.emplace_back(Move{from, from + Point {-1, 1}});
  }
  return result;
}

int AIPlayer::eval_heuristic(const GameState & state) {
  heuristic_call_count++;
  std::queue<Point> point_queue;
  std::array<std::array<int, BOARD_WIDTH>, BOARD_HEIGHT> map {};
  Point next_points[4] = { Point{1, 1}, Point{-1, 1}, Point{1, -1}, Point{-1, -1} };
  auto start_point = state.get_sheep()->pos;
  point_queue.push(start_point);

  while (!point_queue.empty())
  {
    auto from = point_queue.front();
    point_queue.pop();

    for (int i = 0; i < 4; i++) {
      auto to = from + next_points[i];
      if (state.point_valid(to) && state.point_empty(to)) {
        if (map[to.x][to.y] > 0)
          continue;
        map[to.x][to.y] = map[from.x][from.y] + 1;
        if (to.y == 0)
          return map[to.x][to.y];
        point_queue.push(to);
      }
    }
  }
  // If no turns lead to victory
  return -100;
}
