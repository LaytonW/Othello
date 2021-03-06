#include <iostream>
#include <type_traits>
#include <cstdint>
#include <cassert>

#include "utils.hpp"

#ifdef NDEBUG
#undef NDEBUG
#endif

#ifndef DEBUG
#define DEBUG
#endif

int main() {
  // Test BitType
  static_assert(std::is_same<BitType<0>, uint8_t>::value,
                "BitType<0> should be uint8_t!");
  static_assert(std::is_same<BitType<1>, uint8_t>::value,
                "BitType<1> should be uint8_t!");
  static_assert(std::is_same<BitType<7>, uint8_t>::value,
                "BitType<7> should be uint8_t!");
  static_assert(std::is_same<BitType<8>, uint8_t>::value,
                "BitType<8> should be uint8_t!");
  static_assert(std::is_same<BitType<9>, uint16_t>::value,
                "BitType<9> should be uint16_t!");
  static_assert(std::is_same<BitType<10>, uint16_t>::value,
                "BitType<10> should be uint16_t!");
  static_assert(std::is_same<BitType<15>, uint16_t>::value,
                "BitType<15> should be uint16_t!");
  static_assert(std::is_same<BitType<16>, uint16_t>::value,
                "BitType<16> should be uint16_t!");
  static_assert(std::is_same<BitType<17>, uint32_t>::value,
                "BitType<17> should be uint32_t!");
  static_assert(std::is_same<BitType<18>, uint32_t>::value,
                "BitType<18> should be uint32_t!");
  static_assert(std::is_same<BitType<31>, uint32_t>::value,
                "BitType<31> should be uint32_t!");
  static_assert(std::is_same<BitType<32>, uint32_t>::value,
                "BitType<32> should be uint32_t!");
  static_assert(std::is_same<BitType<33>, uint64_t>::value,
                "BitType<33> should be uint64_t!");
  static_assert(std::is_same<BitType<34>, uint64_t>::value,
                "BitType<34> should be uint64_t!");
  static_assert(std::is_same<BitType<63>, uint64_t>::value,
                "BitType<63> should be uint64_t!");
  static_assert(std::is_same<BitType<64>, uint64_t>::value,
                "BitType<64> should be uint64_t!");

  // Test isPowerOf2
  static_assert(not isPowerOf2(0ull), "0 is not power of 2!");
  static_assert(isPowerOf2(1ull), "1 is power of 2!");
  static_assert(isPowerOf2(2ull), "2 is power of 2!");
  static_assert(not isPowerOf2(3ull), "3 is not power of 2!");
  static_assert(isPowerOf2(4ull), "4 is power of 2!");
  static_assert(isPowerOf2(64ull), "64 is power of 2!");

  // Test removeLastOne
  assert(removeLastOne(0b00ull) == 0b00ull);
  assert(removeLastOne(0b01ull) == 0b00ull);
  assert(removeLastOne(0b10ull) == 0b00ull);
  assert(removeLastOne(0b11ull) == 0b10ull);
  assert(removeLastOne(0b0100ull) == 0b00ull);
  assert(removeLastOne(0b0101ull) == 0b0100ull);
  assert(removeLastOne(0b0111ull) == 0b0110ull);
  assert(removeLastOne(0b0100'0000ull) == 0b00ull);

  // Test extractLastOne
  assert(extractLastOne(0b00ull) == 0b00ull);
  assert(extractLastOne(0b01ull) == 0b01ull);
  assert(extractLastOne(0b10ull) == 0b10ull);
  assert(extractLastOne(0b11ull) == 0b01ull);
  assert(extractLastOne(0b0100ull) == 0b0100ull);
  assert(extractLastOne(0b0110ull) == 0b0010ull);
  assert(extractLastOne(0b0111ull) == 0b0001ull);
  assert(extractLastOne(0b0100'0000ull) == 0b0100'0000ull);

  // Test countOnes
  assert(countOnes(0b00ull) == 0);
  assert(countOnes(0b01ull) == 1);
  assert(countOnes(0b10ull) == 1);
  assert(countOnes(0b11ull) == 2);
  assert(countOnes(0b100ull) == 1);
  assert(countOnes(0b101ull) == 2);
  assert(countOnes(0b111ull) == 3);
  assert(countOnes(0b0011'1111ull) == 6);
  assert(countOnes(0b0101'0101ull) == 4);

  // Test isqrt
  static_assert(isqrt<1>::value == 1, "isqrt<1>::value should be 1!");
  static_assert(isqrt<4>::value == 2, "isqrt<4>::value should be 2!");
  static_assert(isqrt<16>::value == 4, "isqrt<16>::value should be 4!");
  static_assert(isqrt<64>::value == 8, "isqrt<64>::value should be 8!");
  static_assert(isqrt<256>::value == 16, "isqrt<256>::value should be 16!");

  // Test positionToBoard
  static_assert(std::is_same<decltype(positionToBoard<uint64_t>(0, 0)),
                             uint64_t>::value,
                "positionToBoard<uint64_t> should result in uint64_t board!");
  assert(positionToBoard<uint64_t>(0, 0) == static_cast<uint64_t>(1) << 63);
  assert(positionToBoard<uint64_t>(1, 0) == static_cast<uint64_t>(1) << 62);
  assert(positionToBoard<uint64_t>(7, 0) == static_cast<uint64_t>(1) << 56);
  assert(positionToBoard<uint64_t>(0, 7) == static_cast<uint64_t>(1) << 7);
  assert(positionToBoard<uint64_t>(4, 4) == static_cast<uint64_t>(1) << 27);

  // Test getRow
  static_assert(std::is_same<decltype(getRow(static_cast<uint64_t>(0), 0)),
                             uint8_t>::value,
                "uint64_t board should have uint8_t rows!");
  assert(getRow(positionToBoard<uint64_t>(0, 0), 0) ==
                static_cast<uint8_t>(1) << 7);
  assert(getRow(positionToBoard<uint64_t>(0, 0), 1) ==
                static_cast<uint8_t>(0));
  assert(getRow(positionToBoard<uint64_t>(3, 3), 0) ==
                static_cast<uint8_t>(0));
  assert(getRow(positionToBoard<uint64_t>(3, 3), 3) ==
                static_cast<uint8_t>(1) << 4);

  // Test getRowNum
  assert(getRowNum(positionToBoard<uint64_t>(0, 0)) == 0);
  assert(getRowNum(positionToBoard<uint64_t>(0, 1)) == 1);
  assert(getRowNum(positionToBoard<uint64_t>(1, 1)) == 1);
  assert(getRowNum(positionToBoard<uint64_t>(4, 4)) == 4);
  assert(getRowNum(positionToBoard<uint64_t>(7, 2)) == 2);
  assert(getRowNum(positionToBoard<uint64_t>(7, 0)) == 0);
  assert(getRowNum(positionToBoard<uint64_t>(5, 7)) == 7);

  // Test getColNum
  assert(getColNum(positionToBoard<uint64_t>(0, 0)) == 0);
  assert(getColNum(positionToBoard<uint64_t>(1, 0)) == 1);
  assert(getColNum(positionToBoard<uint64_t>(1, 1)) == 1);
  assert(getColNum(positionToBoard<uint64_t>(4, 4)) == 4);
  assert(getColNum(positionToBoard<uint64_t>(7, 2)) == 7);
  assert(getColNum(positionToBoard<uint64_t>(7, 0)) == 7);

  std::cout << "All tests passed for utils!" << std::endl;
  return 0;
}
