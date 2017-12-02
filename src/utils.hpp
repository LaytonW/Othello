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
inline BitStringType extractFirstOne(const BitStringType x) {
  _sanityCheck<BitStringType>();
  if (x == 0)
    return 0;
  auto tmp = x;
  while (not isPowerOf2(tmp))
    tmp = removeLastOne(tmp);
  return tmp;
}

template <typename BitStringType>
inline BitStringType fillTail(const BitStringType x) {
  _sanityCheck<BitStringType>();
  return x | (x - 1);
}

template <typename BitStringType>
inline BitStringType fillBetween(const BitStringType x) {
  _sanityCheck<BitStringType>();
  if (isPowerOf2(x))
    return static_cast<BitStringType>(0);
  return fillTail(static_cast<BitStringType>(extractFirstOne(x) >> 1))
         ^ fillTail(static_cast<BitStringType>(extractLastOne(x)));
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

template <typename BitStringType>
inline BitStringType rotateL(const BitStringType x, std::size_t n) {
  _sanityCheck<BitStringType>();
  n %= std::numeric_limits<BitStringType>::digits;
  auto highBits = x << n;
  auto lowBits  = x >> (std::numeric_limits<BitStringType>::digits - n);
  return highBits | lowBits;
}

template <typename BitStringType>
inline BitStringType rotateR(const BitStringType x, std::size_t n) {
  _sanityCheck<BitStringType>();
  n %= std::numeric_limits<BitStringType>::digits;
  auto lowBits  = x >> n;
  auto highBits = x << (std::numeric_limits<BitStringType>::digits - n);
  return highBits | lowBits;
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

template <std::size_t x>
struct pow2 {
  static constexpr std::size_t _value(void) {
    static_assert(isPowerOf2(x), "Size is not a power of 2!");
    auto tmp = x;
    std::size_t numOfZeros = 0;
    while (tmp != 1) {
      tmp >>= 1;
      numOfZeros ++;
    }
    return x << numOfZeros;
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

template <typename BitBoardType>
inline auto getColumn(const BitBoardType board, const std::size_t i,
                      const bool reverse=false) {
  _sanityCheck<BitBoardType>();
  constexpr auto boardSize = std::numeric_limits<BitBoardType>::digits;
  constexpr auto boardCol  = isqrt<boardSize>::value;
  using ColType = BitType<boardCol>;
  ColType col = 0;
  for (std::size_t j = 0; j < boardCol; j++)
    col |= (
      (board >> ((reverse ? boardCol-1-j : j) * boardCol + boardCol - 1 - i))
      & static_cast<ColType>(1)
    ) << j;
  return static_cast<ColType>(col);
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

template <typename BitBoardType>
inline BitBoardType getTranspose(const BitBoardType board) {
  _sanityCheck<BitBoardType>();
  constexpr auto boardSize = std::numeric_limits<BitBoardType>::digits;
  constexpr auto boardRow  = isqrt<boardSize>::value;
  BitBoardType boardT = 0;
  for (std::size_t i = 0; i < boardRow; i++) {
    boardT <<= boardRow;
    boardT |= static_cast<BitBoardType>(getColumn(board, i));
  }
  return boardT;
}

template <typename BitBoardType>
inline BitBoardType antiClockRotate45(const BitBoardType board) {
  _sanityCheck<BitBoardType>();
  constexpr auto boardSize = std::numeric_limits<BitBoardType>::digits;
  constexpr auto boardRow  = isqrt<boardSize>::value;
  BitBoardType boardACR45T = 0;
  for (std::size_t i = 0; i < boardRow; i++) {
    boardACR45T <<= boardRow;
    boardACR45T |= static_cast<BitBoardType>(rotateL(getColumn(board, i), i));
  }
  return getTranspose(boardACR45T);
}

template <typename BitBoardType>
inline BitBoardType clockRotate45(const BitBoardType board) {
  _sanityCheck<BitBoardType>();
  constexpr auto boardSize = std::numeric_limits<BitBoardType>::digits;
  constexpr auto boardRow  = isqrt<boardSize>::value;
  BitBoardType boardCR45T = 0;
  for (std::size_t i = 0; i < boardRow; i++) {
    boardCR45T <<= boardRow;
    boardCR45T |= static_cast<BitBoardType>(rotateR(getColumn(board, i), i));
  }
  return getTranspose(boardCR45T);
}

template <typename BitBoardType>
inline BitBoardType antiClockRotate90(const BitBoardType board) {
  _sanityCheck<BitBoardType>();
  constexpr auto boardSize = std::numeric_limits<BitBoardType>::digits;
  constexpr auto boardRow  = isqrt<boardSize>::value;
  BitBoardType boardACR90 = 0;
  for (std::size_t i = 0; i < boardRow; i++) {
    boardACR90 <<= boardRow;
    boardACR90 |= static_cast<BitBoardType>(getColumn(board, boardRow - 1 - i));
  }
  return boardACR90;
}

template <typename BitBoardType>
inline BitBoardType clockRotate90(const BitBoardType board) {
  _sanityCheck<BitBoardType>();
  constexpr auto boardSize = std::numeric_limits<BitBoardType>::digits;
  constexpr auto boardRow  = isqrt<boardSize>::value;
  BitBoardType boardCR90 = 0;
  for (std::size_t i = 0; i < boardRow; i++) {
    boardCR90 <<= boardRow;
    boardCR90 |= static_cast<BitBoardType>(getColumn(board, i, true));
  }
  return boardCR90;
}

template <typename BitBoardType>
inline BitBoardType rotate180(const BitBoardType board) {
  _sanityCheck<BitBoardType>();
  return clockRotate90(clockRotate90(board));
}

template <typename BitBoardType, typename RowType>
inline auto setRow(const BitBoardType board,
                   const std::size_t rowNum,
                   const RowType row) {
  _sanityCheck<BitBoardType>();
  constexpr auto boardSize = std::numeric_limits<BitBoardType>::digits;
  constexpr auto rowSize  = isqrt<boardSize>::value;
  static_assert(std::numeric_limits<RowType>::digits == rowSize,
    "BitBoardType and RowType mismatch!");
  const auto mask = static_cast<BitBoardType>(static_cast<RowType>(~0));
  BitBoardType res = board & ~(mask << ((rowSize - rowNum - 1) * rowSize));
  res |= static_cast<BitBoardType>(row) << ((rowSize - rowNum - 1) * rowSize);
  return res;
}

template <typename BitBoardType, typename ColType>
inline auto setCol(const BitBoardType board,
                   const std::size_t colNum,
                   const ColType col) {
  _sanityCheck<BitBoardType>();
  constexpr auto boardSize = std::numeric_limits<BitBoardType>::digits;
  constexpr auto colSize  = isqrt<boardSize>::value;
  static_assert(std::numeric_limits<ColType>::digits == colSize,
    "BitBoardType and ColType mismatch!");
  BitBoardType res = setRow(getTranspose(board), colNum, col);
  return getTranspose(res);
}

template <typename BitBoardType, typename DiagType>
inline auto setDiag(const BitBoardType board,
                    const std::size_t diagNum,
                    const DiagType diag) {
  _sanityCheck<BitBoardType>();
  constexpr auto boardSize = std::numeric_limits<BitBoardType>::digits;
  constexpr auto diagSize  = isqrt<boardSize>::value;
  static_assert(std::numeric_limits<DiagType>::digits == diagSize,
    "BitBoardType and DiagType mismatch!");
  BitBoardType res = setRow(antiClockRotate45(board), diagNum, diag);
  return clockRotate45(res);
}

template <typename BitBoardType, typename DiagType>
inline auto setAntiDiag(const BitBoardType board,
                        const std::size_t antiDiagNum,
                        const DiagType antiDiag) {
  _sanityCheck<BitBoardType>();
  constexpr auto boardSize = std::numeric_limits<BitBoardType>::digits;
  constexpr auto diagSize  = isqrt<boardSize>::value;
  static_assert(std::numeric_limits<DiagType>::digits == diagSize,
    "BitBoardType and DiagType mismatch!");
  BitBoardType res = setRow(clockRotate45(board), antiDiagNum, antiDiag);
  return antiClockRotate45(res);
}

#endif
