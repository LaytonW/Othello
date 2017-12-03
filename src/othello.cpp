#include <iostream>

#include "othello_game.hpp"
#include "othello_player.hpp"
#include "othello_controller.hpp"

using namespace Othello;

int main() {
  OthelloTextController controller(
    OthelloGame(),
    std::make_shared<OthelloQueryPlayer>(OthelloQueryPlayer("Black")),
    std::make_shared<OthelloQueryPlayer>(OthelloQueryPlayer("White"))
  );

  while (true) {
    std::cout << controller.getView() << std::endl;
    if (controller.isTerminal()) {
      if (controller.getUtility(black) == 1)
      std::cout << "\nBlack win!" << std::endl;
      else if (controller.getUtility(white) == 1)
      std::cout << "\nWhite win!" << std::endl;
      else
      std::cout << "\nGame draw!" << std::endl;
      break;
    }
    const auto player = controller.getPlayer();
    std::cout << player->getName() << "'s turn." << std::endl;
    const auto move = controller.getMove();
    std::cout << '\n' << player->getName() << " played at "
              << OthelloTextController::asString(move) << '\n' << std::endl;
    controller.applyMove(move);
  }

  return 0;
}
