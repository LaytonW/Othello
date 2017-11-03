// Bit operation utilities

#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <type_traits>
#include <limits>
#include <cmath>
#include <cstdint>

template<std::size_t i>
struct BitType {
  typedef typename std::conditional<
    (i <= 8),
    uint8_t,
    typename std::conditional<
      (i <= 16),
      uint16_t,
      typename std::conditional<
        (i <= 32),
        uint32_t,
        uint64_t
      >::type
    >::type
  >::type type;
};

template <typename BitRepresentationType>
inline void _sanityCheck(void) {
  static_assert(std::is_integral<BitRepresentationType>::value,
    "Bit operation on non-integral type!");
  static_assert(not std::is_signed<BitRepresentationType>::value,
    "Bit operation on signed type!");
}

template <typename BitStringType>
inline BitStringType removeLastOne(const BitStringType x) {
  _sanityCheck<BitStringType>();
  return x & (x - 1);
}

template <typename BitStringType>
inline std::size_t countOnes(const BitStringType x) {
  _sanityCheck<BitStringType>();
  auto tmp = x;
  std::size_t count = 0;
  while (tmp != 0) {
    tmp = removeLastOne(tmp);
    count ++;
  }
  return count;
}

template <typename ActionType>
inline ActionType positionToAction(const std::size_t x, const std::size_t y) {
  _sanityCheck<ActionType>();
  return x + std::numeric_limits<ActionType>::digits * y;
}

template <typename ActionType>
inline auto actionToBoard(const ActionType action) {
  _sanityCheck<ActionType>();
  using BitBoardType = typename
    BitType<std::numeric_limits<ActionType>::digits *
            std::numeric_limits<ActionType>::digits>::type;
  return static_cast<BitBoardType>(1)
          << (std::numeric_limits<BitBoardType>::digits - 1 - action);
}

template <typename BitBoardType>
inline auto positionToBoard(const std::size_t x, const std::size_t y) {
  _sanityCheck<BitBoardType>();
  constexpr auto boardSize = std::numeric_limits<BitBoardType>::digits;
  constexpr auto boardRow  = static_cast<std::size_t>(std::sqrt(boardSize));
  return static_cast<BitBoardType>(1) << (boardSize - 1 - (x + boardRow * y));
}

template <typename BitBoardType>
inline auto getRow(const BitBoardType board, const std::size_t i) {
  _sanityCheck<BitBoardType>();
  constexpr auto boardSize = std::numeric_limits<BitBoardType>::digits;
  constexpr auto boardRow  = static_cast<std::size_t>(std::sqrt(boardSize));
  using RowType = typename BitType<boardRow>::type;
  constexpr auto mask = static_cast<RowType>(~0);
  return (board >> ((boardRow - 1 - i) * boardRow)) & mask;
}

#endif
