#include "player.h"

std::string HumanPlayer::ask() {
  std::string message;
  std::cout << "Write your move: ";
  std::getline(std::cin, message);
  return message;
}

HumanPlayer::HumanPlayer(WolvesAndSheep * game) {
  this->game = game;
}
