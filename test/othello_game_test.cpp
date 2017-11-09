#include <iostream>
#include <cstdint>
#include <cassert>

#include <tuple>

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

  // Test initial state and getState
  assert(std::get<0>(othelloGame.getState()) ==
    (positionToBoard<OthelloBitBoard>(3, 4)
    | positionToBoard<OthelloBitBoard>(4, 3)));
  assert(std::get<1>(othelloGame.getState()) ==
    (positionToBoard<OthelloBitBoard>(3, 3)
    | positionToBoard<OthelloBitBoard>(4, 4)));

  // Test getPlayer
  assert(othelloGame.getPlayer() == black);
  othelloGame.applyMove(othelloGame.getState(), static_cast<OthelloMoves>(0));
  assert(othelloGame.getPlayer() == white);
  othelloGame.applyMove(othelloGame.getState(), static_cast<OthelloMoves>(0));
  assert(othelloGame.getPlayer() == black);

  // Test getResult
  const auto result1 = othelloGame.getResult(
    othelloGame.getState(), othelloGame.getPlayer(),
    positionToBoard<OthelloMoves>(0, 0)
  );
  assert(std::get<0>(result1) ==
    (positionToBoard<OthelloBitBoard>(3, 4)
    | positionToBoard<OthelloBitBoard>(4, 3)
    | positionToBoard<OthelloBitBoard>(0, 0)));
  assert(std::get<1>(result1) ==
    (positionToBoard<OthelloBitBoard>(3, 3)
    | positionToBoard<OthelloBitBoard>(4, 4)));
  const auto result2 = othelloGame.getResult(
    result1, white,
    positionToBoard<OthelloMoves>(5, 2)
  );
  assert(std::get<0>(result2) ==
    (positionToBoard<OthelloBitBoard>(3, 4)
    | positionToBoard<OthelloBitBoard>(4, 3)
    | positionToBoard<OthelloBitBoard>(0, 0)));
  assert(std::get<1>(result2) ==
    (positionToBoard<OthelloBitBoard>(3, 3)
    | positionToBoard<OthelloBitBoard>(4, 4)
    | positionToBoard<OthelloBitBoard>(5, 2)));

  // Test getMoves and applyMove
  const auto moves1 = othelloGame.getMoves(
    othelloGame.getState(), othelloGame.getPlayer()
  );
  assert(moves1 ==
    (positionToBoard<OthelloMoves>(2, 3)
    | positionToBoard<OthelloMoves>(3, 2)
    | positionToBoard<OthelloMoves>(4, 5)
    | positionToBoard<OthelloMoves>(5, 4)));
  const auto moves2 = othelloGame.getMoves(
    std::make_tuple(
      positionToBoard<OthelloBitBoard>(3, 3),
      positionToBoard<OthelloBitBoard>(4, 4)
    ),
    black
  );
  assert(moves2 == positionToBoard<OthelloMoves>(5, 5));
  const auto moves3 = othelloGame.getMoves(
    std::make_tuple(
      positionToBoard<OthelloBitBoard>(3, 3)
        | positionToBoard<OthelloBitBoard>(3, 4),
      positionToBoard<OthelloBitBoard>(4, 4)
    ),
    white
  );
  assert(moves3 ==
    (positionToBoard<OthelloMoves>(2, 2)
    | positionToBoard<OthelloMoves>(2, 4)));

  othelloGame.applyMove(othelloGame.getState(), static_cast<OthelloMoves>(0));
  assert(std::get<0>(othelloGame.getState()) ==
    (positionToBoard<OthelloBitBoard>(3, 4)
    | positionToBoard<OthelloBitBoard>(4, 3)));
  assert(std::get<1>(othelloGame.getState()) ==
    (positionToBoard<OthelloBitBoard>(3, 3)
    | positionToBoard<OthelloBitBoard>(4, 4)));
  othelloGame.applyMove(othelloGame.getState(), static_cast<OthelloMoves>(0));
  assert(std::get<0>(othelloGame.getState()) ==
    (positionToBoard<OthelloBitBoard>(3, 4)
    | positionToBoard<OthelloBitBoard>(4, 3)));
  assert(std::get<1>(othelloGame.getState()) ==
    (positionToBoard<OthelloBitBoard>(3, 3)
    | positionToBoard<OthelloBitBoard>(4, 4)));
  // TODO: flip opponent tokens
  othelloGame.applyMove(othelloGame.getState(), extractFirstOne(moves1));
  assert(std::get<0>(othelloGame.getState()) ==
    (positionToBoard<OthelloBitBoard>(3, 4)
    | positionToBoard<OthelloBitBoard>(4, 3)
    | positionToBoard<OthelloBitBoard>(3, 2)));
  assert(std::get<1>(othelloGame.getState()) ==
    (positionToBoard<OthelloBitBoard>(4, 4)
    | positionToBoard<OthelloBitBoard>(3, 3)));

  std::cout << "All tests passed for Othello Game!" << std::endl;
  return 0;
}
