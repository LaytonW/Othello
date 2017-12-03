#include <limits>

#include "utils.hpp"
#include "othello_game.hpp"

using namespace Othello;

OthelloGame::OthelloGame() {
  this->blackBitBoard |= positionToBoard<OthelloBitBoard>(3, 4);
  this->blackBitBoard |= positionToBoard<OthelloBitBoard>(4, 3);
  this->whiteBitBoard |= positionToBoard<OthelloBitBoard>(3, 3);
  this->whiteBitBoard |= positionToBoard<OthelloBitBoard>(4, 4);
}

const OthelloState OthelloGame::getState(void) const {
  return std::make_tuple(this->blackBitBoard, this->whiteBitBoard);
}

const OthelloMoves OthelloGame::getMoves(const OthelloState& state,
                                         const OthelloPlayer player) {
  const OthelloBitBoard playerBoard =
    player == black ? std::get<indexOf(black)>(state)
                    : std::get<indexOf(white)>(state);
  const OthelloBitBoard opponentBoard =
    player == black ? std::get<indexOf(white)>(state)
                    : std::get<indexOf(black)>(state);

  const OthelloBitBoard emptyBoard = ~(playerBoard | opponentBoard);
  OthelloMoves moves = 0;

  OthelloBitBoard intersecBoard;
  for (std::size_t i = 0; i < othelloRowSize; i++) {
    intersecBoard = opponentBoard & shiftBoard(playerBoard, i);

    intersecBoard |= opponentBoard & shiftBoard(intersecBoard, i);
    intersecBoard |= opponentBoard & shiftBoard(intersecBoard, i);
    intersecBoard |= opponentBoard & shiftBoard(intersecBoard, i);
    intersecBoard |= opponentBoard & shiftBoard(intersecBoard, i);
    intersecBoard |= opponentBoard & shiftBoard(intersecBoard, i);

    moves |= emptyBoard & shiftBoard(intersecBoard, i);
  }
  return moves;
}

const OthelloState OthelloGame::getResult(const OthelloState& state,
                                          const OthelloPlayer player,
                                          const OthelloMoves  move) {
  auto blackBitBoard = std::get<indexOf(black)>(state);
  auto whiteBitBoard = std::get<indexOf(white)>(state);
  auto& playerBoard = player == black ? blackBitBoard : whiteBitBoard;
  auto& opponentBoard = player == black ? whiteBitBoard : blackBitBoard;

  OthelloBitBoard intersecBoard, surroundBoard, filpBoard = 0;

  playerBoard |= move;

  for (std::size_t i = 0; i < othelloRowSize; i++) {
    intersecBoard = opponentBoard & shiftBoard(move, i);

    intersecBoard |= opponentBoard & shiftBoard(intersecBoard, i);
    intersecBoard |= opponentBoard & shiftBoard(intersecBoard, i);
    intersecBoard |= opponentBoard & shiftBoard(intersecBoard, i);
    intersecBoard |= opponentBoard & shiftBoard(intersecBoard, i);
    intersecBoard |= opponentBoard & shiftBoard(intersecBoard, i);

    surroundBoard = playerBoard & shiftBoard(intersecBoard, i);
    filpBoard |= (surroundBoard ? intersecBoard : 0);
  }

  playerBoard   ^= filpBoard;
  opponentBoard ^= filpBoard;

  return std::make_tuple(blackBitBoard, whiteBitBoard);
}

void OthelloGame::applyMove(const OthelloMoves move) {
  const auto state = this->getState();
  const auto res = OthelloGame::getResult(state, this->currentPlayer, move);
  this->blackBitBoard = std::get<indexOf(black)>(res);
  this->whiteBitBoard = std::get<indexOf(white)>(res);
  this->currentPlayer = static_cast<OthelloPlayer>(-this->currentPlayer);
}

void OthelloGame::pass(void) {
  this->currentPlayer = static_cast<OthelloPlayer>(-this->currentPlayer);
}

const OthelloUtility
OthelloGame::getUtility(const OthelloState& state, const OthelloPlayer player) {
  const auto blackBitBoard = std::get<indexOf(black)>(state);
  const auto whiteBitBoard = std::get<indexOf(white)>(state);
  char whiteUtility =
    countOnes(blackBitBoard) == countOnes(whiteBitBoard) ? 0 :
    countOnes(blackBitBoard) <  countOnes(whiteBitBoard) ? 1 : -1;
  return player * whiteUtility;
}

const std::size_t OthelloGame::getCount(const OthelloPlayer player) const {
  const auto board =
    player == black ? std::get<indexOf(black)>(this->getState())
                    : std::get<indexOf(white)>(this->getState());
  return countOnes(board);
}

const bool OthelloGame::isTerminal(const OthelloState& state) {
  const auto blackBitBoard = std::get<indexOf(black)>(state);
  const auto whiteBitBoard = std::get<indexOf(white)>(state);
  bool filled = (blackBitBoard | whiteBitBoard) ==
    ~static_cast<OthelloBitBoard>(0);
  bool noMove = OthelloGame::getMoves(state, black) == 0 and
                OthelloGame::getMoves(state, white) == 0;
  return filled or noMove;
}

const OthelloPlayer OthelloGame::getPlayer(void) const {
  return this->currentPlayer;
}
