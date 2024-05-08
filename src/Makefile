CC=gcc -std=c11
CFLAGS=-Wall -Wextra -Werror
FLAG_COV=--coverage
FUNC_TESTS_C=tests/*_test.c
VALGRIND_FLAGS=--tool=memcheck --track-origins=yes

OS=$(shell uname -s)

ifeq ($(OS),Linux)
	TEST_LIBS=-lcheck -lsubunit -pthread -lrt -lm
else
	TEST_LIBS=-lcheck
endif

all: s21_decimal.a

s21_decimal.a: *.c
	$(CC) $(CFLAGS) -c $^
	ar rc $@ *.o
	ranlib $@

test:
	$(CC) $(CFLAGS) -o s21_decimal tests/main.c $(FUNC_TESTS_C) *.c $(FLAG_COV) `pkg-config --cflags --libs check`
	./s21_decimal

gcov_report: test
	gcov ./s21_decimal
	lcov -c -d . -o gcov.info
	genhtml gcov.info -o gcov_report
	open gcov_report/index.html

format:
	@cp ../materials/linters/.clang-format ./
	@clang-format -i *.c *.h tests/*.c tests/*.h
	@clang-format -n *.c *.h tests/*.c tests/*.h
	@rm .clang-format

gcov_macos:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

valgrind: clean
	$(CC) $(CFLAGS) -o s21_decimal tests/main.c $(FUNC_TESTS_C) -g -O0 *.c $(TEST_LIBS)
	valgrind $(VALGRIND_FLAGS) ./s21_decimal

clean:
	rm -rf gcov_report/
	rm -f *.info s21_decimal
	rm -f *.gcda *.gcno *.gcov *.o *.a

rebuild: clean all