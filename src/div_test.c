#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"
#include "tests.h"

START_TEST(s21_div_1) {
  s21_decimal dec1, dec2, result;
  memset(&dec1, 0, 16);
  memset(&dec2, 0, 16);
  dec1.bits[0] = 10;
  dec2.bits[0] = 2;
  int err = s21_div(dec1, dec2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_uint_eq(result.bits[0], 5);
}
END_TEST

START_TEST(s21_div_2) {
  s21_decimal dec1, dec2, result;
  memset(&dec1, 0, 16);
  memset(&dec2, 0, 16);
  dec1.bits[0] = 10;
  dec2.bits[0] = 0;
  int err = s21_div(dec1, dec2, &result);
  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(s21_div_3) {
  s21_decimal dec1, dec2, result;
  memset(&dec1, 0, 16);
  memset(&dec2, 0, 16);
  dec1.bits[0] = 5;
  dec2.bits[0] = 10;
  int err = s21_div(dec1, dec2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_uint_eq(result.bits[0], 5);
  ck_assert_int_eq(get_exp(result.bits[3]), 1);
}
END_TEST
START_TEST(s21_div_4) {
  s21_decimal dec1, dec2, result;
  memset(&dec1, 0, 16);
  memset(&dec2, 0, 16);
  s21_from_int_to_decimal(-10, &dec1);
  s21_from_int_to_decimal(-10, &dec2);
  int err = s21_div(dec1, dec2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_uint_eq(result.bits[0], 1);
  ck_assert_int_eq(s21_get_sign_dec(result), 0);
  s21_from_int_to_decimal(10, &dec1);
  s21_from_int_to_decimal(-10, &dec2);
  err = s21_div(dec1, dec2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_uint_eq(result.bits[0], 1);
  ck_assert_int_eq(get_sign(result.bits[3]), 1);
  s21_from_int_to_decimal(-10, &dec1);
  s21_from_int_to_decimal(10, &dec2);
  err = s21_div(dec1, dec2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_uint_eq(result.bits[0], 1);
  ck_assert_int_eq(s21_get_sign_dec(result), 1);
}
END_TEST
START_TEST(s21_div_5) {
  s21_decimal dec1, dec2, result;
  memset(&dec1, 0, 16);
  memset(&dec2, 0, 16);
  dec1.bits[0] = 1;
  dec2.bits[0] = 1;
  set_exp(1, &dec2.bits[3]);
  int err = s21_div(dec1, dec2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_uint_eq(result.bits[0], 10);
  ck_assert_int_eq(get_exp(result.bits[3]), 0);
}
END_TEST

START_TEST(s21_div_6) {
  s21_decimal dec1, dec2, result;
  memset(&dec1, 0, 16);
  memset(&dec2, 0, 16);
  dec1.bits[0] = 3;
  dec2.bits[0] = 5;
  int err = s21_div(dec1, dec2, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_uint_eq(result.bits[0], 6);
  ck_assert_int_eq(s21_get_exp_dec(result), 1);
}
END_TEST

START_TEST(s21_div_7) {
  s21_decimal dec1, dec2, result;
  memset(&dec1, 0, 16);
  memset(&dec2, 0, 16);
  dec1.bits[0] = 1;
  dec2.bits[0] = 3;
  int err = s21_div(dec1, dec2, &result);
  ck_assert_int_eq(err, 0);
  float f;
  s21_from_decimal_to_float(result, &f);
  ck_assert_int_eq(s21_get_exp_dec(result), 28);
  ck_assert_float_eq_tol(f, 0.333333, 0.000001);
  memset(&dec1, 0, 16);
  memset(&dec2, 0, 16);
  dec1.bits[0] = 5;
  dec2.bits[0] = 3;
  err = s21_div(dec1, dec2, &result);
  ck_assert_int_eq(err, 0);
  s21_from_decimal_to_float(result, &f);
  ck_assert_int_eq(s21_get_exp_dec(result), 28);
  ck_assert_double_eq_tol(f, 1.66667, 0.00001);
}
END_TEST

START_TEST(s21_div_8) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 9;
  dec1.bits[3] = 65536;
  dec2.bits[0] = 6;
  dec2.bits[3] = 65536;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 15;
  true_ans.bits[3] = 65536;
  int res = s21_div(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_div_9) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 2814903;
  dec1.bits[3] = 65536;
  dec2.bits[0] = 0;
  int res = s21_div(dec1, dec2, &ans);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(s21_div_10) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[3] = 65536;
  dec2.bits[0] = 4578783;
  s21_decimal true_ans = {0};
  int res = s21_div(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_div_11) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 4294967294;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  dec2.bits[0] = 1;
  dec2.bits[3] = 1179648;
  int res = s21_div(dec1, dec2, &ans);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_div_12) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 4294967294;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  dec2.bits[0] = 1;
  set_exp(10, &(dec2.bits[3]));
  s21_negate(dec2, &dec2);
  int res = s21_div(dec1, dec2, &ans);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(s21_div_13) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 1996679748;
  dec1.bits[1] = 4232406046;
  dec1.bits[2] = 151016884;
  dec1.bits[3] = 2148335616;
  dec2.bits[0] = 2671657829;
  dec2.bits[1] = 165868194;
  dec2.bits[2] = 0;
  dec2.bits[3] = 327680;
  // -278576982813512.8359044835908 / 7123984713482.41253 =
  // -39.104096094745301845239149102
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 0b00001010101001000011001000101110;
  true_ans.bits[1] = 0b11110011010000101110001000010000;
  true_ans.bits[2] = 0b1111110010110100010011001110000;
  true_ans.bits[3] = 2149253120;
  int res = s21_div(dec1, dec2, &ans);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_div_14) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;

  dec2.bits[0] = 1;
  set_exp(10, &(dec2.bits[3]));
  set_exp(10, &(dec1.bits[3]));
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 4294967295;
  true_ans.bits[1] = 4294967295;
  true_ans.bits[2] = 4294967295;
  int res = s21_div(dec1, dec2, &ans);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(s21_div_15) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 1188260494;
  dec1.bits[1] = 2547073670;
  dec1.bits[2] = 423;
  dec1.bits[3] = 786432;
  dec2.bits[0] = 1658453339;
  dec2.bits[1] = 2896612263;
  dec2.bits[2] = 67010;
  dec2.bits[3] = 786432;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 2998137797;
  true_ans.bits[1] = 614149364;
  true_ans.bits[2] = 3426771;
  true_ans.bits[3] = 1835008;
  int res = s21_div(dec1, dec2, &ans);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

Suite *dec_div_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_dec_div");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_div_1);
  tcase_add_test(tc_core, s21_div_2);
  tcase_add_test(tc_core, s21_div_3);
  tcase_add_test(tc_core, s21_div_4);
  tcase_add_test(tc_core, s21_div_5);
  tcase_add_test(tc_core, s21_div_6);
  tcase_add_test(tc_core, s21_div_7);
  tcase_add_test(tc_core, s21_div_8);
  tcase_add_test(tc_core, s21_div_9);
  tcase_add_test(tc_core, s21_div_10);
  tcase_add_test(tc_core, s21_div_11);
  tcase_add_test(tc_core, s21_div_12);
  tcase_add_test(tc_core, s21_div_13);
  tcase_add_test(tc_core, s21_div_14);
  tcase_add_test(tc_core, s21_div_15);
  suite_add_tcase(s, tc_core);
  return s;
}