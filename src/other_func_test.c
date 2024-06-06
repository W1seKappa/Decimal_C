#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"

START_TEST(s21_floor_1) {
  s21_decimal a = {0};
  float val = 9.99;
  s21_from_float_to_decimal(val, &a);
  s21_floor(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 9, 0.000001);
}
END_TEST

START_TEST(s21_floor_2) {
  s21_decimal a = {0};
  float val = -9.99;
  s21_from_float_to_decimal(val, &a);
  s21_floor(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -10, 0.000001);
}
END_TEST

START_TEST(s21_floor_3) {
  s21_decimal a = {0};
  float val = 0.0;
  s21_from_float_to_decimal(val, &a);
  s21_floor(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 0, 0.000001);
}
END_TEST

START_TEST(s21_floor_4) {
  s21_decimal a = {0};
  ck_assert_int_eq(1, s21_floor(a, NULL));
}
END_TEST

START_TEST(s21_floor_5) {
  // -39.104096094745301845239149102
  // 01111110 01011010 00100110 01110000
  // 11110011 01000010 11100010 00010000
  // 00001010 10100100 00110010 00101110
  // 10000000 00011011 00000000 00000000
  s21_decimal dec = {0};
  dec.bits[0] = 178532910;
  dec.bits[1] = 4081246736;
  dec.bits[2] = 2119837296;
  dec.bits[3] = 2149253120;

  s21_decimal ans;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 40;
  s21_negate(true_ans, &true_ans);
  int res = s21_floor(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_floor_6) {
  // 0.91275848761238746318274123
  // 00000000 01001011 10000000 01101001
  // 10101101 00010110 00101101 10111100
  // 00100011 10110000 01111110 01001011
  // 00000000 00011010 00000000 00000000
  s21_decimal dec = {0};
  dec.bits[0] = 598769227;
  dec.bits[1] = 2903911868;
  dec.bits[2] = 4948073;
  dec.bits[3] = 1703936;

  s21_decimal ans;

  s21_decimal true_ans = {0};
  int res = s21_floor(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_floor_7) {
  // -0.91275848761238746318274123
  // 00000000 01001011 10000000 01101001
  // 10101101 00010110 00101101 10111100
  // 00100011 10110000 01111110 01001011
  // 00000000 00011010 00000000 00000000
  s21_decimal dec = {0};
  dec.bits[0] = 598769227;
  dec.bits[1] = 2903911868;
  dec.bits[2] = 4948073;
  dec.bits[3] = 1703936;
  s21_negate(dec, &dec);
  s21_decimal ans;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 1;
  s21_negate(true_ans, &true_ans);
  int res = s21_floor(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_floor_8) {
  s21_decimal dec = {0};
  dec.bits[0] = 784662527;
  dec.bits[1] = 11641532;
  dec.bits[3] = 1114112;
  s21_decimal ans;
  s21_decimal true_ans = {0};
  int res = s21_floor(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_round_1) {
  s21_decimal a = {0};
  float val = 9.5;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 10, 0.000001);
}
END_TEST

START_TEST(s21_round_2) {
  s21_decimal a = {0};
  float val = -9.49;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -9, 0.000001);
}
END_TEST

START_TEST(s21_round_3) {
  s21_decimal a = {0};
  float val = 0.0;
  s21_from_float_to_decimal(val, &a);
  s21_round(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 0, 0.000001);
}
END_TEST

START_TEST(s21_round_4) {
  s21_decimal a = {0};
  ck_assert_int_eq(1, s21_round(a, NULL));
}
END_TEST

START_TEST(s21_round_5) {
  // -39.104096094745301845239149102
  // 01111110 01011010 00100110 01110000
  // 11110011 01000010 11100010 00010000
  // 00001010 10100100 00110010 00101110
  // 10000000 00011011 00000000 00000000
  s21_decimal dec = {0};
  dec.bits[0] = 178532910;
  dec.bits[1] = 4081246736;
  dec.bits[2] = 2119837296;
  dec.bits[3] = 2149253120;

  s21_decimal ans;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 39;
  s21_negate(true_ans, &true_ans);
  int res = s21_round(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_round_6) {
  // 0.91275848761238746318274123
  // 00000000 01001011 10000000 01101001
  // 10101101 00010110 00101101 10111100
  // 00100011 10110000 01111110 01001011
  // 00000000 00011010 00000000 00000000
  s21_decimal dec = {0};
  dec.bits[0] = 598769227;
  dec.bits[1] = 2903911868;
  dec.bits[2] = 4948073;
  dec.bits[3] = 1703936;

  s21_decimal ans;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 1;
  int res = s21_round(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_round_7) {
  // -0.91275848761238746318274123
  // 00000000 01001011 10000000 01101001
  // 10101101 00010110 00101101 10111100
  // 00100011 10110000 01111110 01001011
  // 00000000 00011010 00000000 00000000
  s21_decimal dec = {0};
  dec.bits[0] = 598769227;
  dec.bits[1] = 2903911868;
  dec.bits[2] = 4948073;
  dec.bits[3] = 1703936;
  s21_negate(dec, &dec);
  s21_decimal ans;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 1;
  s21_negate(true_ans, &true_ans);
  int res = s21_round(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_round_8) {
  s21_decimal dec = {0};
  dec.bits[0] = 784662527;
  dec.bits[1] = 11641532;
  dec.bits[3] = 1114112;
  s21_decimal ans;
  s21_decimal true_ans = {0};
  int res = s21_round(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_trunc_1) {
  s21_decimal a = {0};
  float val = 9.5;
  s21_from_float_to_decimal(val, &a);
  s21_truncate(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 9, 0.000001);
}
END_TEST

START_TEST(s21_trunc_2) {
  s21_decimal a = {0};
  float val = -9.49;
  s21_from_float_to_decimal(val, &a);
  s21_truncate(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, -9, 0.000001);
}
END_TEST

START_TEST(s21_trunc_3) {
  s21_decimal a = {0};
  float val = 0.0;
  s21_from_float_to_decimal(val, &a);
  s21_truncate(a, &a);
  s21_from_decimal_to_float(a, &val);
  ck_assert_float_eq_tol(val, 0, 0.000001);
}
END_TEST

START_TEST(s21_trunc_4) {
  s21_decimal a = {0};
  ck_assert_int_eq(1, s21_truncate(a, NULL));
}
END_TEST

START_TEST(s21_truncate_5) {
  // -39.104096094745301845239149102
  // 01111110 01011010 00100110 01110000
  // 11110011 01000010 11100010 00010000
  // 00001010 10100100 00110010 00101110
  // 10000000 00011011 00000000 00000000
  s21_decimal dec = {0};
  dec.bits[0] = 178532910;
  dec.bits[1] = 4081246736;
  dec.bits[2] = 2119837296;
  dec.bits[3] = 2149253120;

  s21_decimal ans;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 39;
  s21_negate(true_ans, &true_ans);
  int res = s21_truncate(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_truncate_6) {
  // 0.91275848761238746318274123
  // 00000000 01001011 10000000 01101001
  // 10101101 00010110 00101101 10111100
  // 00100011 10110000 01111110 01001011
  // 00000000 00011010 00000000 00000000
  s21_decimal dec = {0};
  dec.bits[0] = 598769227;
  dec.bits[1] = 2903911868;
  dec.bits[2] = 4948073;
  dec.bits[3] = 1703936;

  s21_decimal ans;

  s21_decimal true_ans = {0};
  int res = s21_truncate(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_truncate_7) {
  // -0.91275848761238746318274123
  // 00000000 01001011 10000000 01101001
  // 10101101 00010110 00101101 10111100
  // 00100011 10110000 01111110 01001011
  // 00000000 00011010 00000000 00000000
  s21_decimal dec = {0};
  dec.bits[0] = 598769227;
  dec.bits[1] = 2903911868;
  dec.bits[2] = 4948073;
  dec.bits[3] = 1703936;
  s21_negate(dec, &dec);
  s21_decimal ans;

  s21_decimal true_ans = {0};
  s21_negate(true_ans, &true_ans);
  int res = s21_truncate(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_truncate_8) {
  s21_decimal dec = {0};
  dec.bits[0] = 784662527;
  dec.bits[1] = 11641532;
  dec.bits[3] = 1114112;
  s21_decimal ans;
  s21_decimal true_ans = {0};
  int res = s21_truncate(dec, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

Suite *dec_other_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_dec_other");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_floor_1);
  tcase_add_test(tc_core, s21_floor_2);
  tcase_add_test(tc_core, s21_floor_3);
  tcase_add_test(tc_core, s21_floor_4);
  tcase_add_test(tc_core, s21_floor_5);
  tcase_add_test(tc_core, s21_floor_6);
  tcase_add_test(tc_core, s21_floor_7);
  tcase_add_test(tc_core, s21_floor_8);
  tcase_add_test(tc_core, s21_round_4);
  tcase_add_test(tc_core, s21_round_1);
  tcase_add_test(tc_core, s21_round_2);
  tcase_add_test(tc_core, s21_round_3);
  tcase_add_test(tc_core, s21_round_5);
  tcase_add_test(tc_core, s21_round_6);
  tcase_add_test(tc_core, s21_round_7);
  tcase_add_test(tc_core, s21_round_8);
  tcase_add_test(tc_core, s21_trunc_1);
  tcase_add_test(tc_core, s21_trunc_2);
  tcase_add_test(tc_core, s21_trunc_3);
  tcase_add_test(tc_core, s21_trunc_4);
  tcase_add_test(tc_core, s21_truncate_5);
  tcase_add_test(tc_core, s21_truncate_6);
  tcase_add_test(tc_core, s21_truncate_7);
  tcase_add_test(tc_core, s21_truncate_8);

  //    tcase_add_test(tc_core, s21_div_3);
  suite_add_tcase(s, tc_core);
  return s;
}