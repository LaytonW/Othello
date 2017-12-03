// Bit operation utilities

#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <type_traits>
#include <limits>
#include <cstdint>

template <std::size_t i>
using BitType =
  std::conditional_t<(i <= 8), uint8_t,
    std::conditional_t<(i <= 16), uint16_t,
      std::conditional_t<(i <= 32), uint32_t, uint64_t>
    >
  >;

template <typename BitRepresentationType>
constexpr void _sanityCheck(void) {
  static_assert(std::is_integral<BitRepresentationType>::value,
    "Bit operation on non-integral type!");
  static_assert(not std::is_signed<BitRepresentationType>::value,
    "Bit operation on signed type!");
}

constexpr uint64_t shiftMasks[] = {
  0x7F'7F'7F'7F'7F'7F'7F'7F,
  0x00'7F'7F'7F'7F'7F'7F'7F,
  0xFF'FF'FF'FF'FF'FF'FF'FF,
  0x00'FE'FE'FE'FE'FE'FE'FE,
  0xFE'FE'FE'FE'FE'FE'FE'FE,
  0xFE'FE'FE'FE'FE'FE'FE'00,
  0xFF'FF'FF'FF'FF'FF'FF'FF,
  0x7F'7F'7F'7F'7F'7F'7F'00,
};

constexpr uint64_t leftShift [] = {0, 0, 0, 0, 1, 9, 8, 7};
constexpr uint64_t rightShift[] = {1, 9, 8, 7, 0, 0, 0, 0};


inline uint64_t shiftBoard(const uint64_t board, std::size_t direction) {
  return (
    direction < 4 ? (board >> rightShift[direction])
                  : (board << leftShift[direction])
  ) & shiftMasks[direction];
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
inline BitStringType extractLastOne(const BitStringType x) {
  _sanityCheck<BitStringType>();
  return x ^ (removeLastOne(x));
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
struct isqrt {
  static constexpr std::size_t _value(void) {
    static_assert(isPowerOf2(x), "Size is not a power of 2!");
    auto tmp = x;
    std::size_t numOfZeros = 0;
    while (tmp != 1) {
      tmp >>= 1;
      numOfZeros ++;
    }
    return x >> (numOfZeros / 2);
  }

  static constexpr std::size_t value = _value();
};

template <typename BitBoardType>
inline auto positionToBoard(const std::size_t x, const std::size_t y) {
  _sanityCheck<BitBoardType>();
  constexpr auto boardSize = std::numeric_limits<BitBoardType>::digits;
  constexpr auto boardRow  = isqrt<boardSize>::value;
  return static_cast<BitBoardType>(1) << (boardSize - 1 - (x + boardRow * y));
}

template <typename BitBoardType>
inline auto getRow(const BitBoardType board, const std::size_t i) {
  _sanityCheck<BitBoardType>();
  constexpr auto boardSize = std::numeric_limits<BitBoardType>::digits;
  constexpr auto boardRow  = isqrt<boardSize>::value;
  using RowType = BitType<boardRow>;
  constexpr auto mask = ~static_cast<RowType>(0);
  return static_cast<RowType>(
    (board >> ((boardRow - 1 - i) * boardRow)) & mask
  );
}

template <typename BitStringType>
inline std::size_t getRowNum(const BitStringType x) {
  _sanityCheck<BitStringType>();
  if (x == 0)
    return 0;
  auto tmp = x;
  constexpr auto boardSize = std::numeric_limits<BitStringType>::digits;
  constexpr auto boardRow  = isqrt<boardSize>::value;
  std::size_t count = 0;
  while (tmp != 0) {
    tmp >>= 1;
    count ++;
  }
  return boardRow - (count - 1) / boardRow - 1;
}

template <typename BitStringType>
inline std::size_t getColNum(const BitStringType x) {
  _sanityCheck<BitStringType>();
  if (x == 0)
    return 0;
  auto tmp = x;
  constexpr auto boardSize = std::numeric_limits<BitStringType>::digits;
  constexpr auto boardCol  = isqrt<boardSize>::value;
  std::size_t count = 0;
  while (tmp != 0) {
    tmp >>= 1;
    count ++;
  }
  return boardCol - (count - 1) % boardCol - 1;
}

#endif
