#include "othello.hpp"

using namespace Othello;

inline OthelloBitBoard positionToBoard(const unsigned char x,
                                       const unsigned char y) {
  return 1 << (63 - (x + 8 * y));
}

inline OthelloBitBoard actionToBoard(const OthelloAction action) {
  return 1 << (63 - action);
}

inline OthelloAction positionToAction(const unsigned char x,
                                      const unsigned char y) {
  return x + 8 * y;
}

OthelloGame::OthelloGame() {
  this->blackBitBoard |= positionToBoard(3, 3);
  this->blackBitBoard |= positionToBoard(4, 4);
  this->whiteBitBoard |= positionToBoard(3, 4);
  this->whiteBitBoard |= positionToBoard(4, 3);
}

OthelloGame::~OthelloGame() {}

const OthelloAction OthelloGame::getActions(const OthelloState& state) const {
  // TODO
  return 0;
}

const OthelloState OthelloGame::getResult(const OthelloState& state,
                                          const OthelloAction action) const {
  // TODO
  return std::make_tuple(this->blackBitBoard, this->whiteBitBoard);
}

void OthelloGame::performAction(const OthelloState& state,
                                const OthelloAction action) {
  auto res = this->getResult(state, action);
  this->blackBitBoard = std::get<0>(res);
  this->whiteBitBoard = std::get<1>(res);
  this->currentPlayer = static_cast<OthelloPlayer>(-this->currentPlayer);
}

const OthelloUtility
OthelloGame::getUtility(const OthelloState& state,
                        const OthelloPlayer player) const {
  // TODO
  return 0;
}

const bool OthelloGame::isTerminal(const OthelloState& state) const {
  return this->getActions(state) == 0;
}

const OthelloPlayer OthelloGame::getPlayer(const OthelloState& state) const {
  // TODO
  return this->currentPlayer;
}
