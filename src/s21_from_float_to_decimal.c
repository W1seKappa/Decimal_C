#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 0;
  if (dst == NULL) return 1;
  memset(dst, 0, 16);
  union {
    float f;
    int i;
  } u;
  u.f = fabs(src);
  if (src < 0) set_bit(&(dst->bits[3]), 31, 1);
  int exp = (u.i >> 23) - 127;

  int mant = u.i << 9;
  mant >>= 9;
  s21_big_decimal val = {0};
  val.bits[0] = 0b00010000000000000000000000000000;
  val.bits[1] = 0b00111110001001010000001001100001;
  val.bits[2] = 0b00100000010011111100111001011110;
  if (exp >= 0) {
    while (exp) {
      shuffle_big_dec_left(&val);
      --exp;
    }
  } else {
    while (exp != 0) {
      shuffle_big_dec_right(&val);
      ++exp;
      if (is_big_dec_zero(val) && exp < 0) error = 1;
    }
  }
  if (!error) {
    s21_big_decimal temp = val;
    int indicator = 1 << 22;
    while (indicator) {
      shuffle_big_dec_right(&temp);
      if (indicator & mant) sum_equal_exp(val, temp, &val, 191);
      indicator >>= 1;
    }
    make_7_digits(&val);
    for (int i = 0; i < 3; ++i) {
      dst->bits[i] = val.bits[i];
    }
    dst->bits[3] = val.bits[6];
    if (src < 0) s21_negate(*dst, dst);
  }
  return error;
}

void make_7_digits(s21_big_decimal *val) {
  s21_big_decimal temp = {0};
  int exp = 28;
  while (val->bits[0] >= 10000000 || val->bits[1] != 0 || val->bits[2] != 0 ||
         val->bits[3] != 0 || val->bits[4] != 0 || val->bits[5] != 0 ||
         exp > 7) {
    temp = div10(val);
    --exp;
  }
  if (temp.bits[0] >= 5) {
    temp.bits[0] = 1;
    sum_equal_exp(*val, temp, val, 191);
  }
  while (exp < 0) {
    _x10(val);
    ++exp;
  }
  temp = div10(val);
  --exp;
  while (is_big_dec_zero(temp) && exp > 0) {
    temp = div10(val);
    --exp;
  }
  _x10(val);
  sum_equal_exp(*val, temp, val, 191);
  ++exp;
  set_exp(exp, &(val->bits[6]));
}