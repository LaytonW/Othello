#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <string>

template <typename GameStateType, typename MoveType>
class Player {
private:
  std::string name;
public:
  Player() = delete;
  Player(const Player&) = default;
  Player& operator=(const Player&) = default;
  Player(Player&&) = default;
  Player& operator=(Player&&) = default;
  ~Player() = default;

  Player(const std::string name) :name(name) {}

  const std::string getName(void) const { return this->name; }
  virtual const MoveType getMove(const GameStateType&) const = 0;
};

#endif
