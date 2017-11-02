#ifndef __GAME_HPP__
#define __GAME_HPP__

template
 <typename StateType,   typename ActionType,
  typename UtilityType, typename PlayerType>
class Game {
public:
  Game();
  virtual const ActionType getActions(const StateType&) const = 0;
  virtual const StateType getResult(const ActionType) const = 0;
  virtual void performAction(StateType&, const ActionType) = 0;
  virtual const UtilityType getUtility(const StateType&,
                                       const PlayerType) const = 0;
  virtual const bool isTerminal(const StateType&) const = 0;
  virtual const PlayerType getPlayer(const StateType&) const = 0;
  virtual ~Game() = 0;
};

#endif
