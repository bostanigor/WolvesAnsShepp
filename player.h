#pragma once

#include "wolves_and_sheep.h"

class WolvesAndSheep;

class Player {
protected:
  WolvesAndSheep * game = nullptr;

public:
  virtual std::string ask() = 0;
};

class HumanPlayer : public Player {
public:
  explicit HumanPlayer(WolvesAndSheep * game);

  std::string ask() override;
};

class AIPlayer : public Player {
};
