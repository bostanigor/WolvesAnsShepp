#pragma once

#include "wolves_and_sheep.h"
#include <vector>

class WolvesAndSheep;

class Player {
public:
  WolvesAndSheep * game = nullptr;

  Player() {}
  Player(WolvesAndSheep * game);
  virtual std::string ask() = 0;
};

class HumanPlayer : public Player {
public:
  HumanPlayer() : Player() {};
  explicit HumanPlayer(WolvesAndSheep * game) : Player(game) {};

  std::string ask() override;
};

struct MoveWithF {
  Move move;
  int f;
};

class AIPlayer : public Player {
public:
  AIPlayer(int difficulty_level) : Player() {
    this->difficulty_level = difficulty_level;
  };
  explicit AIPlayer(WolvesAndSheep * game, int difficulty_level) : Player(game) {
    this->difficulty_level = difficulty_level;
  };

  std::string ask() override;

private:
  int heuristic_call_count = 0;
  int difficulty_level = 0;

  Move best_move();
  int eval_heuristic(const GameState & state);
  MoveWithF min_max(GameState * state, int limit, int alpha, int beta);

  std::vector<Move> get_possible_moves(const GameState & state) const;
};
