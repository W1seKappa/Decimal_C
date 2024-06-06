#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_big_decimal bigVal1 = convert_dec_to_big(value_1),
                  bigVal2 = convert_dec_to_big(value_2);
  make_equal_exp(&bigVal1, &bigVal2);
  for (int i = 0; i < 7; i++) {
    if (bigVal1.bits[i] != bigVal2.bits[i]) return 0;
  }
  return 1;
}