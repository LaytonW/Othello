#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__

template <typename GameType, typename ViewType, typename MoveType>
class Controller {
public:
  Controller() = default;
  Controller(const Controller&) = delete;
  Controller& operator=(const Controller&) = delete;
  Controller(Controller&&) = delete;
  Controller& operator=(Controller&&) = delete;
  virtual const ViewType getView(void) const = 0;
  virtual void applyMove(const MoveType) = 0;
  virtual void pass(void) = 0;
  virtual const MoveType getMove(void) const = 0;
  virtual bool isTerminal(void) const = 0;
  ~Controller() = default;
};

#endif
