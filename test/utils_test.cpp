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

  // Test extractFirstOne
  assert(extractFirstOne(0b00ull) == 0b00ull);
  assert(extractFirstOne(0b01ull) == 0b01ull);
  assert(extractFirstOne(0b10ull) == 0b10ull);
  assert(extractFirstOne(0b11ull) == 0b10ull);
  assert(extractFirstOne(0b0100ull) == 0b0100ull);
  assert(extractFirstOne(0b0110ull) == 0b0100ull);
  assert(extractFirstOne(0b0111ull) == 0b0100ull);
  assert(extractFirstOne(0b0101'0101ull) == 0b0100'0000ull);

  // Test fillTail
  assert(fillTail(0b01ull) == 0b01ull);
  assert(fillTail(0b10ull) == 0b11ull);
  assert(fillTail(0b11ull) == 0b11ull);
  assert(fillTail(0b0100ull) == 0b0111ull);
  assert(fillTail(0b0110ull) == 0b0111ull);
  assert(fillTail(0b0111ull) == 0b0111ull);
  assert(fillTail(0b0100'0000ull) == 0b0111'1111ull);

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

  // Test rotateL
  assert(rotateL(0b00ull, 1) == 0b00ull);
  assert(rotateL(0b01ull, 1) == 0b10ull);
  assert(rotateL(0b01ull, 2) == 0b0100ull);
  assert(rotateL(0b11ull, 1) == 0b0110ull);
  assert(rotateL(0b0100ull, 1) == 0b1000ull);
  assert(rotateL(static_cast<uint8_t>(0b0000'0100), 6) == 0b0000'0001);
  assert(rotateL(static_cast<uint8_t>(0b0000'0100), 8) == 0b0000'0100);
  assert(rotateL(static_cast<uint8_t>(0b0000'0100), 16) == 0b0000'0100);

  // Test rotateR
  assert(rotateR(0b00ull, 1) == 0b00ull);
  assert(rotateR(0b10ull, 1) == 0b01ull);
  assert(rotateR(0b0100ull, 2) == 0b0001ull);
  assert(rotateR(static_cast<uint8_t>(0b0000'0100), 3) == 0b1000'0000);
  assert(rotateR(static_cast<uint8_t>(0b0000'0100), 8) == 0b0000'0100);
  assert(rotateR(static_cast<uint8_t>(0b0000'0100), 16) == 0b0000'0100);

  // Test isqrt
  static_assert(isqrt<1>::value == 1, "isqrt<1>::value should be 1!");
  static_assert(isqrt<4>::value == 2, "isqrt<4>::value should be 2!");
  static_assert(isqrt<16>::value == 4, "isqrt<16>::value should be 4!");
  static_assert(isqrt<64>::value == 8, "isqrt<64>::value should be 8!");
  static_assert(isqrt<256>::value == 16, "isqrt<256>::value should be 16!");

  // Test pow2
  static_assert(pow2<1>::value == 1, "pow2<1>::value should be 1!");
  static_assert(pow2<2>::value == 4, "pow2<2>::value should be 4!");
  static_assert(pow2<4>::value == 16, "pow2<4>::value should be 16!");
  static_assert(pow2<8>::value == 64, "pow2<8>::value should be 64!");
  static_assert(pow2<16>::value == 256, "pow2<16>::value should be 256!");

  // Test positionToAction
  assert(positionToAction<uint8_t>(0, 0) == 0);
  assert(positionToAction<uint8_t>(1, 0) == 1);
  assert(positionToAction<uint8_t>(7, 0) == 7);
  assert(positionToAction<uint8_t>(0, 1) == 8);
  assert(positionToAction<uint8_t>(0, 7) == 56);
  assert(positionToAction<uint8_t>(3, 3) == 27);
  assert(positionToAction<uint8_t>(4, 3) == 28);
  assert(positionToAction<uint8_t>(3, 4) == 35);
  assert(positionToAction<uint8_t>(4, 4) == 36);

  // Test actionToBoard
  static_assert(std::is_same<decltype(actionToBoard(static_cast<uint8_t>(0))),
                             uint64_t>::value,
                "uint8_t action should result in uint64_t board!");
  assert(actionToBoard(static_cast<uint8_t>(0)) ==
                       static_cast<uint64_t>(1) << 63);
  assert(actionToBoard(static_cast<uint8_t>(1)) ==
                       static_cast<uint64_t>(1) << 62);
  assert(actionToBoard(static_cast<uint8_t>(7)) ==
                       static_cast<uint64_t>(1) << 56);
  assert(actionToBoard(static_cast<uint8_t>(56)) ==
                       static_cast<uint64_t>(1) << 7);
  assert(actionToBoard(static_cast<uint8_t>(36)) ==
                       static_cast<uint64_t>(1) << 27);

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

  // Test getColumn
  static_assert(std::is_same<decltype(getColumn(static_cast<uint64_t>(0), 0)),
                             uint8_t>::value,
                "uint64_t board should have uint8_t columns!");
  assert(getColumn(positionToBoard<uint64_t>(0, 0), 0) ==
                   static_cast<uint8_t>(1) << 7);
  assert(getColumn(positionToBoard<uint64_t>(0, 0), 1) ==
                   static_cast<uint8_t>(0));
  assert(getColumn(positionToBoard<uint64_t>(3, 3), 0) ==
                   static_cast<uint8_t>(0));
  assert(getColumn(positionToBoard<uint64_t>(3, 3), 3) ==
                   static_cast<uint8_t>(1) << 4);
  assert(getColumn(positionToBoard<uint64_t>(3, 4), 3) ==
                   static_cast<uint8_t>(1) << 3);
  assert(getColumn(positionToBoard<uint64_t>(3, 4), 3, true) ==
                   static_cast<uint8_t>(1) << 4);

  // Test getTranspose
  assert(getTranspose(positionToBoard<uint64_t>(0, 0)) ==
                      positionToBoard<uint64_t>(0, 0));
  assert(getTranspose(positionToBoard<uint64_t>(0, 1)) ==
                      positionToBoard<uint64_t>(1, 0));
  assert(getTranspose(positionToBoard<uint64_t>(0, 7)) ==
                      positionToBoard<uint64_t>(7, 0));
  assert(getTranspose(positionToBoard<uint64_t>(2, 6)) ==
                      positionToBoard<uint64_t>(6, 2));
  assert(getTranspose(positionToBoard<uint64_t>(3, 5)
                      | positionToBoard<uint64_t>(6, 1)) ==
                      (positionToBoard<uint64_t>(5, 3)
                      | positionToBoard<uint64_t>(1, 6)));

  // Test antiClockRotate45
  assert(antiClockRotate45(positionToBoard<uint64_t>(0, 0)) ==
                           positionToBoard<uint64_t>(0, 0));
  assert(antiClockRotate45(positionToBoard<uint64_t>(0, 7)) ==
                           positionToBoard<uint64_t>(0, 7));
  assert(antiClockRotate45(positionToBoard<uint64_t>(2, 6)) ==
                           positionToBoard<uint64_t>(2, 4));
  assert(antiClockRotate45(positionToBoard<uint64_t>(3, 5)
                           | positionToBoard<uint64_t>(6, 1)) ==
                           (positionToBoard<uint64_t>(3, 2)
                           | positionToBoard<uint64_t>(6, 3)));

  // Test clockRotate45
  assert(clockRotate45(positionToBoard<uint64_t>(0, 0)) ==
                       positionToBoard<uint64_t>(0, 0));
  assert(clockRotate45(positionToBoard<uint64_t>(0, 7)) ==
                       positionToBoard<uint64_t>(0, 7));
  assert(clockRotate45(positionToBoard<uint64_t>(2, 6)) ==
                       positionToBoard<uint64_t>(2, 0));
  assert(clockRotate45(positionToBoard<uint64_t>(3, 5)
                       | positionToBoard<uint64_t>(6, 1)) ==
                       (positionToBoard<uint64_t>(3, 0)
                       | positionToBoard<uint64_t>(6, 7)));

  // Test antiClockRotate90
  assert(antiClockRotate90(positionToBoard<uint64_t>(0, 0)) ==
                           positionToBoard<uint64_t>(0, 7));
  assert(antiClockRotate90(positionToBoard<uint64_t>(0, 7)) ==
                           positionToBoard<uint64_t>(7, 7));
  assert(antiClockRotate90(positionToBoard<uint64_t>(2, 6)) ==
                           positionToBoard<uint64_t>(6, 5));
  assert(antiClockRotate90(positionToBoard<uint64_t>(3, 5)
                           | positionToBoard<uint64_t>(6, 1)) ==
                           (positionToBoard<uint64_t>(5, 4)
                           | positionToBoard<uint64_t>(1, 1)));

  // Test clockRotate90
  assert(clockRotate90(positionToBoard<uint64_t>(0, 0)) ==
                       positionToBoard<uint64_t>(7, 0));
  assert(clockRotate90(positionToBoard<uint64_t>(0, 7)) ==
                       positionToBoard<uint64_t>(0, 0));
  assert(clockRotate90(positionToBoard<uint64_t>(2, 6)) ==
                       positionToBoard<uint64_t>(1, 2));
  assert(clockRotate90(positionToBoard<uint64_t>(3, 5)
                       | positionToBoard<uint64_t>(6, 1)) ==
                       (positionToBoard<uint64_t>(2, 3)
                       | positionToBoard<uint64_t>(6, 6)));

  // Test rotate180
  assert(rotate180(positionToBoard<uint64_t>(0, 0)) ==
                   positionToBoard<uint64_t>(7, 7));
  assert(rotate180(positionToBoard<uint64_t>(0, 7)) ==
                   positionToBoard<uint64_t>(7, 0));
  assert(rotate180(positionToBoard<uint64_t>(2, 6)) ==
                   positionToBoard<uint64_t>(5, 1));
  assert(rotate180(positionToBoard<uint64_t>(3, 5)
                   | positionToBoard<uint64_t>(6, 1)) ==
                   (positionToBoard<uint64_t>(4, 2)
                   | positionToBoard<uint64_t>(1, 6)));

  assert(
    antiClockRotate90(
      clockRotate90(
        positionToBoard<uint64_t>(3, 5) | positionToBoard<uint64_t>(6, 1)
      )
    ) == (positionToBoard<uint64_t>(3, 5) | positionToBoard<uint64_t>(6, 1))
  );

  assert(
    rotate180(
      rotate180(
        positionToBoard<uint64_t>(3, 5)
        | positionToBoard<uint64_t>(6, 1)
      )
    ) == (positionToBoard<uint64_t>(3, 5) | positionToBoard<uint64_t>(6, 1))
  );

  std::cout << "All tests passed for utils!" << std::endl;
  return 0;
}
