#ifndef __GAME_HPP__
#define __GAME_HPP__

template
 <typename StateType,   typename ActionType,
  typename UtilityType, typename PlayerType>
class Game {
public:
  Game();
  Game(const Game&) = default;
  Game& operator=(const Game&) = default;
  Game(Game&&) = default;
  Game& operator=(Game&&) = default;
  virtual const ActionType getActions(const StateType&,
                                      const PlayerType) const = 0;
  virtual const StateType getResult(const StateType&,
                                    const PlayerType,
                                    const ActionType) const = 0;
  virtual void applyAction(const StateType&,
                           const ActionType) = 0;
  virtual const UtilityType getUtility(const StateType&,
                                       const PlayerType) const = 0;
  virtual const bool isTerminal(const StateType&) const = 0;
  virtual const PlayerType getPlayer(void) const = 0;
  virtual ~Game() = 0;
};

#endif
