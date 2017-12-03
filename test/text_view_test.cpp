#include <iostream>
#include <cassert>

#include "utils.hpp"
#include "othello_game.hpp"
#include "othello_controller.hpp"
#include "othello_player.hpp"

using namespace Othello;

#ifdef NDEBUG
#undef NDEBUG
#endif

#ifndef DEBUG
#define DEBUG
#endif

int main() {
  OthelloGame othelloGame;
  OthelloTextController othelloTextController(
    othelloGame,
    std::make_shared<OthelloQueryPlayer>(OthelloQueryPlayer("Black")),
    std::make_shared<OthelloQueryPlayer>(OthelloQueryPlayer("White"))
  );

  std::cout << othelloTextController.getView() << std::endl;
  assert(
    othelloTextController.getView() ==
    "     A   B   C   D   E   F   G   H  \n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 1 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 2 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 3 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 4 |   |   |   | w | b |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 5 |   |   |   | b | w |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 6 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 7 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 8 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
  );

  othelloTextController.applyMove(positionToBoard<OthelloMoves>(3, 2));
  std::cout << othelloTextController.getView() << std::endl;
  assert(
    othelloTextController.getView() ==
    "     A   B   C   D   E   F   G   H  \n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 1 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 2 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 3 |   |   |   | b |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 4 |   |   |   | b | b |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 5 |   |   |   | b | w |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 6 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 7 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 8 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
  );

  othelloTextController.applyMove(positionToBoard<OthelloMoves>(2, 2));
  std::cout << othelloTextController.getView() << std::endl;
  assert(
    othelloTextController.getView() ==
    "     A   B   C   D   E   F   G   H  \n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 1 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 2 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 3 |   |   | w | b |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 4 |   |   |   | w | b |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 5 |   |   |   | b | w |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 6 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 7 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 8 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
  );

  othelloTextController.applyMove(positionToBoard<OthelloMoves>(2, 3));
  std::cout << othelloTextController.getView() << std::endl;
  assert(
    othelloTextController.getView() ==
    "     A   B   C   D   E   F   G   H  \n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 1 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 2 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 3 |   |   | w | b |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 4 |   |   | b | b | b |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 5 |   |   |   | b | w |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 6 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 7 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 8 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
  );

  othelloTextController.applyMove(positionToBoard<OthelloMoves>(2, 4));
  std::cout << othelloTextController.getView() << std::endl;
  assert(
    othelloTextController.getView() ==
    "     A   B   C   D   E   F   G   H  \n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 1 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 2 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 3 |   |   | w | b |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 4 |   |   | w | b | b |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 5 |   |   | w | w | w |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 6 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 7 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
    " 8 |   |   |   |   |   |   |   |   |\n"
    "   +---+---+---+---+---+---+---+---+\n"
  );

  std::cout << "All tests passed for Text View!" << std::endl;
  return 0;
}
