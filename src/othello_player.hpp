#ifndef __OTHELLO_PLAYER_HPP__
#define __OTHELLO_PLAYER_HPP__

#include "othello_game.hpp"
#include "player.hpp"

namespace Othello {
  class OthelloQueryPlayer final: public Player<OthelloState, OthelloMoves> {
  private:
    OthelloPlayer player;
  public:
    OthelloQueryPlayer() = delete;
    OthelloQueryPlayer(const OthelloQueryPlayer&) = default;
    OthelloQueryPlayer& operator=(const OthelloQueryPlayer&) = default;
    OthelloQueryPlayer(OthelloQueryPlayer&&) = default;
    OthelloQueryPlayer& operator=(OthelloQueryPlayer&&) = default;
    ~OthelloQueryPlayer() = default;

    OthelloQueryPlayer(const std::string);

    const OthelloMoves getMove(const OthelloState&) const override;
  };

  class OthelloAlphaBetaPlayer final: public Player<OthelloState,
                                                    OthelloMoves> {
  private:
    OthelloPlayer player;
  public:
    OthelloAlphaBetaPlayer() = delete;
    OthelloAlphaBetaPlayer(const OthelloAlphaBetaPlayer&) = default;
    OthelloAlphaBetaPlayer& operator=(const OthelloAlphaBetaPlayer&) = default;
    OthelloAlphaBetaPlayer(OthelloAlphaBetaPlayer&&) = default;
    OthelloAlphaBetaPlayer& operator=(OthelloAlphaBetaPlayer&&) = default;
    ~OthelloAlphaBetaPlayer() = default;

    OthelloAlphaBetaPlayer(const std::string);

    const OthelloMoves getMove(const OthelloState&) const override;
  };
}

#endif
