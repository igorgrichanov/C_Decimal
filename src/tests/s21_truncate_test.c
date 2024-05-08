#include "s21_decimal_suites.h"

START_TEST(truncate_test_1_float) {
  float a = 1234.3456;
  s21_decimal trunc = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(a, &trunc);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_truncate(trunc, &result);
  s21_from_decimal_to_float(result, &a);
  int equal = s21_is_less(result, trunc);
  ck_assert_int_eq(equal, TRUE);
  ck_assert_float_eq(a, 1234);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), 0);
}
END_TEST

START_TEST(truncate_test_2_negfloat) {
  float a = -1234.3456;
  s21_decimal trunc = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(a, &trunc);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_truncate(trunc, &result);
  s21_from_decimal_to_float(result, &a);
  int equal = s21_is_less(trunc, result);
  ck_assert_int_eq(equal, TRUE);
  ck_assert_int_eq(a, -1234);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), -2147483648);
}
END_TEST

START_TEST(truncate_test_zero_with_drob) {
  float a = 0.3456;
  s21_decimal floor = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(a, &floor);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_truncate(floor, &result);
  s21_from_decimal_to_float(floor, &a);
  ck_assert_int_eq(a, 0.0);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), 0);
}
END_TEST

START_TEST(truncate_test_3_zero) {
  s21_decimal trunc = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_truncate(trunc, &result);
  int equal = s21_is_equal(trunc, result);
  ck_assert_int_eq(equal, TRUE);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), 0);
}
END_TEST

START_TEST(truncate_test_4_noexp) {
  s21_decimal trunc = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal result = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  int status = s21_truncate(trunc, &result);
  int equal = s21_is_equal(trunc, result);
  ck_assert_int_eq(equal, TRUE);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), 0);
}
END_TEST

START_TEST(truncate_test_5_midexp) {
  s21_decimal trunc = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal result = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_set_exp(&trunc, 26);
  int status = s21_truncate(trunc, &result);
  float a = 0;
  s21_from_decimal_to_float(result, &a);
  int equal = s21_is_less(result, trunc);
  ck_assert_int_eq(a, 792.0);
  ck_assert_int_eq(equal, TRUE);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), 0);
}
END_TEST

Suite *s21_truncate_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_truncate");
  tc = tcase_create("s21_truncate_case");

  tcase_add_test(tc, truncate_test_1_float);
  tcase_add_test(tc, truncate_test_2_negfloat);
  tcase_add_test(tc, truncate_test_zero_with_drob);
  tcase_add_test(tc, truncate_test_3_zero);
  tcase_add_test(tc, truncate_test_4_noexp);
  tcase_add_test(tc, truncate_test_5_midexp);
  suite_add_tcase(s, tc);

  return s;
}