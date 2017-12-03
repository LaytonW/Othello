#include <iostream>

#include "othello_controller.hpp"

using namespace Othello;

OthelloTextController::OthelloTextController(const OthelloGame& othelloGame)
  :othelloGame(othelloGame) {}

const std::string OthelloTextController::getView(void) const {
  const auto state = this->othelloGame.getState();
  const auto blackBitBoard = std::get<indexOf(black)>(state);
  const auto whiteBitBoard = std::get<indexOf(white)>(state);

  std::string textView =
  "     A   B   C   D   E   F   G   H  \n"
  "   +---+---+---+---+---+---+---+---+\n";

  for (std::size_t i = 0; i < othelloRowSize; i++) {
    const auto blackRow = getRow(blackBitBoard, i);
    const auto whiteRow = getRow(whiteBitBoard, i);
    std::string row = "|";
    for (std::size_t j = 0; j < othelloRowSize; j++) {
      bool isBlack = (blackRow >> j) & 1;
      bool isWhite = (whiteRow >> j) & 1;
      if (isBlack)
        row = " b " + row;
      else if (isWhite)
        row = " w " + row;
      else
        row = "   " + row;
      row = "|" + row;
    }
    textView += " " + std::to_string(i + 1) + " " + row + "\n"
                + "   +---+---+---+---+---+---+---+---+\n";
  }
  return textView;
}

const bool _isValidInput(const std::string input) {
  if (input.length() != 2)
    return false;
  if (input.at(0) > 'H' or input.at(0) < 'A')
    return false;
  if (input.at(1) > '8' or input.at(1) < '1')
    return false;
  return true;
}

const OthelloMoves _parseMove(const std::string input) {
  const std::size_t colNum = input.at(0) - 'A';
  const std::size_t rowNum = input.at(1) - '1';
  return positionToBoard<OthelloMoves>(colNum, rowNum);
}

const bool _isValidMove(const OthelloMoves move, const OthelloMoves allowed) {
  return move & allowed;
}

const OthelloMoves OthelloTextController::requestControl(void) const {
  std::string input = "";
  OthelloMoves move = 0;
  const OthelloMoves allowed = OthelloGame::getMoves(
    this->othelloGame.getState(), this->othelloGame.getPlayer()
  );

  while (true) {
    std::cout << "Input move coordinates: ";
    std::cin >> input;
    if (not _isValidInput(input))
      std::cout << "Invalid input!" << std::endl;
    else {
      move = _parseMove(input);
      if (not _isValidMove(move, allowed))
        std::cout << "Invalid move!" << std::endl;
      else
        break;
    }
  }

  return move;
}

void OthelloTextController::applyControl(const OthelloMoves move) {
  this->othelloGame.applyMove(move);
}
