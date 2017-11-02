#include "othello.hpp"

using namespace Othello;

OthelloGame::OthelloGame() {
  // TODO
}

OthelloGame::~OthelloGame() {
  // TODO
}

const OthelloAction OthelloGame::getActions(const OthelloState& state) const {
  // TODO
}

const OthelloState OthelloGame::getResult(const OthelloAction action) const {
  // TODO

}

void OthelloGame::performAction(OthelloState& state,
                                const OthelloAction action) {
  // TODO
  this->currentPlayer = static_cast<OthelloPlayer>(-this->currentPlayer);
}

const OthelloUtility
OthelloGame::getUtility(const OthelloState& state,
                        const OthelloPlayer player) const {
  // TODO
}

const bool OthelloGame::isTerminal(const OthelloState& state) const {
  return this->getActions(state) == 0;
}

const OthelloPlayer OthelloGame::getPlayer(const OthelloState& state) const {
  // TODO
  return this->currentPlayer;
}
