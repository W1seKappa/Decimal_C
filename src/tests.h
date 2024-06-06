#ifndef tests_h
#define tests_h

#include <check.h>
#include <stdio.h>

Suite* dec_add_suite(void);
Suite* int_to_dec_suite(void);
Suite* float_to_dec_suite(void);
Suite* dec_div_suite(void);
Suite* dec_mul_suite(void);
Suite* dec_sub_suite(void);
Suite* dec_comp_suite(void);
Suite* dec_other_suite(void);
#endif /* tests_h */