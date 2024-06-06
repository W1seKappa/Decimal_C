#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal res;
  s21_sub(value_1, value_2, &res);
  if (get_sign(res.bits[3]) == 1) return 1;
  return 0;
}