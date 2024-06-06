#include "s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal res;
  s21_sub(value_1, value_2, &res);
  if (get_sign(res.bits[3]) == 0 && s21_is_equal(value_1, value_2) == 0)
    return 1;
  return 0;
}