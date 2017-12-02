#ifndef __VIEW_HPP__
#define __VIEW_HPP__

template <typename GameType, typename ViewType>
class View {
public:
  View() = default;
  View(const View&) = delete;
  View& operator=(const View&) = delete;
  View(View&&) = delete;
  View& operator=(View&&) = delete;
  virtual const ViewType getView(void) const = 0;
  virtual void updateGame(const GameType&) = 0;
  ~View() = default;
};

#endif
