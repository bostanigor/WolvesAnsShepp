#ifndef WOLVESANDSHEEP_PLAYER_H
#define WOLVESANDSHEEP_PLAYER_H

#include "wolves_and_sheep.h"


class Player {
  WolvesAndSheep & game;

public:
  virtual std::string ask();
};

class HumanPlayer : Player {
};

class AIPlayer : Player {
};

#endif //WOLVESANDSHEEP_PLAYER_H
