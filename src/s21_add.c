

#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;
  s21_big_decimal bv1 = convert_dec_to_big(value_1),
                  bv2 = convert_dec_to_big(value_2);
  s21_big_decimal res;
  memset(&res, 0, 28);
  make_equal_exp(&bv1, &bv2);
  if (!get_sign(value_1.bits[3]) && !get_sign(value_2.bits[3])) {
    sum_equal_exp(bv1, bv2, &res, 191);
    err = convert_big_to_dec(res, result, get_exp(bv1.bits[6]), 1);
  } else if (get_sign(value_1.bits[3]) && get_sign(value_2.bits[3])) {
    s21_negate_big(bv1, &bv1);
    s21_negate_big(bv2, &bv2);
    sum_equal_exp(bv1, bv2, &res, 191);
    err = convert_big_to_dec(res, result, get_exp(bv1.bits[6]), 1);
    err == 1 ? err = 2 : 1;
    s21_negate(*result, result);
  } else if (!get_sign(value_1.bits[3]) && get_sign(value_2.bits[3])) {
    s21_negate(value_2, &value_2);
    err = s21_sub(value_1, value_2, result);
  } else if (get_sign(value_1.bits[3]) && !get_sign(value_2.bits[3])) {
    s21_negate(value_1, &value_1);
    err = s21_sub(value_2, value_1, result);
  }
  return err;
}