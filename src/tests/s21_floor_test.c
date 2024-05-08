#include "s21_decimal_suites.h"

// s21_current_sign !0 = -2147483648

START_TEST(floor_test_1_float) {
  float a = 1234.3456;
  s21_decimal floor = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(a, &floor);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(floor, &result);
  s21_from_decimal_to_float(floor, &a);
  ck_assert_int_eq(a, 1234);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), 0);
}
END_TEST

START_TEST(floor_test_1_int) {
  int a = 1234;
  s21_decimal floor = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(a, &floor);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(floor, &result);
  s21_from_decimal_to_int(floor, &a);
  ck_assert_int_eq(a, 1234);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), 0);
}
END_TEST

START_TEST(floor_test_2_neg_int) {
  int a = -1234;
  s21_decimal floor = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(a, &floor);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(floor, &result);
  s21_from_decimal_to_int(floor, &a);
  ck_assert_int_eq(a, -1234);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), -2147483648);
}
END_TEST

START_TEST(floor_test_2_negfloat) {
  float a = -1234.35;
  s21_decimal floor = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(a, &floor);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(floor, &result);
  s21_from_decimal_to_float(result, &a);
  ck_assert_float_eq(a, -1235);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), -2147483648);
}
END_TEST

START_TEST(floor_test_3_zero) {
  s21_decimal floor = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(floor, &result);
  int equal = s21_compare(floor, result);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(equal, 0);
  ck_assert_int_eq(s21_current_sign(result), 0);
}
END_TEST

START_TEST(floor_test_4_noexp) {
  s21_decimal floor = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal result = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  int status = s21_truncate(floor, &result);
  int equal = s21_compare(floor, result);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(equal, 0);
  ck_assert_int_eq(s21_current_sign(result), 0);
}
END_TEST

START_TEST(floor_test_5_midexp) {
  s21_decimal floor = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal result = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  float a = 0;
  s21_set_exp(&floor, 26);
  int status = s21_floor(floor, &result);
  s21_from_decimal_to_float(result, &a);
  s21_compare(floor, result);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_float_eq(a, 792.0);
  ck_assert_int_eq(s21_current_sign(result), 0);
}
END_TEST

START_TEST(floor_test_wrong_decimal) {
  s21_decimal floor = {{0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}};
  s21_decimal result = {{0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff}};
  int status = s21_negate(floor, &result);
  int equal = s21_is_equal(floor, result);
  ck_assert_int_eq(status, CONV_ERR);
  ck_assert_int_eq(equal, FALSE);
}
END_TEST

START_TEST(floor_test_zero_with_exp) {
  s21_decimal floor = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_set_exp(&result, 20);
  int status = s21_floor(floor, &result);
  int equal = s21_is_equal(floor, result);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(equal, TRUE);
}
END_TEST

START_TEST(floor_test_zero_with_drob) {
  float a = 0.3456;
  s21_decimal floor = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(a, &floor);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(floor, &result);
  s21_from_decimal_to_float(floor, &a);
  ck_assert_int_eq(a, 0.0);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), 0);
}
END_TEST

Suite *s21_floor_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_floor");
  tc = tcase_create("s21_floor_case");

  tcase_add_test(tc, floor_test_1_float);
  tcase_add_test(tc, floor_test_2_negfloat);
  tcase_add_test(tc, floor_test_1_int);
  tcase_add_test(tc, floor_test_2_neg_int);
  tcase_add_test(tc, floor_test_3_zero);
  tcase_add_test(tc, floor_test_4_noexp);
  tcase_add_test(tc, floor_test_5_midexp);
  tcase_add_test(tc, floor_test_wrong_decimal);
  tcase_add_test(tc, floor_test_zero_with_exp);
  tcase_add_test(tc, floor_test_zero_with_drob);
  suite_add_tcase(s, tc);

  return s;
}