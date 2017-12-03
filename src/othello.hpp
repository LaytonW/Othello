#ifndef __OTHELLO_HPP__
#define __OTHELLO_HPP__

#include <cstdint>
#include <tuple>

#include "utils.hpp"
#include "game.hpp"
#include "controller.hpp"

namespace Othello {
  using OthelloBitBoard = uint64_t;
  using OthelloUtility  = int8_t; // Win, lose, or tie
  constexpr auto othelloRowSize =
    isqrt<std::numeric_limits<OthelloBitBoard>::digits>::value;
  using OthelloRow = BitType<othelloRowSize>;
  using OthelloCol = OthelloRow;
  using OthelloMoves = OthelloBitBoard;
  using OthelloState = std::tuple<OthelloBitBoard, OthelloBitBoard>;
  enum  OthelloPlayer { black = -1, white = 1 };

  class OthelloGame final: public Game <OthelloState, OthelloMoves,
                                        OthelloUtility, OthelloPlayer> {
  private:
    OthelloBitBoard blackBitBoard = 0;
    OthelloBitBoard whiteBitBoard = 0;
    OthelloPlayer   currentPlayer = black;

  public:
    OthelloGame();
    const OthelloState getState(void) const override;
    void applyMove(const OthelloMoves) override;
    const OthelloPlayer getPlayer(void) const override;
    static const OthelloMoves getMoves(const OthelloState&,
                                       const OthelloPlayer);
    static const OthelloState getResult(const OthelloState&,
                                        const OthelloPlayer,
                                        const OthelloMoves);
    static const OthelloUtility getUtility(const OthelloState&,
                                           const OthelloPlayer);
    static const bool isTerminal(const OthelloState&);
    ~OthelloGame() = default;
  };

  class OthelloTextController: public Controller <OthelloGame, std::string,
                                                  OthelloMoves> {
  private:
    OthelloGame othelloGame;
  public:
    OthelloTextController() = delete;
    OthelloTextController(const OthelloGame&);
    const std::string getView(void) const override;
    void applyControl(const OthelloMoves) override;
    const OthelloMoves requestControl(void) const override;
    ~OthelloTextController() = default;
  };
}

#endif
