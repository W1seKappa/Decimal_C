#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#define MAX(i, j) (i > j ? i : j)
#define MAX_INT 2147483647
#define MAX_UINT 4294967295
#define MAX_FLT 3.402823e+38
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  uint32_t bits[4];
} s21_decimal;

typedef struct {
  uint32_t bits[7];  // unsigned int 32 bit
} s21_big_decimal;

typedef enum { CONVERSION_SUCCESS, CONVERSION_ERROR } eReturnVal;

int s21_add(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // done
int s21_sub(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // done
int s21_mul(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // done
int s21_div(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // done
s21_big_decimal s21_div_supp(s21_big_decimal value_1, s21_big_decimal value_2,
                             s21_big_decimal *result);  // sup func for div
s21_big_decimal div10(s21_big_decimal *value_1);        // sup func for div
int s21_is_less_or_equal_big(s21_big_decimal lhs,
                             s21_big_decimal rhs);  // sup func for div
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value,
               s21_decimal *result);  // done, also need in add, mul, div, sub
int s21_negate_big(
    s21_big_decimal val,
    s21_big_decimal *result);  // done, also need in add, mul, div, sub

// дополнительные

s21_big_decimal convert_dec_to_big(s21_decimal val);
uint32_t get_exp(uint32_t val);
int get_sign(uint32_t val);
void set_bit(uint32_t *dst, int pos, int bit);
void set_exp(uint32_t val, uint32_t *data);
s21_big_decimal abs_big_decimal(s21_big_decimal val);
int shuffle_big_dec_left(s21_big_decimal *dst);
void shuffle_big_dec_right(s21_big_decimal *dst);
int sum_equal_exp(s21_big_decimal summand, s21_big_decimal addend,
                  s21_big_decimal *result, int last_bit);
void _x10(s21_big_decimal *dst);
void make_equal_exp(s21_big_decimal *val1, s21_big_decimal *val2);
int convert_big_to_dec(s21_big_decimal val, s21_decimal *result, int exp,
                       int op);
s21_decimal abs_decimal(s21_decimal val);
int get_last_bit(s21_big_decimal val);
int is_dec_zero(s21_decimal data);
int is_big_dec_zero(s21_big_decimal data);
void bank_round(s21_big_decimal val, s21_big_decimal *result);
void plus_one_big(s21_big_decimal *val);
int minus_equal_exp(s21_big_decimal red, s21_big_decimal ded,
                    s21_big_decimal *result);
int s21_get_bit_dec(s21_decimal data, int index);
int s21_get_sign_dec(s21_decimal data);
int s21_get_exp_dec(s21_decimal data);
void make_7_digits(s21_big_decimal *val);
#endif  //   SRC_S21_DECIMAL_H_