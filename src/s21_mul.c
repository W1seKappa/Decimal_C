
#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;
  s21_big_decimal bv1 = convert_dec_to_big(value_1),
                  bv2 = convert_dec_to_big(value_2);
  s21_big_decimal res;
  memset(&res, 0, 28);
  int exp = get_exp(value_1.bits[3]) + get_exp(value_2.bits[3]);
  int sign = get_sign(value_1.bits[3]) ^ get_sign(value_2.bits[3]);
  while (!is_big_dec_zero(bv2)) {
    if (bv2.bits[0] & 1) sum_equal_exp(res, bv1, &res, 191);
    shuffle_big_dec_left(&bv1);
    shuffle_big_dec_right(&bv2);
  }
  set_bit(&res.bits[6], 31, sign);
  err = convert_big_to_dec(res, result, exp, 1);
  return err;
}