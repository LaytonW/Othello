#include "othello.hpp"

using namespace Othello;

inline OthelloAction positionToAction(const uint8_t x, const uint8_t y) {
  return x + 8 * y;
}

inline OthelloBitBoard actionToBoard(const OthelloAction action) {
  return 1ull << (63 - action);
}

inline OthelloBitBoard positionToBoard(const uint8_t x, const uint8_t y) {
  return actionToBoard(positionToAction(x, y));
}

constexpr inline const std::size_t indexOf(const OthelloPlayer player) {
  return player == black ? 0 : 1;
}

inline uint8_t countToken(const OthelloBitBoard board) {
  if (board == 0)
    return 0;
  auto tmp = board;
  uint8_t count = 1;
  while (tmp &= tmp - 1)
    count ++;
  return count;
}

OthelloGame::OthelloGame() {
  this->blackBitBoard |= positionToBoard(3, 4);
  this->blackBitBoard |= positionToBoard(4, 3);
  this->whiteBitBoard |= positionToBoard(3, 3);
  this->whiteBitBoard |= positionToBoard(4, 4);
}

OthelloGame::~OthelloGame() {}

const OthelloAction OthelloGame::getActions(const OthelloState& state,
                                            const OthelloPlayer player) const {
  // TODO
  // auto blackBitBoard = std::get<indexOf(black)>(state);
  // auto whiteBitBoard = std::get<indexOf(white)>(state);
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
    countToken(this->blackBitBoard) == countToken(this->whiteBitBoard) ? 0 :
    countToken(this->blackBitBoard) <  countToken(this->whiteBitBoard) ? 1 : -1;
  return player * whiteUtility;
}

const bool OthelloGame::isTerminal(const OthelloState& state) const {
  bool filled = (this->blackBitBoard | this->whiteBitBoard) == ~0ull;
  bool noMove = this->getActions(state, black) == 0 &&
                this->getActions(state, white) == 0;
  return filled || noMove;
}

const OthelloPlayer OthelloGame::getPlayer(void) const {
  return this->currentPlayer;
}
