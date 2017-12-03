#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__

template <typename GameType, typename ViewType, typename ControlType>
class Controller {
public:
  Controller() = default;
  Controller(const Controller&) = delete;
  Controller& operator=(const Controller&) = delete;
  Controller(Controller&&) = delete;
  Controller& operator=(Controller&&) = delete;
  virtual const ViewType getView(void) const = 0;
  virtual void applyControl(const ControlType) = 0;
  virtual const ControlType requestControl(void) const = 0;
  ~Controller() = default;
};

#endif
