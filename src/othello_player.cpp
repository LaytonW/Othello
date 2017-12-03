#include <iostream>
#include <functional>
#include <limits>
#include <cmath>

#include "utils.hpp"
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

using EvalFuncType =
  std::function<const double (const OthelloState&, const OthelloPlayer)>;
using StopFuncType =
  std::function<bool (const OthelloState&, const std::size_t)>;

const OthelloMoves alphaBetaSearch(
  const OthelloState& state,
  const OthelloPlayer player,
  const std::size_t maxDepth=10,
  StopFuncType stopFunc={},
  EvalFuncType evalFunc={}
) {
  std::function<double (
    const OthelloState&, const OthelloPlayer, double, double, const std::size_t
  )> maxValue, minValue;

  if (not stopFunc)
    stopFunc = [=] (const auto state, const auto depth) {
      return depth > maxDepth or OthelloGame::isTerminal(state);
    };
  if (not evalFunc)
    evalFunc = [] (const auto state, const auto player) {
      return OthelloGame::getUtility(state, player);
    };

  maxValue = [&] (
    const OthelloState& state,
    const OthelloPlayer player,
    double alpha,
    double beta,
    const std::size_t depth
  ) {
    if (stopFunc(state, depth))
      return evalFunc(state, player);
    auto value = -std::numeric_limits<double>::infinity();
    auto moves = OthelloGame::getMoves(state, player);
    while (moves) {
      const auto move = extractLastOne(moves);
      moves = removeLastOne(moves);
      value = std::max(
        value,
        minValue(
          OthelloGame::getResult(
            state, static_cast<OthelloPlayer>(player), move
          ), static_cast<OthelloPlayer>(-player), alpha, beta, depth + 1
        )
      );
      if (value >= beta)
        return value;
      alpha = std::max(alpha, value);
    }
    return value;
  };

  minValue = [&] (
    const OthelloState& state,
    const OthelloPlayer player,
    double alpha,
    double beta,
    const std::size_t depth
  ) {
    if (stopFunc(state, depth))
      return evalFunc(state, player);
    auto value = std::numeric_limits<double>::infinity();
    auto moves = OthelloGame::getMoves(state, player);
    while (moves) {
      const auto move = extractLastOne(moves);
      moves = removeLastOne(moves);
      value = std::min(
        value,
        maxValue(
          OthelloGame::getResult(
            state, static_cast<OthelloPlayer>(player), move
          ), static_cast<OthelloPlayer>(-player), alpha, beta, depth + 1
        )
      );
      if (value <= alpha)
        return value;
      beta = std::min(beta, value);
    }
    return value;
  };

  auto bestScore = -std::numeric_limits<double>::infinity();
  auto beta = std::numeric_limits<double>::infinity();
  OthelloMoves bestMove = 0;
  auto moves = OthelloGame::getMoves(state, player);
  while (moves) {
    const auto move = extractLastOne(moves);
    moves = removeLastOne(moves);
    auto value = minValue(
      OthelloGame::getResult(state, static_cast<OthelloPlayer>(player), move),
      static_cast<OthelloPlayer>(-player), bestScore, beta, 1
    );
    if (value > bestScore) {
      bestScore = value;
      bestMove  = move;
    }
  }

  return bestMove;
}

const double
differenceEvalFunc(const OthelloState& state, const OthelloPlayer player) {
  OthelloBitBoard playerBoard =
    player == black ? std::get<indexOf(black)>(state)
                    : std::get<indexOf(white)>(state);
  OthelloBitBoard opponentBoard =
    player == black ? std::get<indexOf(white)>(state)
                    : std::get<indexOf(black)>(state);

  return static_cast<double>(countOnes(playerBoard))
         - static_cast<double>(countOnes(opponentBoard));
}

const double
L1WeightedEvalFunc(const OthelloState& state, const OthelloPlayer player) {
  OthelloBitBoard playerBoard =
    player == black ? std::get<indexOf(black)>(state)
                    : std::get<indexOf(white)>(state);
  OthelloBitBoard opponentBoard =
    player == black ? std::get<indexOf(white)>(state)
                    : std::get<indexOf(black)>(state);

  double playerScore = 0., opponentScore = 0.;

  while (playerBoard) {
    const auto token = extractLastOne(playerBoard);
    playerBoard = removeLastOne(playerBoard);
    const auto rowNum = static_cast<double>(getRowNum(token));
    const auto colNum = static_cast<double>(getColNum(token));
    playerScore += std::abs(rowNum - 3.5) + std::abs(colNum - 3.5);
  }

  while (opponentBoard) {
    const auto token = extractLastOne(opponentBoard);
    opponentBoard = removeLastOne(opponentBoard);
    const auto rowNum = static_cast<double>(getRowNum(token));
    const auto colNum = static_cast<double>(getColNum(token));
    opponentScore += std::abs(rowNum - 3.5) + std::abs(colNum - 3.5);
  }

  return playerScore - opponentScore;
}

const double
L2WeightedEvalFunc(const OthelloState& state, const OthelloPlayer player) {
  OthelloBitBoard playerBoard =
    player == black ? std::get<indexOf(black)>(state)
                    : std::get<indexOf(white)>(state);
  OthelloBitBoard opponentBoard =
    player == black ? std::get<indexOf(white)>(state)
                    : std::get<indexOf(black)>(state);

  double playerScore = 0., opponentScore = 0.;

  while (playerBoard) {
    const auto token = extractLastOne(playerBoard);
    playerBoard = removeLastOne(playerBoard);
    const auto rowNum = static_cast<double>(getRowNum(token));
    const auto colNum = static_cast<double>(getColNum(token));
    playerScore += std::pow(rowNum - 3.5, 2) + std::pow(colNum - 3.5, 2);
  }

  while (opponentBoard) {
    const auto token = extractLastOne(opponentBoard);
    opponentBoard = removeLastOne(opponentBoard);
    const auto rowNum = static_cast<double>(getRowNum(token));
    const auto colNum = static_cast<double>(getColNum(token));
    opponentScore += std::pow(rowNum - 3.5, 2) + std::pow(colNum - 3.5, 2);
  }

  return playerScore - opponentScore;
}

const OthelloMoves
OthelloAlphaBetaPlayer::getMove(const OthelloState& state) const {
  return alphaBetaSearch(state, this->player, 11, {}, differenceEvalFunc);
}
