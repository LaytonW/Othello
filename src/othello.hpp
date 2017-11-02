#ifndef __OTHELLO_HPP__
#define __OTHELLO_HPP__

#include <tuple>

#include "game.hpp"

namespace Othello {
  using OthelloBitBoard = unsigned long long;
  using OthelloUtility  = unsigned long long;
  using OthelloAction   = unsigned char;
  using OthelloState    = std::tuple<OthelloBitBoard, OthelloBitBoard>;
  enum  OthelloPlayer { black = -1, white = 1 };
  
  class OthelloGame final: Game <OthelloState, OthelloAction,
                                 OthelloUtility, OthelloPlayer> {
  private:
    OthelloBitBoard blackBitBoard = 0;
    OthelloBitBoard whiteBitBoard = 0;
    OthelloPlayer   currentPlayer = black;

  public:
    OthelloGame();
    const OthelloAction getActions(const OthelloState&) const override;
    const OthelloState getResult(const OthelloState&,
                                 const OthelloAction) const override;
    void performAction(const OthelloState&, const OthelloAction) override;
    const OthelloUtility getUtility(const OthelloState&,
                                    const OthelloPlayer) const override;
    const bool isTerminal(const OthelloState&) const override;
    const OthelloPlayer getPlayer(const OthelloState&) const override;
    ~OthelloGame();
  };
}

#endif
