#include "s21_decimal_suites.h"

START_TEST(round_test_1_neg_int) {
  int a = -1234;
  s21_decimal round = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(a, &round);
  s21_decimal result;
  int status = s21_round(round, &result);
  s21_from_decimal_to_int(round, &a);
  int equal = s21_is_less(result, round);
  ck_assert_int_eq(equal, 0);
  ck_assert_int_eq(a, -1234);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), -2147483648);
}
END_TEST

START_TEST(round_test_2_plus_int) {
  int a = 1234;
  s21_decimal round = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(a, &round);
  s21_decimal result;
  int status = s21_round(round, &result);
  s21_from_decimal_to_int(round, &a);
  int equal = s21_is_less(result, round);
  ck_assert_int_eq(equal, 0);
  ck_assert_int_eq(a, 1234);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), 0);
}
END_TEST

START_TEST(round_test_3_plus_float) {
  float a = 1234.3456;
  s21_decimal round = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(a, &round);
  s21_decimal result;
  int status = s21_round(round, &result);
  s21_from_decimal_to_float(result, &a);
  int equal = s21_is_less(result, round);
  ck_assert_int_eq(equal, 1);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), 0);
  ck_assert_float_eq(a, 1234);
}
END_TEST

START_TEST(round_test_4_neg_float) {
  float a = -1234.45666;
  s21_decimal round = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(a, &round);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_round(round, &result);
  s21_from_decimal_to_float(result, &a);
  int equal = s21_is_less(round, result);
  ck_assert_int_eq(equal, 1);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), -2147483648);
  ck_assert_float_eq(a, -1234);
}
END_TEST

START_TEST(round_test_55_one5manyzero) {
  float a = -1234.500000;
  s21_decimal round = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(a, &round);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_round(round, &result);
  s21_from_decimal_to_float(result, &a);
  int equal = s21_is_less(round, result);
  ck_assert_float_eq(a, -1234.0);
  ck_assert_int_eq(equal, TRUE);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), -2147483648);
}
END_TEST

START_TEST(round_test_1234_exp2) {
  float a = -1235.500000;
  s21_decimal round = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(a, &round);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_round(round, &result);
  s21_from_decimal_to_float(result, &a);
  int equal = s21_is_less(result, round);
  ck_assert_float_eq(a, -1236.0);
  ck_assert_int_eq(equal, TRUE);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), -2147483648);
}
END_TEST

START_TEST(round_test_31_plus_float) {
  float a = 1234.9456;
  s21_decimal round = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(a, &round);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_round(round, &result);
  s21_from_decimal_to_float(result, &a);
  int less = s21_is_less(round, result);
  ck_assert_int_eq(less, 1);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), 0);
  ck_assert_float_eq(a, 1235.0);
}
END_TEST

START_TEST(round_test_41_neg_float) {
  float a = -1234.9456;
  s21_decimal round = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(a, &round);
  s21_decimal result;
  int status = s21_round(round, &result);
  s21_from_decimal_to_float(result, &a);
  int less = s21_is_less(result, round);
  ck_assert_float_eq(a, -1235.0);
  ck_assert_int_eq(less, TRUE);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), -2147483648);
}
END_TEST

START_TEST(round_test_5_decim_exp) {
  s21_decimal round = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal result = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_set_exp(&round, 26);
  int status = s21_round(round, &result);
  float a = 0;
  s21_from_decimal_to_float(result, &a);
  int equal = s21_is_less(result, round);
  ck_assert_int_eq(a, 792.0);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(equal, 1);
}
END_TEST

START_TEST(round_test_6_decim_noexp) {
  s21_decimal round = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  s21_decimal result = {{0xffffffff, 0xffffffff, 0xffffffff, 0}};
  int status = s21_round(round, &result);
  int equal = s21_is_equal(round, result);
  ck_assert_int_eq(equal, 1);
  ck_assert_int_eq(status, CONV_OK);
}
END_TEST

START_TEST(round_test_7_zero) {
  s21_decimal round = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_round(round, &result);
  int equal = s21_is_equal(round, result);
  ck_assert_int_eq(equal, 1);
  ck_assert_int_eq(status, CONV_OK);
}
END_TEST

START_TEST(round_test_49_one4many9) {
  float a = -1234.499;
  s21_decimal round = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(a, &round);
  s21_decimal result;
  int status = s21_round(round, &result);
  s21_from_decimal_to_float(result, &a);
  int equal = s21_is_less(round, result);
  ck_assert_float_eq(a, -1234);
  ck_assert_int_eq(equal, 1);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), -2147483648);
}
END_TEST

START_TEST(round_test_bank_chet) {
  float a = 1234.500;
  s21_decimal round = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(a, &round);
  s21_decimal result;
  int status = s21_round(round, &result);
  s21_from_decimal_to_float(result, &a);
  int equal = s21_is_less(result, round);
  ck_assert_float_eq(a, 1234);
  ck_assert_int_eq(equal, 1);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), 0);
}
END_TEST

START_TEST(round_test_bank_nechet) {
  float a = 1231.5000000;
  s21_decimal round = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(a, &round);
  s21_decimal result;
  int status = s21_round(round, &result);
  s21_from_decimal_to_float(result, &a);
  int equal = s21_is_less(round, result);
  ck_assert_float_eq(a, 1232);
  ck_assert_int_eq(equal, 1);
  ck_assert_int_eq(status, CONV_OK);
  ck_assert_int_eq(s21_current_sign(result), 0);
}
END_TEST

Suite *s21_round_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_round");
  tc = tcase_create("s21_round_case");

  tcase_add_test(tc, round_test_1_neg_int);
  tcase_add_test(tc, round_test_2_plus_int);
  tcase_add_test(tc, round_test_3_plus_float);
  tcase_add_test(tc, round_test_4_neg_float);
  tcase_add_test(tc, round_test_31_plus_float);
  tcase_add_test(tc, round_test_41_neg_float);
  tcase_add_test(tc, round_test_5_decim_exp);
  tcase_add_test(tc, round_test_6_decim_noexp);
  tcase_add_test(tc, round_test_7_zero);
  tcase_add_test(tc, round_test_55_one5manyzero);
  tcase_add_test(tc, round_test_1234_exp2);
  tcase_add_test(tc, round_test_49_one4many9);
  tcase_add_test(tc, round_test_bank_chet);
  tcase_add_test(tc, round_test_bank_nechet);
  suite_add_tcase(s, tc);

  return s;
}