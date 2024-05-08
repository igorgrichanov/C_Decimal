#include "s21_decimal_suites.h"

START_TEST(from_decimal_to_int_test_1) {
  s21_decimal src = {{0x1, 0, 0, 0}};
  int dst = 0;
  s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(dst, 1);
}
END_TEST

START_TEST(from_decimal_to_int_test_2) {
  s21_decimal src = {{0xF, 0, 0, 0}};
  int dst = 0;
  s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(dst, 15);
}
END_TEST

START_TEST(from_decimal_to_int_test_3) {
  s21_decimal src = {{0, 0, 0, 0}};
  int dst = 0;
  s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(dst, 0);
}
END_TEST

START_TEST(from_decimal_to_int_test_4) {
  s21_decimal src = {{0, 0xF, 0, 0}};
  int dst = 0;
  s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(dst, 0);
}
END_TEST

START_TEST(from_decimal_to_int_test_5) {
  s21_decimal src = {{0, 0xF, 0, 0}};
  s21_set_exp(&src, 2);
  int dst = 0;
  s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(dst, 644245094);
}
END_TEST

START_TEST(from_decimal_to_int_test_6) {
  s21_decimal src = {{0, 0, 0xFF, 0}};
  s21_set_exp(&src, 28);
  int dst = 0;
  s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(dst, 0);
}
END_TEST

START_TEST(from_decimal_to_int_test_7) {
  s21_decimal src = {{0xFFFFFFFF, 0, 0, 0}};
  int dst = 0;
  s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(dst, 0);
}
END_TEST

START_TEST(from_decimal_to_int_test_8) {
  s21_decimal src = {{0x7FFFFFFF, 0, 0, 0}};
  s21_change_sign(&src);
  int dst = 0;
  s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(dst, INT32_MIN);
}
END_TEST

START_TEST(from_decimal_to_int_test_9) {
  s21_decimal src = {{0x7FFFFFFF, 0, 0, 0}};
  int dst = 0;
  s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(dst, INT32_MAX);
}
END_TEST

START_TEST(from_decimal_to_int_test_10) {
  s21_decimal src = {{0xF3FFF, 0, 0, 0}};
  int dst = 0;
  s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(dst, 999423);
}
END_TEST

START_TEST(from_decimal_to_int_test_11) {
  s21_decimal src = {{0xF3FFF, 0, 0, 0}};
  int *dst = NULL;
  int err = s21_from_decimal_to_int(src, dst);
  ck_assert_int_eq(err, CONV_ERR);
}
END_TEST

START_TEST(from_decimal_to_int_test_12) {
  s21_decimal src = {{0xF3FFF, 0, 0, 0x7F0000}};
  int dst = 0;
  int err = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(err, CONV_ERR);
}
END_TEST

START_TEST(from_decimal_to_int_test_13) {
  s21_decimal src = {{0xFFFF, 0, 0, 0}};
  s21_set_exp(&src, 5);
  int dst = 0;
  s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(dst, 0);
}
END_TEST

START_TEST(from_decimal_to_int_test_14) {
  s21_decimal src = {{0xFFFF, 0, 0, 0}};
  s21_change_sign(&src);
  s21_set_exp(&src, 5);
  int dst = 0;
  s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(dst, 0);
}
END_TEST

START_TEST(from_decimal_to_int_test_15) {
  s21_decimal src = {{0xFFFF, 0, 0, 0}};
  s21_change_sign(&src);
  s21_set_exp(&src, 4);
  int dst = 0;
  s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(dst, -6);
}
END_TEST

START_TEST(from_decimal_to_int_test_16) {
  s21_decimal src = {{0x3FFF, 0, 0, 0}};
  s21_change_sign(&src);
  s21_set_exp(&src, 4);
  int dst = 0;
  s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(dst, -1);
}
END_TEST

Suite *s21_from_decimal_to_int_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_from_decimal_to_int");
  tc = tcase_create("s21_from_decimal_to_int_case");

  tcase_add_test(tc, from_decimal_to_int_test_1);
  tcase_add_test(tc, from_decimal_to_int_test_2);
  tcase_add_test(tc, from_decimal_to_int_test_3);
  tcase_add_test(tc, from_decimal_to_int_test_4);
  tcase_add_test(tc, from_decimal_to_int_test_5);
  tcase_add_test(tc, from_decimal_to_int_test_6);
  tcase_add_test(tc, from_decimal_to_int_test_7);
  tcase_add_test(tc, from_decimal_to_int_test_8);
  tcase_add_test(tc, from_decimal_to_int_test_9);
  tcase_add_test(tc, from_decimal_to_int_test_10);
  tcase_add_test(tc, from_decimal_to_int_test_11);
  tcase_add_test(tc, from_decimal_to_int_test_12);
  tcase_add_test(tc, from_decimal_to_int_test_13);
  tcase_add_test(tc, from_decimal_to_int_test_14);
  tcase_add_test(tc, from_decimal_to_int_test_15);
  tcase_add_test(tc, from_decimal_to_int_test_16);

  suite_add_tcase(s, tc);

  return s;
}