#include "s21_decimal_suites.h"

START_TEST(is_less_or_equal_test_1) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 1);
}
END_TEST

START_TEST(is_less_or_equal_test_2) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 1);
}
END_TEST

START_TEST(is_less_or_equal_test_3) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_set_exp(&a, 23);
  s21_set_exp(&b, 23);

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 1);
}
END_TEST

START_TEST(is_less_or_equal_test_4) {
  s21_decimal a = {{743895734, 353234, 234045, 0}};
  s21_decimal b = {{74389534, 353234, 134045, 0}};
  s21_set_exp(&a, 23);
  s21_set_exp(&b, 23);

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 1);
}
END_TEST

START_TEST(is_less_or_equal_test_5) {
  s21_decimal a = {{743895734, 353234, 0, 0}};
  s21_decimal b = {{74389534, 353234, 0, 0}};
  s21_set_exp(&a, 23);
  s21_set_exp(&b, 23);

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 1);
}
END_TEST

START_TEST(is_less_or_equal_test_6) {
  s21_decimal a = {{743895734, 353234, 234045, 0}};
  s21_decimal b = {{74389534, 353234, 134045, 0}};
  s21_set_exp(&a, 23);
  s21_set_exp(&b, 23);
  s21_change_sign(&a);

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 0);
}
END_TEST

START_TEST(is_less_or_equal_test_7) {
  s21_decimal a = {{743895734, 353234, 0, 0}};
  s21_decimal b = {{74389534, 353234, 0, 0}};
  s21_set_exp(&a, 23);
  s21_set_exp(&b, 23);
  s21_change_sign(&a);

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 0);
}
END_TEST

START_TEST(is_less_or_equal_test_8) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_change_sign(&a);

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 1);
}
END_TEST

START_TEST(is_less_or_equal_test_9) {
  s21_decimal a = {{743895734, 353234, 0, 0}};
  s21_decimal b = {{743895734, 353234, 0, 0}};
  s21_set_exp(&a, 25);
  s21_set_exp(&b, 23);

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 0);
}
END_TEST

START_TEST(is_less_or_equal_test_10) {
  s21_decimal a = {{125000, 0, 0, 0}};
  s21_decimal b = {{125, 0, 0, 0}};
  s21_set_exp(&a, 5);
  s21_set_exp(&b, 2);

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 1);
}
END_TEST

START_TEST(is_less_or_equal_test_11) {
  s21_decimal a = {{743895734, 353234, 234045, 0xFF0000}};
  s21_decimal b = {{74389534, 353234, 134045, 0xFF0000}};

  ck_assert_int_eq(s21_is_less_or_equal(a, b), FALSE);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), FALSE);
}
END_TEST

START_TEST(is_less_or_equal_test_12) {
  s21_decimal a = {{743895734, 353234, 234045, 0}};
  s21_decimal b = {{74389534, 353234, 134045, 0xFF0000}};

  ck_assert_int_eq(s21_is_less_or_equal(a, b), FALSE);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), FALSE);
}
END_TEST

Suite *s21_is_less_or_equal_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_is_less_or_equal");
  tc = tcase_create("s21_is_less_or_equal_case");

  tcase_add_test(tc, is_less_or_equal_test_1);
  tcase_add_test(tc, is_less_or_equal_test_2);
  tcase_add_test(tc, is_less_or_equal_test_3);
  tcase_add_test(tc, is_less_or_equal_test_4);
  tcase_add_test(tc, is_less_or_equal_test_5);
  tcase_add_test(tc, is_less_or_equal_test_6);
  tcase_add_test(tc, is_less_or_equal_test_7);
  tcase_add_test(tc, is_less_or_equal_test_8);
  tcase_add_test(tc, is_less_or_equal_test_9);
  tcase_add_test(tc, is_less_or_equal_test_10);
  tcase_add_test(tc, is_less_or_equal_test_11);
  tcase_add_test(tc, is_less_or_equal_test_12);

  suite_add_tcase(s, tc);

  return s;
}