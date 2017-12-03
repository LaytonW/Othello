#include <iostream>
#include <cstdint>
#include <cassert>

#include <tuple>

#include "utils.hpp"
#include "othello_game.hpp"

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

  // Test getResult
  const auto result1 = OthelloGame::getResult(
    othelloGame.getState(), othelloGame.getPlayer(),
    positionToBoard<OthelloMoves>(3, 2)
  );
  assert(std::get<0>(result1) ==
    (positionToBoard<OthelloBitBoard>(3, 4)
    | positionToBoard<OthelloBitBoard>(4, 3)
    | positionToBoard<OthelloBitBoard>(3, 2)
    | positionToBoard<OthelloBitBoard>(3, 3)));
  assert(std::get<1>(result1) == positionToBoard<OthelloBitBoard>(4, 4));
  const auto result2 = OthelloGame::getResult(
    result1, white,
    positionToBoard<OthelloMoves>(2, 4)
  );
  assert(std::get<0>(result2) ==
    (positionToBoard<OthelloBitBoard>(4, 3)
    | positionToBoard<OthelloBitBoard>(3, 3)
    | positionToBoard<OthelloBitBoard>(3, 2)));
  assert(std::get<1>(result2) ==
    (positionToBoard<OthelloBitBoard>(3, 4)
    | positionToBoard<OthelloBitBoard>(4, 4)
    | positionToBoard<OthelloBitBoard>(2, 4)));

  // Test getMoves, getPlayer, and applyMove
  assert(othelloGame.getPlayer() == black);
  const auto moves1 = OthelloGame::getMoves(
    othelloGame.getState(), othelloGame.getPlayer()
  );
  assert(moves1 ==
    (positionToBoard<OthelloMoves>(2, 3)
    | positionToBoard<OthelloMoves>(3, 2)
    | positionToBoard<OthelloMoves>(4, 5)
    | positionToBoard<OthelloMoves>(5, 4)));
  const auto moves2 = OthelloGame::getMoves(
    std::make_tuple(
      positionToBoard<OthelloBitBoard>(3, 3),
      positionToBoard<OthelloBitBoard>(4, 4)
    ),
    black
  );
  assert(moves2 == positionToBoard<OthelloMoves>(5, 5));
  const auto moves3 = OthelloGame::getMoves(
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

  othelloGame.applyMove(positionToBoard<OthelloMoves>(3, 2));
  assert(othelloGame.getPlayer() == white);
  assert(std::get<0>(othelloGame.getState()) ==
    (positionToBoard<OthelloBitBoard>(3, 4)
    | positionToBoard<OthelloBitBoard>(4, 3)
    | positionToBoard<OthelloBitBoard>(3, 2)
    | positionToBoard<OthelloBitBoard>(3, 3)));
  assert(std::get<1>(result1) == positionToBoard<OthelloBitBoard>(4, 4));

  const auto moves4 = OthelloGame::getMoves(
    othelloGame.getState(), othelloGame.getPlayer()
  );

  assert(moves4 ==
    (positionToBoard<OthelloMoves>(2, 2)
    | positionToBoard<OthelloMoves>(2, 4)
    | positionToBoard<OthelloMoves>(4, 2)));

  othelloGame.applyMove(positionToBoard<OthelloMoves>(2, 2));
  assert(othelloGame.getPlayer() == black);
  assert(std::get<0>(othelloGame.getState()) ==
    (positionToBoard<OthelloBitBoard>(3, 4)
    | positionToBoard<OthelloBitBoard>(4, 3)
    | positionToBoard<OthelloBitBoard>(3, 2)));
  assert(std::get<1>(othelloGame.getState()) ==
    (positionToBoard<OthelloBitBoard>(4, 4)
    | positionToBoard<OthelloBitBoard>(3, 3)
    | positionToBoard<OthelloBitBoard>(2, 2)));

  const auto moves5 = OthelloGame::getMoves(
    othelloGame.getState(), othelloGame.getPlayer()
  );

  assert(moves5 ==
    (positionToBoard<OthelloMoves>(1, 2)
    | positionToBoard<OthelloMoves>(2, 3)
    | positionToBoard<OthelloMoves>(5, 4)
    | positionToBoard<OthelloMoves>(4, 5)));

  othelloGame.applyMove(positionToBoard<OthelloMoves>(2, 3));
  assert(othelloGame.getPlayer() == white);
  assert(std::get<0>(othelloGame.getState()) ==
    (positionToBoard<OthelloBitBoard>(3, 4)
    | positionToBoard<OthelloBitBoard>(4, 3)
    | positionToBoard<OthelloBitBoard>(3, 3)
    | positionToBoard<OthelloBitBoard>(2, 3)
    | positionToBoard<OthelloBitBoard>(3, 2)));
  assert(std::get<1>(othelloGame.getState()) ==
    (positionToBoard<OthelloBitBoard>(4, 4)
    | positionToBoard<OthelloBitBoard>(2, 2)));

  const auto moves6 = OthelloGame::getMoves(
    othelloGame.getState(), othelloGame.getPlayer()
  );

  assert(moves6 ==
    (positionToBoard<OthelloMoves>(4, 2)
    | positionToBoard<OthelloMoves>(2, 4)));

  std::cout << "All tests passed for Othello Game!" << std::endl;
  return 0;
}
