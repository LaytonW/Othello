// Bit operation utilities

#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <type_traits>

template <typename T>
inline T removeLastOne(const T x) {
  static_assert(std::is_integral<T>::value,
    "Bit operation on non-integral type!");
  static_assert(not std::is_signed<T>::value,
    "Bit operation on signed type!");
  auto tmp = x;
  return tmp & (tmp - 1);
}

template <typename T>
inline std::size_t countOnes(const T x) {
  static_assert(std::is_integral<T>::value,
    "Bit operation on non-integral type!");
  static_assert(not std::is_signed<T>::value,
    "Bit operation on signed type!");
  if (x == 0)
    return 0;
  auto tmp = x;
  std::size_t count = 1;
  while (tmp &= tmp - 1)
    count ++;
  return count;
}

#endif
