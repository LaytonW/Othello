#ifndef __GAME_HPP__
#define __GAME_HPP__

template
 <typename StateType,   typename ActionType,
  typename UtilityType, typename PlayerType>
class Game {
public:
  Game();
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;
  Game(Game&&) = delete;
  Game& operator=(Game&&) = delete;
  virtual const ActionType getActions(const StateType&) const = 0;
  virtual const StateType getResult(const StateType&,
                                    const ActionType) const = 0;
  virtual void performAction(const StateType&, const ActionType) = 0;
  virtual const UtilityType getUtility(const StateType&,
                                       const PlayerType) const = 0;
  virtual const bool isTerminal(const StateType&) const = 0;
  virtual const PlayerType getPlayer(const StateType&) const = 0;
  virtual ~Game() = 0;
};

#endif
