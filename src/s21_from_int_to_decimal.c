#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 0;
  memset(dst, 0, 16);
  if (src < 0) {
    dst->bits[0] = 0 - src;
    s21_negate(*dst, dst);
  } else {
    dst->bits[0] = src;
  }
  return error;
}