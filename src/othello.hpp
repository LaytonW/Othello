#ifndef __OTHELLO_HPP__
#define __OTHELLO_HPP__

#include <cstdint>
#include <tuple>

#include "game.hpp"

namespace Othello {
  using OthelloBitBoard = uint64_t;
  using OthelloUtility  = int8_t; // Win, lose, or tie
  using OthelloMoves    = OthelloBitBoard;
  using OthelloState    = std::tuple<OthelloBitBoard, OthelloBitBoard>;
  enum  OthelloPlayer { black = -1, white = 1 };

  class OthelloGame final: Game <OthelloState, OthelloMoves,
                                 OthelloUtility, OthelloPlayer> {
  private:
    OthelloBitBoard blackBitBoard = 0;
    OthelloBitBoard whiteBitBoard = 0;
    OthelloPlayer   currentPlayer = black;

  public:
    OthelloGame();
    const OthelloState getState(void) const override;
    const OthelloMoves getMoves(const OthelloState&,
                                const OthelloPlayer) const override;
    const OthelloState getResult(const OthelloState&,
                                 const OthelloPlayer,
                                 const OthelloMoves) const override;
    void applyMoves(const OthelloState&,
                    const OthelloMoves) override;
    const OthelloUtility getUtility(const OthelloState&,
                                    const OthelloPlayer) const override;
    const bool isTerminal(const OthelloState&) const override;
    const OthelloPlayer getPlayer(void) const override;
    ~OthelloGame() = default;
  };
}

#endif
