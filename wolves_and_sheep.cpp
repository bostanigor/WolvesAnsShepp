#include "wolves_and_sheep.h"
#include <iostream>

WolvesAndSheep::WolvesAndSheep() {
  last_move = "START";
  sheep_player = HumanPlayer();
  wolves_player = HumanPlayer();
}

void WolvesAndSheep::start() {
  bool wolves_turn = false;
  while(true){
    auto answer = wolves_turn ? wolves_player.ask() : sheep_player.ask();
    if (answer == "EXIT")
      break;
    wolves_turn = !wolves_turn;
  }
}

void WolvesAndSheep::print_state() {
  std::cout << ' ';
  for (int x = 0; x < BOARD_WIDTH; x++)
    std::cout << ' ' << x;
  for (int y = 0; y < BOARD_HEIGHT; y++) {
    std::cout << std::endl << y << '|';
    for (int x = 0; x < BOARD_WIDTH; x++) {
      auto checker = state.get(x,y);
      if (checker == nullptr)
        std::cout << " |";
      else if (checker->type == WOLF)
        std::cout << "w|";
      else
        std::cout << "s|";
    }
  }
}

void WolvesAndSheep::decode(std::string message) {
  auto message
}
