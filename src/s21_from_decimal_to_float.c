#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 0;
  if (dst == NULL) {
    error = 1;
  } else {
    *dst = 0.0;
    double temp = 1.0, result = 0.0;
    int sign = get_sign(src.bits[3]);
    int exp = get_exp((src.bits[3]));
    s21_big_decimal b_src = convert_dec_to_big(src);
    src.bits[3] = 0;
    while (!is_big_dec_zero(b_src)) {
      (b_src.bits[0] & 1) ? result += temp : 1;
      temp *= 2;
      shuffle_big_dec_right(&b_src);
    }
    while (exp) {
      result /= 10;
      --exp;
    }
    if (result > MAX_FLT)
      error = 1;
    else {
      *dst = result;
      if (sign) *dst *= -1;
    }
  }
  return error;
}