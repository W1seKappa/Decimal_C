#include "s21_decimal.h"

s21_big_decimal convert_dec_to_big(s21_decimal val) {
  s21_big_decimal res;
  memset(&res, 0, 28);
  for (int i = 0; i < 3; ++i) {
    res.bits[i] = val.bits[i];
  }
  res.bits[6] = val.bits[3];
  return res;
}

uint32_t get_exp(uint32_t val) {
  val <<= 1;
  val >>= 17;
  return val;
}

int s21_get_bit_dec(s21_decimal data, int index) {
  return (data.bits[index / 32] >> (index % 32)) & 1;
}

int s21_get_sign_dec(s21_decimal data) { return data.bits[3] >> 31 & 1U; }

int s21_get_exp_dec(s21_decimal data) {
  int result = data.bits[3];
  return result >> 16 & 255;
}

int get_sign(uint32_t val) { return (val >> 31) & 1; }

void set_bit(uint32_t *dst, int pos, int bit) {
  if (bit) {
    *dst |= (1 << pos);
  } else {
    *dst &= ~(1 << pos);
  }
}
void set_exp(uint32_t val, uint32_t *data) {
  val <<= 16;
  if (get_sign(*data)) {
    *data = val;
    set_bit(data, 31, 1);
  } else {
    *data = val;
  }
}

int get_last_bit(s21_big_decimal val) {
  int result = 0;
  for (int i = 0; i < 192; ++i) {
    if (val.bits[i / 32] & 1) result = i;
    val.bits[i / 32] >>= 1;
  }
  return result;
}

int is_dec_zero(s21_decimal data) {
  int res = 0;
  if (data.bits[0] == 0 && data.bits[1] == 0 && data.bits[2] == 0) res = 1;
  return res;
}
int is_big_dec_zero(s21_big_decimal data) {
  int res = 1;
  for (int i = 0; i < 6; ++i) data.bits[i] != 0 ? res = 0 : 1;
  return res;
}

s21_big_decimal abs_big_decimal(s21_big_decimal val) {
  set_bit(&(val.bits[6]), 31, 0);
  return val;
}
int shuffle_big_dec_left(s21_big_decimal *dst) {
  int error = 1;
  int flag_p = 0;
  for (int i = 0; i < 6; i++) {
    int temp = 0;
    flag_p == 1 ? temp = 1 : 1;
    if (dst->bits[i] & (1 << 31)) {
      flag_p = 1;

    } else {
      flag_p = 0;
    }
    dst->bits[i] <<= 1;
    if (temp) {
      set_bit(&(dst->bits[i]), 0, 1);
    }
  }
  return error;
}

void shuffle_big_dec_right(s21_big_decimal *dst) {
  dst->bits[0] >>= 1;
  for (int i = 1; i < 6; i++) {
    if (dst->bits[i] & 1) {
      set_bit(&(dst->bits[i - 1]), 31, 1);
    }
    dst->bits[i] >>= 1;
  }
}

int sum_equal_exp(s21_big_decimal summand, s21_big_decimal addend,
                  s21_big_decimal *result, int last_bit) {
  int err = 1;
  s21_big_decimal temp;
  memset(&temp, 0, 28);
  memset(result, 0, 28);

  set_exp(get_exp(summand.bits[6]), &(result->bits[6]));
  int flag_plus = 0;
  for (int i = 0; i < last_bit / 32 + 1; ++i) {
    int ind = 0;
    int flag_local_plus = 0;
    int bit = 31;
    i == last_bit / 32 ? bit = last_bit % 32 : 1;
    last_bit < 32 ? bit = last_bit : 1;
    for (int j = 0; j < bit + 1; ++j) {
      int s_bite = 0, a_bite = 0;
      s_bite = summand.bits[i] & 1;
      a_bite = addend.bits[i] & 1;
      int summ = a_bite + s_bite + flag_local_plus;
      if (flag_plus) {
        summ += flag_plus;
        flag_plus = 0;
      }
      if (summ == 1) {
        flag_local_plus = 0;
        set_bit(&(result->bits[i]), ind, 1);
      } else if (summ == 2) {
        flag_local_plus = 1;
        set_bit(&(result->bits[i]), ind, 0);
      } else if (summ == 3) {
        flag_local_plus = 1;
        set_bit(&(result->bits[i]), ind, 1);
      }
      if (j == bit && flag_local_plus) {
        flag_plus = 1;
      }
      ++ind;
      summand.bits[i] >>= 1;
      addend.bits[i] >>= 1;
    }
  }
  flag_plus == 1 ? err = 0 : 1;
  return err;
}

void _x10(s21_big_decimal *dst) {
  shuffle_big_dec_left(dst);  // разбор функции
  s21_big_decimal temp = *dst;
  shuffle_big_dec_left(&temp);
  shuffle_big_dec_left(&temp);
  sum_equal_exp(*dst, temp, dst, 192);
}

void make_equal_exp(s21_big_decimal *val1, s21_big_decimal *val2) {
  int exp1 = 0, exp2 = 0;
  exp1 = get_exp(val1->bits[6]);
  exp2 = get_exp(val2->bits[6]);
  int sign1 = get_sign(val1->bits[6]);
  int sign2 = get_sign(val2->bits[6]);

  if (exp1 > exp2) {
    *val1 = abs_big_decimal(*val1);
    *val2 = abs_big_decimal(*val2);
    while (exp1 > exp2) {
      _x10(val2);
      ++exp2;
    }
    set_exp(exp1, &(val2->bits[6]));
    if (sign1) s21_negate_big(*val1, val1);
    if (sign2) s21_negate_big(*val2, val2);
  } else if (exp2 > exp1) {
    make_equal_exp(val2, val1);
  }
}

