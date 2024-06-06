#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"
#include "tests.h"

START_TEST(s21_add_1) {
  s21_decimal dec1, dec2, result;
  memset(&dec1, 0, 16);
  memset(&dec2, 0, 16);
  dec1.bits[0] = 5;
  dec2.bits[0] = 10;
  int err = s21_add(dec1, dec2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_uint_eq(result.bits[0], 15);
  ck_assert_int_eq(s21_get_exp_dec(result), 0);
}
END_TEST

START_TEST(s21_add_2) {
  s21_decimal dec1, dec2, result;
  memset(&dec1, 0, 16);
  memset(&dec2, 0, 16);
  dec1.bits[0] = 5;
  dec2.bits[0] = 10;
  set_exp(1, &dec1.bits[3]);
  int err = s21_add(dec1, dec2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_uint_eq(result.bits[0], 105);
  int val;
  s21_from_decimal_to_int(result, &val);
  ck_assert_int_eq(val, 10);
  ck_assert_int_eq(s21_get_exp_dec(result), 1);
}
END_TEST
START_TEST(s21_add_3) {
  int num1 = 42;
  int num2 = 30;
  int sum_int = 72;
  s21_decimal a, b;
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
  ck_assert_int_eq(s21_add(a, b, &res_dec), 0);
}
END_TEST

START_TEST(s21_add_4) {
  int num1 = 0;
  int num2 = 0;
  int sum_int = 0;
  s21_decimal a, b;
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
}
END_TEST

START_TEST(s21_add_5) {
  int num1 = -1;
  int num2 = -10;
  int sum_int = -11;
  s21_decimal a, b;
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, sum_int);
}
END_TEST

START_TEST(s21_add_6) {
  s21_decimal src1, src2;
  int a = -1234;
  int b = 234;
  int res_origin = -1000;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(s21_add_7) {
  s21_decimal src1, src2;
  int a = 450;
  int b = -50;
  int res_origin = 400;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(s21_add_8) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans = {0};
  dec1.bits[0] = 4238529012;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 0;

  dec2.bits[0] = 56438283;
  dec2.bits[1] = 4294967295;
  dec2.bits[2] = 4294967294;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 4294967295;
  true_ans.bits[1] = 4294967294;
  true_ans.bits[2] = 4294967295;

  int res = s21_add(dec1, dec2, &ans);

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_add_9) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans = {0};
  dec1.bits[0] = 4238529012;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;

  dec2.bits[0] = 56438283;
  dec2.bits[1] = 4294967295;
  dec2.bits[2] = 4294967294;

  int res = s21_add(dec1, dec2, &ans);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_add_14) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans = {0};
  dec1.bits[0] = 4238529012;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;

  dec2.bits[0] = 56438283;
  dec2.bits[1] = 4294967295;
  dec2.bits[2] = 4294967294;
  s21_negate(dec1, &dec1);
  s21_negate(dec2, &dec2);
  int res = s21_add(dec1, dec2, &ans);

  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(s21_add_10) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans = {0};
  dec1.bits[0] = 613478421;
  dec1.bits[3] = 196608;
  dec2.bits[0] = 2056771366;
  dec2.bits[1] = 613;
  dec2.bits[3] = 393216;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 1354869038;
  true_ans.bits[1] = 756;
  true_ans.bits[3] = 393216;
  int res = s21_add(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_add_11) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans = {0};

  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;

  dec1.bits[3] = 196608;

  dec2.bits[0] = 1;
  dec2.bits[3] = 196608;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 2576980378;
  true_ans.bits[1] = 2576980377;
  true_ans.bits[2] = 429496729;
  true_ans.bits[3] = 131072;
  int res = s21_add(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_add_12) {
  s21_decimal src1, src2;
  int num1 = -1234;
  float num2 = 1.234;
  float res_origin = -1232.766;
  s21_from_int_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(s21_add_13) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;

  dec1.bits[0] = 4294967280;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  // 11111111 11111111 11111111 11111111
  // 11111111 11111111 11111111 11111111
  // 11111111 11111111 11111111 11111111
  // 11111111 11111111 11111111 11110000 =
  // 79228162514264337593543950335 - 15 = 79228162514264337593543950320

  dec2.bits[0] = 5;
  set_exp(1, &dec2.bits[3]);

  // 79228162514264337593543950320 + 0.5 = 79228162514264337593543950320.5 =

  // 79228162514264337593543950320.5 = 79228162514264337593543950320
  // используем банковское округление - округляется к ближайшему четному

  int res = s21_add(dec1, dec2, &ans);

  ck_assert_int_eq(1, s21_is_equal(ans, dec1));
  ck_assert_int_eq(res, 0);
}
END_TEST

Suite *dec_add_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_dec_add");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_add_1);
  tcase_add_test(tc_core, s21_add_2);
  tcase_add_test(tc_core, s21_add_3);
  tcase_add_test(tc_core, s21_add_4);
  tcase_add_test(tc_core, s21_add_5);
  tcase_add_test(tc_core, s21_add_6);
  tcase_add_test(tc_core, s21_add_7);
  tcase_add_test(tc_core, s21_add_8);
  tcase_add_test(tc_core, s21_add_9);
  tcase_add_test(tc_core, s21_add_10);
  tcase_add_test(tc_core, s21_add_11);
  tcase_add_test(tc_core, s21_add_12);
  tcase_add_test(tc_core, s21_add_13);
  tcase_add_test(tc_core, s21_add_14);
  suite_add_tcase(s, tc_core);
  return s;
}