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

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    std::cout << "Welcome to WolvesAndSheep!" << std::endl;

    std::cout << "Who will be playing as Sheep? (0 - human, 1 - AI)" << std::endl;
    Player * sheep_player = init_player();
    std::cout << "Who will be playing as Wolves? (0 - human, 1 - AI)" << std::endl;
    Player * wolves_player = init_player();

    auto game = WolvesAndSheep(sheep_player, wolves_player);

    game.start();
  }
  else {
    auto ai_level = std::stoi(argv[1]);
    auto is_sheep = argv[2] == "0"; // if 0 - bot is sheep, 1 - wolves
    Player * sheep_player;
    Player * wolves_player;
    if (is_sheep) {
      sheep_player = new AIPlayer(ai_level);
      wolves_player = new HumanPlayer();
    }
    else {
      sheep_player = new HumanPlayer();
      wolves_player = new AIPlayer(ai_level);
    }

    auto game = WolvesAndSheep(sheep_player, wolves_player);

    game.start();
    if (is_sheep && game.get_status() == SHEEP_WON)
      return 0;
    else
      return 3;
  }

  return 0;
}