int convert_big_to_dec(s21_big_decimal val, s21_decimal *result, int exp,
                       int op) {
  int err = 0, counter = 0;
  int sign = get_sign(val.bits[6]) ? 1 : 0;
  if (sign) s21_negate_big(val, &val);
  s21_big_decimal temp = {0};
  if ((val.bits[3] > 0 || val.bits[4] > 0 || val.bits[5] > 0) && exp > 0) {
    while ((val.bits[3] > 0 || val.bits[4] > 0 || val.bits[5] > 0) && exp > 0) {
      temp = div10(&val);
      --exp;
      if (temp.bits[0] != 0) ++counter;
    }
  }
  if (exp > 28) {
    while (exp > 28) {
      temp = div10(&val);
      ++counter;
      --exp;
    }
  } else if (exp < 0) {
    while (val.bits[2] <= 429496729 && exp < 0 && val.bits[3] == 0 &&
           val.bits[4] == 0 && val.bits[5] == 0) {
      ++exp;
      _x10(&val);
    }
  }
  if (exp < 0 ||
      (exp == 0 && (val.bits[3] > 0 || val.bits[4] > 0 || val.bits[5] > 0)))
    err = sign ? 2 : 1;

  if ((temp.bits[0] > 5 || (temp.bits[0] == 5 && counter > 1) ||
       (temp.bits[0] > 4 && !op)) &&
      !err) {
    temp.bits[0] = 1;
    sum_equal_exp(val, temp, &val, 191);
  } else if (temp.bits[0] == 5 && !err && counter == 1)
    bank_round(val, &val);

  if ((val.bits[3] > 0 || val.bits[4] > 0 || val.bits[5] > 0) && err == 0)
    err = convert_big_to_dec(val, result, exp, op);
  if (err == 0) {
    set_exp(exp, &(val.bits[6]));
    for (int i = 0; i < 3; ++i) {
      result->bits[i] = val.bits[i];
    }
    result->bits[3] = val.bits[6];
    if (sign) s21_negate(*result, result);
  }
  return err;
}

void bank_round(s21_big_decimal val, s21_big_decimal *result) {
  s21_big_decimal temp = {0};
  temp = div10(&val);
  if (temp.bits[0] % 2 == 1) {
    temp.bits[0] = 1;
    sum_equal_exp(temp, *result, result, 191);
  }
}

s21_decimal abs_decimal(s21_decimal val) {
  set_bit(&(val.bits[3]), 31, 0);
  return val;
}

int minus_equal_exp(s21_big_decimal red, s21_big_decimal ded,
                    s21_big_decimal *result) {
  int err = 0;
  int last_bit = MAX(get_last_bit(ded), get_last_bit(red));
  memset(result, 0, 28);
  set_exp(red.bits[6], &(result->bits[6]));
  if (!get_sign(red.bits[6]) && get_sign(ded.bits[6])) {
    s21_negate_big(ded, &ded);  //?
    err = sum_equal_exp(red, ded, result, 120);
  } else if (get_sign(red.bits[6]) && !get_sign(ded.bits[6])) {
    s21_negate_big(red, &red);
    err = sum_equal_exp(red, ded, result, 120);
    s21_negate_big(*result, result);
  } else if (get_sign(red.bits[6]) && get_sign(ded.bits[6])) {
    s21_negate_big(ded, &ded);
    s21_negate_big(red, &red);
    err = minus_equal_exp(ded, red, result);
  } else {
    for (int i = 0; i < last_bit / 32 + 1; ++i) {
      if (i == last_bit / 32) {
        int bit = last_bit % 32, temp = ded.bits[i];
        last_bit < 32 ? bit = last_bit : 1;
        for (int j = 0; j < bit + 1; ++j) {
          if (temp & 1)
            set_bit(&ded.bits[i], j, 0);
          else
            set_bit(&ded.bits[i], j, 1);
          temp >>= 1;
        }

      } else {
        ded.bits[i] = ~ded.bits[i];
      }
    }
    s21_big_decimal temp;
    memset(&temp, 0, 28);

    temp.bits[0] = 1;
    sum_equal_exp(ded, temp, &ded, last_bit);

    int sign = sum_equal_exp(red, ded, result, last_bit);
    if (sign && !is_big_dec_zero(ded)) {
      s21_big_decimal temp1 = *result;
      memset(result, 0, 28);
      for (int i = 0; i < last_bit / 32 + 1; ++i) {
        int bit = 31;
        i == last_bit / 32 ? bit = last_bit % 32 : 1;
        last_bit < 32 ? bit = last_bit : 1;
        for (int j = 0; j < bit + 1; ++j) {
          if (!(temp1.bits[i] & 1)) {
            set_bit(&(result->bits[i]), j, 1);
          }
          temp1.bits[i] >>= 1;
        }
      }
      sum_equal_exp(*result, temp, result, 191);
      s21_negate_big(*result, result);
    }
  }
  return err;
}

void plus_one_big(s21_big_decimal *val) {
  s21_big_decimal one;
  memset(&one, 0, 28);
  one.bits[0] = 1;
  sum_equal_exp(*val, one, val, 191);
}
