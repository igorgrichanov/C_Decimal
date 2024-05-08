#include "s21_decimal_suites.h"

START_TEST(negate_test_1_neg_int) {
  int a = -1234;
  s21_decimal neg = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(a, &neg);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_negate(neg, &result);
  s21_from_decimal_to_int(result, &a);
  ck_assert_int_eq(a, 1234);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), 0);
}
END_TEST

START_TEST(negate_test_2_neg_float) {
  float a = -1234.345;
  s21_decimal neg = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(a, &neg);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_negate(neg, &result);
  s21_from_decimal_to_float(result, &a);
  ck_assert_float_eq(a, 1234.345);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), 0);
}
END_TEST

START_TEST(negate_test_3_plus_float) {
  float a = 1234.3459;
  s21_decimal neg = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(a, &neg);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_negate(neg, &result);
  s21_from_decimal_to_float(result, &a);
  int equal = s21_is_less(result, neg);
  ck_assert_int_eq(equal, 1);
  ck_assert_float_eq(a, -1234.3459);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), -2147483648);
}
END_TEST

START_TEST(negate_test_plus_int) {
  int a = 1234;
  s21_decimal neg = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(a, &neg);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_negate(neg, &result);
  s21_from_decimal_to_int(result, &a);
  ck_assert_int_eq(a, -1234);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), -2147483648);
}
END_TEST

START_TEST(negate_test_big_decimal_midexp) {
  s21_decimal neg = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal result = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_set_exp(&neg, 10);
  int status = s21_negate(neg, &result);
  int equal = s21_is_less(result, neg);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(equal, 1);
  ck_assert_int_eq(s21_current_sign(result), -2147483648);
}
END_TEST

START_TEST(negate_test_big_decimal_noexp) {
  s21_decimal neg = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal result = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  int status = s21_negate(neg, &result);
  int equal = s21_is_less(result, neg);
  ck_assert_int_eq(equal, 1);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), -2147483648);
}
END_TEST

START_TEST(negate_test_zero) {
  s21_decimal neg = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_negate(neg, &result);
  int equal = s21_is_equal(neg, result);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(negate_test_wrong_decimal) {
  s21_decimal neg = {{0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}};
  s21_decimal result = {{0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}};
  int status = s21_negate(neg, &result);
  int equal = s21_is_equal(neg, result);
  ck_assert_int_eq(status, CONV_ERR);
  ck_assert_int_eq(equal, FALSE);
}
END_TEST

START_TEST(negate_test_zero_with_exp) {
  s21_decimal neg = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_set_exp(&result, 20);
  int status = s21_negate(neg, &result);
  int equal = s21_is_equal(neg, result);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(equal, 1);
}
END_TEST

Suite *s21_negate_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_negate");
  tc = tcase_create("s21_negate_case");

  tcase_add_test(tc, negate_test_1_neg_int);
  tcase_add_test(tc, negate_test_2_neg_float);
  tcase_add_test(tc, negate_test_3_plus_float);
  tcase_add_test(tc, negate_test_big_decimal_midexp);
  tcase_add_test(tc, negate_test_big_decimal_noexp);
  tcase_add_test(tc, negate_test_zero);
  tcase_add_test(tc, negate_test_wrong_decimal);
  tcase_add_test(tc, negate_test_zero_with_exp);
  tcase_add_test(tc, negate_test_plus_int);
  suite_add_tcase(s, tc);

  return s;
}