CFLAGS = -Wall -Werror -Wextra -std=c11
GCCFLAGS = -std=c11 -Wall -Werror -Wextra
GCOVFLAGS = -fprofile-arcs -ftest-coverage
FORDANILAM2 = -I/opt/homebrew/Cellar/check/0.15.2/include -L/opt/homebrew/Cellar/check/0.15.2/lib

all: s21_decimal.a 

ubuntu: clean s21_decimal.a test_ubuntu gcov_report

test: *.c
	gcc -o test $(CFLAGS) --coverage *.c -lcheck  -lpthread -lm  -I/usr/local/include -L/usr/local/lib
	./test
	
test_ubuntu: s21_decimal.a
	gcc -o test $(CFLAGS) --coverage add_test.c comp_test.c conversion_test.c div_test.c main.c mul_test.c sub_test.c other_func_test.c s21_decimal.a -lcheck -lm -lpthread -lsubunit
	./test
	
s21_decimal.a: clean clang
	gcc $(GCCFLAGS) -g -c s21_*.c
	ar rc s21_decimal.a *.o
	ranlib s21_decimal.a
	rm *.o
	
gcov_report: test_ubuntu
	./test
	lcov -t "gcov_test" -o gcov_test.info -c -d .
	genhtml -o report gcov_test.info
	open report/index.html

clang:
	clang-format -style=Google -i *.c *.h

clean:
	rm -rf *.o *.a *.gcno *.gcda *.info test report gcovreport check
