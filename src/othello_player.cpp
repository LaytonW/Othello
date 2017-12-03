#include <iostream>

#include "othello_player.hpp"

using namespace Othello;

OthelloQueryPlayer::OthelloQueryPlayer(const std::string name) :Player(name) {
  this->player = name == "Black" ? black : white;
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

const OthelloMoves
OthelloQueryPlayer::getMove(const OthelloState& state) const {
  std::string input = "";
  OthelloMoves move = 0;
  const OthelloMoves allowed = OthelloGame::getMoves(state, this->player);

  while (true) {
    std::cout << "Input move coordinates (e.g.: D3): ";
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

OthelloAlphaBetaPlayer::OthelloAlphaBetaPlayer(const std::string name)
  :Player(name) {
  this->player = name == "Black" ? black : white;
}

const OthelloMoves
OthelloAlphaBetaPlayer::getMove(const OthelloState& state) const {
  // TODO: implement alpha beta pruning search
  return 0;
}
