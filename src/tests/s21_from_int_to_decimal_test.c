#include "s21_decimal_suites.h"

START_TEST(from_int_to_decimal_test_1) {
  int src = 1;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(src, dst.bits[0]);
}
END_TEST

START_TEST(from_int_to_decimal_test_2) {
  int src = -1;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(1, dst.bits[0]);
}
END_TEST

START_TEST(from_int_to_decimal_test_3) {
  int src = 0;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(src, dst.bits[0]);
}
END_TEST

START_TEST(from_int_to_decimal_test_4) {
  int src = INT32_MAX;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(src, dst.bits[0]);
}
END_TEST

START_TEST(from_int_to_decimal_test_5) {
  int src = INT32_MIN;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(__INT32_MAX__, dst.bits[0]);
}
END_TEST

START_TEST(from_int_to_decimal_test_6) {
  int src = 45364;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(src, dst.bits[0]);
}
END_TEST

START_TEST(from_int_to_decimal_test_7) {
  int src = -45364;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(src, &dst);
  int dst_int = 0;
  s21_from_decimal_to_int(dst, &dst_int);
  ck_assert_int_eq(dst_int, -45364);
  ck_assert_int_eq(-1 * src, dst.bits[0]);
}
END_TEST

START_TEST(from_int_to_decimal_test_8) {
  int src = -4536;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(src * -1, dst.bits[0]);
}
END_TEST

Suite *s21_from_int_to_decimal_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_from_int_to_decimal");
  tc = tcase_create("s21_from_int_to_decimal_case");

  tcase_add_test(tc, from_int_to_decimal_test_1);
  tcase_add_test(tc, from_int_to_decimal_test_2);
  tcase_add_test(tc, from_int_to_decimal_test_3);
  tcase_add_test(tc, from_int_to_decimal_test_4);
  tcase_add_test(tc, from_int_to_decimal_test_5);
  tcase_add_test(tc, from_int_to_decimal_test_6);
  tcase_add_test(tc, from_int_to_decimal_test_7);
  tcase_add_test(tc, from_int_to_decimal_test_8);

  suite_add_tcase(s, tc);

  return s;
}