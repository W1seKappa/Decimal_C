#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int res = 0;
  if (result == NULL) {
    res = 1;
  } else {
    for (int i = 0; i <= 3; i++) result->bits[i] = value.bits[i];
    if (get_sign(value.bits[3]))
      set_bit(&(result->bits[3]), 31, 0);
    else
      set_bit(&(result->bits[3]), 31, 1);
  }
  return res;
}