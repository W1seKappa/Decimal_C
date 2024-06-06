#include "s21_decimal.h"

// тут нет проверки на знак, вызывается только для двух положительных
int s21_is_less_or_equal_big(s21_big_decimal lhs, s21_big_decimal rhs) {
  int result = 1;
  make_equal_exp(&lhs, &rhs);
  int break_flag = 0, ind = 5;
  while (ind >= 0 && !break_flag) {
    if (lhs.bits[ind] > rhs.bits[ind]) {
      result = 0;
      break_flag = 1;
    } else if (lhs.bits[ind] < rhs.bits[ind]) {
      result = 1;
      break_flag = 1;
    }
    --ind;
  }
  return result;
}