#ifndef __GAME_HPP__
#define __GAME_HPP__

template
 <typename StateType,   typename MoveType,
  typename UtilityType, typename PlayerType>
class Game {
public:
  Game() = default;
  Game(const Game&) = default;
  Game& operator=(const Game&) = default;
  Game(Game&&) = default;
  Game& operator=(Game&&) = default;
  static const MoveType getMoves(const StateType&, const PlayerType);
  static const UtilityType getUtility(const StateType&, const PlayerType);
  static const bool isTerminal(const StateType&);
  static const StateType getResult(const StateType&,
                                   const PlayerType,
                                   const MoveType);
  virtual void applyMove(const StateType&, const MoveType) = 0;
  virtual const StateType getState(void) const = 0;
  virtual const PlayerType getPlayer(void) const = 0;
  ~Game() = default;
};

#endif
