#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"
#include "tests.h"

START_TEST(s21_mul_1) {
  int num1 = -1;
  int num2 = -10;
  int prod_int = 10;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(s21_mul_2) {
  int num1 = 10;
  int num2 = 20;
  int prod_int = 200;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(s21_mul_3) {
  int num1 = -10;
  int num2 = 20;
  int prod_int = -200;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, prod_int);
}
END_TEST

START_TEST(s21_mul_4) {
  int num1 = 9403;
  int num2 = 202;
  int res_origin = 1899406;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(s21_mul_5) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[2] = 4294967295;
  dec2.bits[0] = 2;
  int res = s21_mul(dec1, dec2, &ans);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_mul_6) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 137900165;
  dec1.bits[1] = 69122625;
  dec1.bits[2] = 1;
  dec1.bits[3] = 1310720;
  dec2.bits[0] = 46246921;
  dec2.bits[1] = 0;
  dec2.bits[2] = 0;
  dec2.bits[3] = 983040;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 2090836749;
  true_ans.bits[1] = 3002702997;
  true_ans.bits[2] = 4;
  true_ans.bits[3] = 1835008;
  int res = s21_mul(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_mul_7) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 137900165;
  dec1.bits[1] = 69122625;
  dec1.bits[2] = 1;
  dec1.bits[3] = 1310720;
  dec2.bits[0] = 46246921;
  dec2.bits[1] = 0;
  dec2.bits[2] = 0;
  dec2.bits[3] = 983040;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 2090836749;
  true_ans.bits[1] = 3002702997;
  true_ans.bits[2] = 4;
  true_ans.bits[3] = 1835008;
  s21_negate(dec1, &dec1);
  s21_negate(dec2, &dec2);
  int res = s21_mul(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_mul_8) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 137900165;
  dec1.bits[1] = 69122625;
  dec1.bits[2] = 1;
  dec1.bits[3] = 1310720;
  dec2.bits[0] = 46246921;
  dec2.bits[1] = 0;
  dec2.bits[2] = 0;
  dec2.bits[3] = 983040;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 2090836749;
  true_ans.bits[1] = 3002702997;
  true_ans.bits[2] = 4;
  true_ans.bits[3] = 1835008;
  s21_negate(dec1, &dec1);
  s21_negate(true_ans, &true_ans);
  int res = s21_mul(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_mul_9) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 137900165;
  dec1.bits[1] = 69122625;
  dec1.bits[2] = 1;
  dec1.bits[3] = 1310720;
  dec2.bits[0] = 46246921;
  dec2.bits[1] = 0;
  dec2.bits[2] = 0;
  dec2.bits[3] = 983040;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 2090836749;
  true_ans.bits[1] = 3002702997;
  true_ans.bits[2] = 4;
  true_ans.bits[3] = 1835008;
  s21_negate(dec2, &dec2);
  s21_negate(true_ans, &true_ans);
  int res = s21_mul(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

Suite *dec_mul_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_dec_mul");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_mul_1);
  tcase_add_test(tc_core, s21_mul_2);
  tcase_add_test(tc_core, s21_mul_3);
  tcase_add_test(tc_core, s21_mul_4);
  tcase_add_test(tc_core, s21_mul_5);
  tcase_add_test(tc_core, s21_mul_6);
  tcase_add_test(tc_core, s21_mul_7);
  tcase_add_test(tc_core, s21_mul_8);
  tcase_add_test(tc_core, s21_mul_9);
  suite_add_tcase(s, tc_core);
  return s;
}