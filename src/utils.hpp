// Bit operation utilities

#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <type_traits>
#include <limits>
#include <cstdint>

template<std::size_t i>
struct _BitType {
  using type = std::conditional_t<(i <= 8), uint8_t,
    typename std::conditional_t<(i <= 16), uint16_t,
      typename std::conditional_t<(i <= 32), uint32_t, uint64_t>
    >
  >;
};

template <std::size_t i>
using BitType = typename _BitType<i>::type;

template <typename BitRepresentationType>
constexpr void _sanityCheck(void) {
  static_assert(std::is_integral<BitRepresentationType>::value,
    "Bit operation on non-integral type!");
  static_assert(not std::is_signed<BitRepresentationType>::value,
    "Bit operation on signed type!");
}

template <typename BitStringType>
constexpr bool isPowerOf2(const BitStringType x) {
  _sanityCheck<BitStringType>();
  return x && ((x & (x - 1)) == 0);
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

template <std::size_t x>
constexpr std::size_t isqrt(void) {
  static_assert(isPowerOf2(x), "Size is not a power of 2!");
  auto tmp = x;
  std::size_t numOfZeros = 0;
  while (tmp != 1) {
    tmp >>= 1;
    numOfZeros ++;
  }
  return x >> (numOfZeros / 2);
}

template <std::size_t x>
constexpr std::size_t pow2(void) {
  static_assert(isPowerOf2(x), "Size is not a power of 2!");
  auto tmp = x;
  std::size_t numOfZeros = 0;
  while (tmp != 1) {
    tmp >>= 1;
    numOfZeros ++;
  }
  return x << numOfZeros;
}

template <typename ActionType>
inline ActionType positionToAction(const std::size_t x, const std::size_t y) {
  _sanityCheck<ActionType>();
  return x + std::numeric_limits<ActionType>::digits * y;
}

template <typename ActionType>
inline auto actionToBoard(const ActionType action) {
  _sanityCheck<ActionType>();
  using BitBoardType = BitType<pow2<std::numeric_limits<ActionType>::digits>()>;
  return static_cast<BitBoardType>(1)
          << (std::numeric_limits<BitBoardType>::digits - 1 - action);
}

template <typename BitBoardType>
inline auto positionToBoard(const std::size_t x, const std::size_t y) {
  _sanityCheck<BitBoardType>();
  constexpr auto boardSize = std::numeric_limits<BitBoardType>::digits;
  constexpr auto boardRow  = isqrt<boardSize>();
  return static_cast<BitBoardType>(1) << (boardSize - 1 - (x + boardRow * y));
}

template <typename BitBoardType>
inline auto getRow(const BitBoardType board, const std::size_t i) {
  _sanityCheck<BitBoardType>();
  constexpr auto boardSize = std::numeric_limits<BitBoardType>::digits;
  constexpr auto boardRow  = isqrt<boardSize>();
  using RowType = BitType<boardRow>;
  constexpr auto mask = static_cast<RowType>(~0);
  return static_cast<RowType>(
    (board >> ((boardRow - 1 - i) * boardRow)) & mask
  );
}

#endif
