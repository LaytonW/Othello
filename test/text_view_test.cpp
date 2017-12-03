#include <iostream>
#include <cassert>

#include "utils.hpp"
#include "othello.hpp"

using namespace Othello;

#ifdef NDEBUG
#undef NDEBUG
#endif

#ifndef DEBUG
#define DEBUG
#endif

int main() {
  OthelloGame othelloGame;
  OthelloTextController othelloTextController(othelloGame);

  std::cout << othelloTextController.getView() << std::endl;
  assert(
    othelloTextController.getView() ==
    "  A B C D E F G H\n"
    "1 o o o o o o o o\n"
    "2 o o o o o o o o\n"
    "3 o o o o o o o o\n"
    "4 o o o w b o o o\n"
    "5 o o o b w o o o\n"
    "6 o o o o o o o o\n"
    "7 o o o o o o o o\n"
    "8 o o o o o o o o\n"
  );

  othelloTextController.applyControl(positionToBoard<OthelloMoves>(3, 2));
  std::cout << othelloTextController.getView() << std::endl;
  assert(
    othelloTextController.getView() ==
    "  A B C D E F G H\n"
    "1 o o o o o o o o\n"
    "2 o o o o o o o o\n"
    "3 o o o b o o o o\n"
    "4 o o o b b o o o\n"
    "5 o o o b w o o o\n"
    "6 o o o o o o o o\n"
    "7 o o o o o o o o\n"
    "8 o o o o o o o o\n"
  );

  othelloTextController.applyControl(positionToBoard<OthelloMoves>(2, 2));
  std::cout << othelloTextController.getView() << std::endl;
  assert(
    othelloTextController.getView() ==
    "  A B C D E F G H\n"
    "1 o o o o o o o o\n"
    "2 o o o o o o o o\n"
    "3 o o w b o o o o\n"
    "4 o o o w b o o o\n"
    "5 o o o b w o o o\n"
    "6 o o o o o o o o\n"
    "7 o o o o o o o o\n"
    "8 o o o o o o o o\n"
  );

  othelloTextController.applyControl(positionToBoard<OthelloMoves>(2, 3));
  std::cout << othelloTextController.getView() << std::endl;
  assert(
    othelloTextController.getView() ==
    "  A B C D E F G H\n"
    "1 o o o o o o o o\n"
    "2 o o o o o o o o\n"
    "3 o o w b o o o o\n"
    "4 o o b b b o o o\n"
    "5 o o o b w o o o\n"
    "6 o o o o o o o o\n"
    "7 o o o o o o o o\n"
    "8 o o o o o o o o\n"
  );

  othelloTextController.applyControl(positionToBoard<OthelloMoves>(2, 4));
  std::cout << othelloTextController.getView() << std::endl;
  assert(
    othelloTextController.getView() ==
    "  A B C D E F G H\n"
    "1 o o o o o o o o\n"
    "2 o o o o o o o o\n"
    "3 o o w b o o o o\n"
    "4 o o w b b o o o\n"
    "5 o o w w w o o o\n"
    "6 o o o o o o o o\n"
    "7 o o o o o o o o\n"
    "8 o o o o o o o o\n"
  );

  std::cout << "All tests passed for Text View!" << std::endl;
  return 0;
}
