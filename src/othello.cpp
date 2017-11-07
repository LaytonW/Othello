#include <limits>

#include "utils.hpp"
#include "othello.hpp"

using namespace Othello;

using OthelloRow =
  BitType<isqrt<std::numeric_limits<OthelloBitBoard>::digits>::value>;

constexpr auto othelloRowSize = std::numeric_limits<OthelloRow>::digits;

constexpr std::size_t indexOf(const OthelloPlayer player) {
  return player == black ? 0 : 1;
}

OthelloGame::OthelloGame() {
  this->blackBitBoard |= positionToBoard<OthelloBitBoard>(3, 4);
  this->blackBitBoard |= positionToBoard<OthelloBitBoard>(4, 3);
  this->whiteBitBoard |= positionToBoard<OthelloBitBoard>(3, 3);
  this->whiteBitBoard |= positionToBoard<OthelloBitBoard>(4, 4);
}

OthelloGame::~OthelloGame() {}

const OthelloAction OthelloGame::getActions(const OthelloState& state,
                                            const OthelloPlayer player) const {
  // OthelloBitBoard playerBoard, opponentBoard;
  //
  // if (player == black) {
  //   playerBoard   = std::get<indexOf(black)>(state);
  //   opponentBoard = std::get<indexOf(white)>(state);
  // } else {
  //   playerBoard   = std::get<indexOf(white)>(state);
  //   opponentBoard = std::get<indexOf(black)>(state);
  // }
  //
  // auto clockRotate45PlayerBoard   = clockRotate45(playerBoard);
  // auto clockRotate45OpponentBoard = clockRotate45(opponentBoard);
  //
  // for (std::size_t i = 0; i < othelloRowSize; i++) {
  //   auto upperMask = static_cast<OthelloRow>(1) << (othelloRowSize - 1 - i);
  //   auto lowerMask = ~upperMask;
  // }

  return 0;
}

const OthelloState OthelloGame::getResult(const OthelloState& state,
                                          const OthelloPlayer player,
                                          const OthelloAction action) const {
  auto blackBitBoard = std::get<indexOf(black)>(state);
  auto whiteBitBoard = std::get<indexOf(white)>(state);
  if (player == black)
    blackBitBoard |= actionToBoard(action);
  else
    whiteBitBoard |= actionToBoard(action);
  return std::make_tuple(blackBitBoard, whiteBitBoard);
}

void OthelloGame::applyAction(const OthelloState& state,
                              const OthelloAction action) {
  this->blackBitBoard = std::get<indexOf(black)>(state);
  this->whiteBitBoard = std::get<indexOf(white)>(state);
  if (this->currentPlayer == black)
    blackBitBoard |= actionToBoard(action);
  else
    whiteBitBoard |= actionToBoard(action);
  this->currentPlayer = static_cast<OthelloPlayer>(-this->currentPlayer);
}

const OthelloUtility
OthelloGame::getUtility(const OthelloState& state,
                        const OthelloPlayer player) const {
  // TODO: check if is terminal state
  char whiteUtility =
    countOnes(this->blackBitBoard) == countOnes(this->whiteBitBoard) ? 0 :
    countOnes(this->blackBitBoard) <  countOnes(this->whiteBitBoard) ? 1 : -1;
  return player * whiteUtility;
}

const bool OthelloGame::isTerminal(const OthelloState& state) const {
  bool filled = (this->blackBitBoard | this->whiteBitBoard) == ~0ull;
  bool noMove = this->getActions(state, black) == 0 and
                this->getActions(state, white) == 0;
  return filled or noMove;
}

const OthelloPlayer OthelloGame::getPlayer(void) const {
  return this->currentPlayer;
}
