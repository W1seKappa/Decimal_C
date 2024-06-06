#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  int exp = get_exp(src.bits[3]);
  int sign = get_sign(src.bits[3]) ? -1 : 1;
  if (exp == 0) {
    if (src.bits[1] == 0 && src.bits[2] == 0 &&
        (src.bits[0] <= MAX_INT || sign == -1)) {
      *dst = src.bits[0] * sign;
    } else
      error = 1;
  } else {
    s21_big_decimal temp = convert_dec_to_big(src);
    while (exp > 0) {
      div10(&temp);
      --exp;
    }
    if (is_big_dec_zero(temp)) {
      *dst = 0;
    } else {
      set_exp(exp, &(temp.bits[6]));
      convert_big_to_dec(temp, &src, exp, 0);
      error = s21_from_decimal_to_int(src, dst);
    }
  }
  return error;
}