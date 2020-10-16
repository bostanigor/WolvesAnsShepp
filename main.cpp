#include <iostream>
#include "wolves_and_sheep.h"

Player * init_player() {
  while (true) {
    int temp = 0;
    std::cin >> temp;
    if (temp == 0)
      return new HumanPlayer();
    else if (temp == 1) {
      std::cout << "Difficulty level: ";
      int level = 0;
      std::cin >> level;
      return new AIPlayer(level);
    }
    else
      std::cout << "Try again" << std::endl;
  }
}

int main() {
  std::cout << "Welcome to WolvesAndSheep!" << std::endl;
  
  std::cout << "Who will be playing as Sheep? (0 - human, 1 - AI)" << std::endl;
  Player * sheep_player = init_player();
  std::cout << "Who will be playing as Wolves? (0 - human, 1 - AI)" << std::endl;
  Player * wolves_player = init_player();

  auto game = WolvesAndSheep(sheep_player, wolves_player);

  game.start();

  return 0;
}
