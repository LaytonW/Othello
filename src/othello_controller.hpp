#ifndef __OTHELLO_CONTROLLER_HPP__
#define __OTHELLO_CONTROLLER_HPP__

#include <string>
#include <memory>

#include "othello_game.hpp"
#include "controller.hpp"
#include "player.hpp"

namespace Othello {
  using IPlayer = Player<OthelloState, OthelloMoves>;
  using IPlayerPtr = std::shared_ptr<IPlayer>;

  class OthelloTextController: public Controller <OthelloGame, std::string,
                                                  OthelloMoves> {
  private:
    OthelloGame othelloGame;
    IPlayerPtr blackPlayer;
    IPlayerPtr whitePlayer;
  public:
    OthelloTextController() = delete;
    OthelloTextController(const OthelloTextController&) = default;
    OthelloTextController& operator=(const OthelloTextController&) = default;
    OthelloTextController(OthelloTextController&&) = default;
    OthelloTextController& operator=(OthelloTextController&&) = default;
    ~OthelloTextController() = default;

    OthelloTextController(
      const OthelloGame&,
      const IPlayerPtr,
      const IPlayerPtr
    );

    const std::string getView(void) const override;
    void applyMove(const OthelloMoves) override;
    void pass(void) override;
    const OthelloMoves getMove(void) const override;
    bool isTerminal(void) const override;

    const IPlayerPtr getPlayer(void) const;
    const OthelloUtility getUtility(const OthelloPlayer) const;
    bool noMove(void) const;

    static const std::string asString(const OthelloMoves);
  };
}

#endif
