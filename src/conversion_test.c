#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"
#include "tests.h"

START_TEST(s21_fl_to_dec_1) {
  s21_decimal decimal = {0};
  float number = 1356.22;
  s21_from_float_to_decimal(number, &decimal);
}
END_TEST

START_TEST(s21_fl_to_dec_2) {
  s21_decimal decimal = {0};
  float A = 100.532;
  float B = 0.0;
  s21_from_float_to_decimal(A, &decimal);
  s21_from_decimal_to_float(decimal, &B);
  ck_assert_float_eq(A, B);
}
END_TEST

START_TEST(s21_fl_to_dec_3) {
  s21_decimal decimal = {0};
  float A = -100.532;
  float B = 0.0;
  s21_from_float_to_decimal(A, &decimal);
  s21_from_decimal_to_float(decimal, &B);
  ck_assert_float_eq(A, B);
}
END_TEST

START_TEST(s21_fl_to_dec_4) {
  s21_decimal decimal = {0};
  float A = -10000.121;
  float B = 0.0;
  s21_from_float_to_decimal(A, &decimal);
  s21_from_decimal_to_float(decimal, &B);
  ck_assert_float_eq(-10000.12, B);
}
END_TEST

Suite *float_to_dec_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_float_to_dec");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_fl_to_dec_1);
  tcase_add_test(tc_core, s21_fl_to_dec_2);
  tcase_add_test(tc_core, s21_fl_to_dec_3);
  tcase_add_test(tc_core, s21_fl_to_dec_4);
  // tcase_add_test(tc_core, s21_div_2);
  suite_add_tcase(s, tc_core);
  return s;
}

//------------------------dec_to_int_to_dec-------------------------

START_TEST(s21_int_to_dec) {
  s21_decimal dec1;
  //  int src;
  //  memset(&dec1, 0, 16);
  // src = NAN;
  s21_from_int_to_decimal(5, &dec1);
  ck_assert_uint_eq(dec1.bits[0], 5);
  ck_assert_uint_eq(dec1.bits[1], 0);
  ck_assert_uint_eq(dec1.bits[2], 0);
  ck_assert_uint_eq(dec1.bits[3], 0);
  s21_from_int_to_decimal(-5, &dec1);
  ck_assert_uint_eq(dec1.bits[0], 5);
  ck_assert_uint_eq(dec1.bits[1], 0);
  ck_assert_uint_eq(dec1.bits[2], 0);
  ck_assert_int_eq(s21_get_sign_dec(dec1), 1);
}
END_TEST

START_TEST(s21_dec_to_int) {
  s21_decimal dec1;
  int res;
  memset(&dec1, 0, 16);
  s21_from_int_to_decimal(-5, &dec1);
  s21_from_decimal_to_int(dec1, &res);
  ck_assert_int_eq(res, -5);
  s21_from_int_to_decimal(55555, &dec1);
  set_exp(4, &(dec1.bits[3]));
  s21_from_decimal_to_int(dec1, &res);
  ck_assert_int_eq(res, 5);
}
START_TEST(s21_int_to_dec_1) {
  s21_decimal dec = {0};
  int i = INT32_MAX, res = 0;
  s21_from_int_to_decimal(i, &dec);
  s21_from_decimal_to_int(dec, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(s21_int_to_dec_2) {
  s21_decimal dec = {0};
  int i = INT32_MIN, res = 0;
  s21_from_int_to_decimal(i, &dec);
  s21_from_decimal_to_int(dec, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

Suite *int_to_dec_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_int_to_dec");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_int_to_dec);
  tcase_add_test(tc_core, s21_dec_to_int);
  tcase_add_test(tc_core, s21_int_to_dec_1);
  tcase_add_test(tc_core, s21_int_to_dec_2);
  // tcase_add_test(tc_core, s21_div_2);
  suite_add_tcase(s, tc_core);
  return s;
}