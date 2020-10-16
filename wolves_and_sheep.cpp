#include "wolves_and_sheep.h"
#include <iostream>

WolvesAndSheep::WolvesAndSheep() {
  last_message = "START";
  wolves_player = new AIPlayer(this, true);
  sheep_player = new HumanPlayer(this, false);
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
      check_move(move);

      state.move(move);
    }
    catch (GameException & e) {
      std::cout << e.what() << std::endl;
      continue;
    }

    last_message = answer;
  }
}

bool WolvesAndSheep::check_move(const Move & move) const {
  if (!state.point_valid(move.from))
    throw GameException("No checker at the point");
  auto checker = state.get(move.from);
  if (checker == nullptr)
    throw GameException("No checker at the point");

  // If wrong player's checker
  if (checker->type == WOLF != state.is_wolves_turn())
    throw GameException("Wrong player's checker");
  if (abs(move.from.x - move.to.x) != 1 ||
      abs(move.from.y - move.to.y) != 1)
    throw GameException("Invalid move");
  if (!state.point_valid(move.to))
    throw GameException("Destination out of bounds");
  auto to = state.get(move.to);
  if (to != nullptr)
    throw GameException("Destination is not empty");
  return true;
}

GameState WolvesAndSheep::copy_state() {
  return GameState(state);
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
  std::cout << std::endl << ' ';
  for (int x = 0; x < BOARD_WIDTH; x++)
    std::cout << ' ' << x;
  std::cout << std::endl << last_message << std::endl;
  std::cout << (state.is_wolves_turn() ? "WOLVES TURN" : "SHEEP TURN") << std::endl;
}

bool WolvesAndSheep::decode(const std::string & message, Move & move) {
  try {
    auto delimeter_i = message.find(">");
    auto from = message.substr(0, delimeter_i);
    auto to = message.substr(delimeter_i + 1);

    move.from.x = from[0] - '0';
    move.from.y = from[1] - '0';

    move.to.x = to[0] - '0';
    move.to.y = to[1] - '0';
    return true;
  }
  catch (const std::exception& ex) {
    throw GameException("Cannot decode");
  }
}
