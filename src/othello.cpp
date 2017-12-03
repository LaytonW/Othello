#include <iostream>

#include "othello_game.hpp"
#include "othello_player.hpp"
#include "othello_controller.hpp"

using namespace Othello;

int main() {
  OthelloTextController controller(
    OthelloGame(),
    std::make_shared<OthelloQueryPlayer>(OthelloQueryPlayer("Black")),
    std::make_shared<OthelloAlphaBetaPlayer>(OthelloAlphaBetaPlayer("White"))
  );

  std::cout << controller.getView() << std::endl;
  while (true) {
    if (controller.isTerminal()) {
      std::cout << "Game over, ";
      if (controller.getUtility(black) == 1)
        std::cout << "black win!" << std::endl;
      else if (controller.getUtility(white) == 1)
        std::cout << "white win!" << std::endl;
      else
        std::cout << "draw!" << std::endl;
      std::cout << "Black: " << controller.getCount(black) << '\n'
                << "White: " << controller.getCount(white) << std::endl;
      break;
    }
    const auto player = controller.getPlayer();
    std::cout << player->getName() << "'s turn." << std::endl;
    if (controller.noMove()) {
      std::cout << '\n' << player->getName() << " has no available move, "
                << "pass over.\n" << std::endl;
      controller.pass();
    } else {
      const auto move = controller.getMove();
      std::cout << '\n' << player->getName() << " played at "
      << OthelloTextController::asString(move) << '\n' << std::endl;
      controller.applyMove(move);
      std::cout << controller.getView() << std::endl;
    }
  }

  return 0;
}
