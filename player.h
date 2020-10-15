#pragma once

#include "wolves_and_sheep.h"
#include <vector>

class WolvesAndSheep;

class Player {
protected:
  bool wolves_player;
  WolvesAndSheep * game = nullptr;

public:
  Player(WolvesAndSheep * game, bool wolves_player);
  virtual std::string ask() = 0;
};

class HumanPlayer : public Player {
public:
  explicit HumanPlayer(WolvesAndSheep * game, bool wolves_player) :
    Player(game, wolves_player) {};

  std::string ask() override;
};

class AIPlayer : public Player {
public:
  explicit AIPlayer(WolvesAndSheep * game, bool wolves_player) :
    Player(game, wolves_player) {};

  std::string ask() override;

private:
  Move best_move();
  int eval_heuristic(const GameState & state) const;
  int min_max(GameState * state, int limit, Move & best_move);

  std::vector<Move> get_possible_moves(const GameState & state) const;
};
