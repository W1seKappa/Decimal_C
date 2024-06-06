#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"
#include "tests.h"

START_TEST(s21_sub_1) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0};
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 4;
  set_exp(1, &(b.bits[3]));
  s21_sub(a, b, &res);
  ck_assert_int_eq(a.bits[0], res.bits[0]);
  ck_assert_int_eq(a.bits[1], res.bits[1]);
  ck_assert_int_eq(a.bits[2], res.bits[2]);
}
END_TEST

START_TEST(s21_sub_2) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0};
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 6;
  set_exp(1, &(b.bits[3]));
  s21_sub(a, b, &res);
  ck_assert_int_eq(a.bits[0], res.bits[0] + 1);
  ck_assert_int_eq(a.bits[1], res.bits[1]);
  ck_assert_int_eq(a.bits[2], res.bits[2]);
}
END_TEST

START_TEST(s21_sub_3) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0};
  s21_from_int_to_decimal(100, &a);
  s21_from_int_to_decimal(50, &b);
  int err = s21_sub(a, b, &res);
  int int_res = 0;
  s21_from_decimal_to_int(res, &int_res);
  ck_assert_int_eq(int_res, 50);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(s21_sub_4) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0};
  s21_from_int_to_decimal(-100, &a);
  s21_from_int_to_decimal(50, &b);
  int err = s21_sub(a, b, &res);
  int int_res = 0;
  s21_from_decimal_to_int(res, &int_res);
  ck_assert_int_eq(int_res, -150);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(s21_sub_5) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0};
  s21_from_int_to_decimal(-100, &a);
  s21_from_int_to_decimal(-50, &b);
  int err = s21_sub(a, b, &res);
  int int_res = 0;
  s21_from_decimal_to_int(res, &int_res);
  ck_assert_int_eq(int_res, -50);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(s21_sub_6) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0};
  s21_from_int_to_decimal(100, &a);
  s21_from_int_to_decimal(-50, &b);
  int err = s21_sub(a, b, &res);
  int int_res = 0;
  s21_from_decimal_to_int(res, &int_res);
  ck_assert_int_eq(int_res, 150);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(s21_sub_7) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0};
  s21_from_int_to_decimal(100, &a);
  s21_from_int_to_decimal(500, &b);
  int err = s21_sub(a, b, &res);
  int int_res = 0;
  s21_from_decimal_to_int(res, &int_res);
  ck_assert_int_eq(int_res, -400);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(s21_sub_8) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0};
  s21_from_int_to_decimal(-100, &a);
  s21_from_int_to_decimal(-500, &b);
  int err = s21_sub(a, b, &res);
  int int_res = 0;
  s21_from_decimal_to_int(res, &int_res);
  ck_assert_int_eq(int_res, 400);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(s21_sub_9) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 532167;
  dec1.bits[3] = 196608;

  dec2.bits[0] = 1236;
  dec2.bits[3] = 983040;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 607087404;
  true_ans.bits[1] = 123904785;
  true_ans.bits[3] = 983040;
  int res = s21_sub(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_sub_10) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;
  dec1.bits[0] = 532167;
  dec1.bits[3] = 196608;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 532167;
  true_ans.bits[3] = 196608;
  int res = s21_sub(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

Suite *dec_sub_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_dec_sub");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_sub_1);
  tcase_add_test(tc_core, s21_sub_2);
  tcase_add_test(tc_core, s21_sub_3);
  tcase_add_test(tc_core, s21_sub_4);
  tcase_add_test(tc_core, s21_sub_5);
  tcase_add_test(tc_core, s21_sub_6);
  tcase_add_test(tc_core, s21_sub_7);
  tcase_add_test(tc_core, s21_sub_8);
  tcase_add_test(tc_core, s21_sub_9);
  tcase_add_test(tc_core, s21_sub_10);
  suite_add_tcase(s, tc_core);
  return s;
}