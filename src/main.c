#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"
#include "tests.h"

int main() {
  Suite *tests[] = {dec_div_suite(),      dec_add_suite(),  int_to_dec_suite(),
                    float_to_dec_suite(), dec_mul_suite(),  dec_other_suite(),
                    dec_sub_suite(),      dec_comp_suite(), NULL};
  int no_failed = 0;
  for (int i = 0; tests[i]; ++i) {
    SRunner *runner;
    runner = srunner_create(tests[i]);
    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  if (no_failed == 0) printf("TEST OK\n");
  return 0;
}