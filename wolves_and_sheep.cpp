#include "wolves_and_sheep.h"
#include <iostream>

WolvesAndSheep::WolvesAndSheep() {
  last_message = "START";
  sheep_player = new HumanPlayer(this);
  wolves_player = new HumanPlayer(this);
}

void WolvesAndSheep::start() {
  while(true){
    print_state();
    auto status = state.check_win();
    if (status == WOLVES_WON)
      std::cout << "WOLVES WON\n";
    if (status == SHEEP_WON)
      std::cout << "SHEEP WON\n";
    auto answer = state.is_wolves_turn() ? wolves_player->ask() : sheep_player->ask();
    if (answer == "EXIT")
      break;

    auto move = Move();
    try {
      decode(answer, move);
      state.move(move);
    }
    catch (GameException & e) {
      std::cout << e.what() << std::endl;
      continue;
    }

    last_message = answer;
  }
}

void WolvesAndSheep::print_state() {
  std::cout << ' ';
  for (int x = 0; x < BOARD_WIDTH; x++)
    std::cout << ' ' << x;
  for (int y = 0; y < BOARD_HEIGHT; y++) {
    std::cout << std::endl << y << "▕";
    for (int x = 0; x < BOARD_WIDTH; x++) {
      auto checker = state.get(x,y);
      if (checker == nullptr)
        if ((x + y) % 2 == 0)
          std::cout << "█▏";
        else
          std::cout << " ▕";
      else if (checker->type == WOLF)
        std::cout << "w▕";
      else
        std::cout << "s▕";
    }
  }
  std::cout << std::endl << last_message << std::endl;
  std::cout << std::endl;
}

bool WolvesAndSheep::decode(const std::string & message, Move & move) {
  try {
    auto delimeter_i = message.find("->");
    auto from = message.substr(0, delimeter_i);
    auto to = message.substr(delimeter_i + 3);

    auto del_f = from.find(' ');
    move.from.x = stoi(from.substr(0, del_f));
    move.from.y = stoi(from.substr(del_f + 1));

    auto del_t = to.find(' ');
    move.to.x = stoi(to.substr(0, del_t));
    move.to.y = stoi(to.substr(del_t + 1));
    return true;
  }
  catch (const std::exception& ex) {
    throw GameException("Cannot decode");
  }
}
