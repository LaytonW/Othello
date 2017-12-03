#ifndef __OTHELLO_CONTROLLER_HPP__
#define __OTHELLO_CONTROLLER_HPP__

#include "othello_game.hpp"
#include "controller.hpp"

namespace Othello {
  class OthelloTextController: public Controller <OthelloGame, std::string,
                                                  OthelloMoves> {
  private:
    OthelloGame othelloGame;
  public:
    OthelloTextController() = delete;
    OthelloTextController(const OthelloGame&);
    const std::string getView(void) const override;
    void applyMove(const OthelloMoves) override;
    const OthelloMoves getMove(void) const override;
    ~OthelloTextController() = default;
  };
}

#endif
