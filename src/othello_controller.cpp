#include <iostream>

#include "utils.hpp"
#include "othello_controller.hpp"

using namespace Othello;

OthelloTextController::OthelloTextController(
  const OthelloGame& othelloGame,
  const IPlayerPtr blackPlayer,
  const IPlayerPtr whitePlayer
) : othelloGame(othelloGame),
    blackPlayer(blackPlayer),
    whitePlayer(whitePlayer) {}

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

const OthelloMoves OthelloTextController::getMove(void) const {
  return this->othelloGame.getPlayer() == black
         ? this->blackPlayer->getMove(this->othelloGame.getState())
         : this->whitePlayer->getMove(this->othelloGame.getState());
}

void OthelloTextController::applyMove(const OthelloMoves move) {
  this->othelloGame.applyMove(move);
}

void OthelloTextController::pass(void) {
  this->othelloGame.pass();
}

bool OthelloTextController::isTerminal(void) const {
  return OthelloGame::isTerminal(this->othelloGame.getState());
}

const IPlayerPtr OthelloTextController::getPlayer(void) const {
  return this->othelloGame.getPlayer() == black
         ? this->blackPlayer : this->whitePlayer;
}

const OthelloUtility
OthelloTextController::getUtility(const OthelloPlayer player) const {
  return OthelloGame::getUtility(this->othelloGame.getState(), player);
}

const std::size_t
OthelloTextController::getCount(const OthelloPlayer player) const {
  return this->othelloGame.getCount(player);
}

bool OthelloTextController::noMove(void) const {
  return OthelloGame::getMoves(
    this->othelloGame.getState(), this->othelloGame.getPlayer()
  ) == 0;
}

const std::string OthelloTextController::asString(const OthelloMoves move) {
  std::string res = "";
  res.push_back("ABCDEFGH"[getColNum(move)]);
  res.push_back("12345678"[getRowNum(move)]);
  return res;
}
