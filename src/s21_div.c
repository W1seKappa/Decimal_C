#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;
  memset(result, 0, 16);
  if (is_dec_zero(value_2)) {
    err = 3;
  } else if (is_dec_zero(value_1)) {
    for (int i = 0; i < 3; ++i) result->bits[i] = 0;
    if (get_sign(value_2.bits[3])) s21_negate(*result, result);
  } else {
    int exp = get_exp(value_1.bits[3]) - get_exp(value_2.bits[3]);
    s21_big_decimal temp1, temp2, temp_res, frac_part;
    memset(&temp_res, 0, 28);
    memset(&temp1, 0, 28);
    memset(&temp2, 0, 28);
    memset(&frac_part, 0, 28);
    for (int i = 0; i < 3; ++i) {
      temp1.bits[i] = value_1.bits[i];
      temp2.bits[i] = value_2.bits[i];
    }
    int overflow_flag = 0, flag_finish = 0;
    while (exp < 96 && !overflow_flag && !flag_finish) {
      memset(&frac_part, 0, 28);
      if (s21_is_less_or_equal_big(temp2, temp1)) {
        temp1 = s21_div_supp(temp1, temp2, &frac_part);
        is_big_dec_zero(temp1) ? flag_finish = 1 : 1;
        sum_equal_exp(temp_res, frac_part, &temp_res, 100);
      } else {
        if (temp_res.bits[3] == 0) {
          _x10(&temp_res);
          ++exp;
          _x10(&temp1);
          temp1 = s21_div_supp(temp1, temp2, &frac_part);
          is_big_dec_zero(temp1) ? flag_finish = 1 : 1;
          sum_equal_exp(temp_res, frac_part, &temp_res, 100);
        } else {
          overflow_flag = 1;
        }
      }
    }
    if ((!get_sign(value_1.bits[3]) && get_sign(value_2.bits[3])) ||
        (get_sign(value_1.bits[3]) && !get_sign(value_2.bits[3])))
      s21_negate_big(temp_res, &temp_res);
    err = convert_big_to_dec(temp_res, result, exp, 1);
  }
  return err;
}

s21_big_decimal s21_div_supp(s21_big_decimal value_1, s21_big_decimal value_2,
                             s21_big_decimal *result) {
  memset(result, 0, 28);
  set_exp(0, &(value_1.bits[6]));
  set_exp(0, &(value_2.bits[6]));
  int lb1 = get_last_bit(value_1), lb2 = get_last_bit(value_2);
  int diff = lb1 - lb2;
  for (int i = 0; i < diff; ++i) shuffle_big_dec_left(&value_2);
  while (diff >= 0) {
    if (s21_is_less_or_equal_big(value_2, value_1)) {
      minus_equal_exp(value_1, value_2, &value_1);
      int bit = diff % 32;
      bit == 0 ? bit = diff : 1;
      set_bit(&(result->bits[diff / 32]), bit, 1);
      shuffle_big_dec_right(&value_2);
    } else {
      int bit = diff % 32;
      diff < 32 ? bit = diff : 1;
      set_bit(&(result->bits[diff / 32]), bit, 0);
      shuffle_big_dec_right(&value_2);
    }
    --diff;
  }
  return value_1;
}

s21_big_decimal div10(s21_big_decimal *value_1) {
  s21_big_decimal value_2;
  memset(&value_2, 0, 28);
  value_2.bits[0] = 10;
  s21_big_decimal result;
  memset(&result, 0, 28);
  result = s21_div_supp(*value_1, value_2, value_1);
  return result;
}