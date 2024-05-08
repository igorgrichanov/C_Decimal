#include "s21_decimal_suites.h"

START_TEST(from_float_to_decimal_test_1) {
  float src = 1.0;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, src, S21_EPS_TEST);
}
END_TEST

START_TEST(from_float_to_decimal_test_2) {
  float src = 10.0;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, src, S21_EPS_TEST);
}
END_TEST

START_TEST(from_float_to_decimal_test_3) {
  float src = 0.333;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, src, S21_EPS_TEST);
}
END_TEST

START_TEST(from_float_to_decimal_test_4) {
  float src = 0.666;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, src, S21_EPS_TEST);
}
END_TEST

START_TEST(from_float_to_decimal_test_5) {
  float src = 123.456789;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, src, 1E-4);
}
END_TEST

START_TEST(from_float_to_decimal_test_6) {
  float src = 5555.555;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, src, S21_EPS_TEST);
}
END_TEST

START_TEST(from_float_to_decimal_test_7) {
  float src = FLT_MAX;
  s21_decimal dst = {{0, 0, 0, 0}};
  int err = s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, 0.0, S21_EPS_TEST);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(from_float_to_decimal_test_8) {
  float src = FLT_MIN;
  s21_decimal dst = {{0, 0, 0, 0}};
  int err = s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, 0.0, S21_EPS_TEST);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(from_float_to_decimal_test_9) {
  float src = POS_INF;
  s21_decimal dst = {{0, 0, 0, 0}};
  int err = s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, 0.0, S21_EPS_TEST);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(from_float_to_decimal_test_10) {
  float src = NEG_INF;
  s21_decimal dst = {{0, 0, 0, 0}};
  int err = s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, 0.0, S21_EPS_TEST);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(from_float_to_decimal_test_11) {
  float src = NAN;
  s21_decimal dst = {{0, 0, 0, 0}};
  int err = s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, 0.0, S21_EPS_TEST);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(from_float_to_decimal_test_12) {
  float src = 1e-28;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, src, S21_EPS_TEST);
}
END_TEST

START_TEST(from_float_to_decimal_test_13) {
  float src = 1e-29;
  s21_decimal dst = {{0, 0, 0, 0}};
  int err = s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, 0.0, S21_EPS_TEST);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(from_float_to_decimal_test_14) {
  float src = 2e-20;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, src, S21_EPS_TEST);
}
END_TEST

START_TEST(from_float_to_decimal_test_15) {
  float src = DECIMAL_MAX;
  s21_decimal dst = {{0, 0, 0, 0}};
  int err = s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, 0.0, S21_EPS_TEST);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(from_float_to_decimal_test_16) {
  float src = DECIMAL_MIN;
  s21_decimal dst = {{0, 0, 0, 0}};
  int err = s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, 0.0, S21_EPS_TEST);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(from_float_to_decimal_test_17) {
  float src = -985.112244;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, src, 1E-4);
}
END_TEST

START_TEST(from_float_to_decimal_test_18) {
  float src = -0.0;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, src, S21_EPS_TEST);
}
END_TEST

START_TEST(from_float_to_decimal_test_19) {
  float src = -0.4698731;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, src, S21_EPS_TEST);
}
END_TEST

START_TEST(from_float_to_decimal_test_20) {
  float src = -84.566976;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_int_eq(8456698, dst.bits[0]);
  ck_assert_double_eq_tol(src, dst_float, S21_EPS_TEST);
}
END_TEST

START_TEST(from_float_to_decimal_test_21) {
  float src = -84.566;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, src, S21_EPS_TEST);
}
END_TEST

START_TEST(from_float_to_decimal_test_22) {
  float src = 0.000011335577;
  s21_decimal dst = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &dst);
  float dst_float = 2.0;
  s21_from_decimal_to_float(dst, &dst_float);
  ck_assert_float_eq_tol(dst_float, src, 1e-10);
}
END_TEST

Suite *s21_from_float_to_decimal_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_from_float_to_decimal");
  tc = tcase_create("s21_from_float_to_decimal_case");

  tcase_add_test(tc, from_float_to_decimal_test_1);
  tcase_add_test(tc, from_float_to_decimal_test_2);
  tcase_add_test(tc, from_float_to_decimal_test_3);
  tcase_add_test(tc, from_float_to_decimal_test_4);
  tcase_add_test(tc, from_float_to_decimal_test_5);
  tcase_add_test(tc, from_float_to_decimal_test_6);
  tcase_add_test(tc, from_float_to_decimal_test_7);
  tcase_add_test(tc, from_float_to_decimal_test_8);
  tcase_add_test(tc, from_float_to_decimal_test_9);
  tcase_add_test(tc, from_float_to_decimal_test_10);
  tcase_add_test(tc, from_float_to_decimal_test_11);
  tcase_add_test(tc, from_float_to_decimal_test_12);
  tcase_add_test(tc, from_float_to_decimal_test_13);
  tcase_add_test(tc, from_float_to_decimal_test_14);
  tcase_add_test(tc, from_float_to_decimal_test_15);
  tcase_add_test(tc, from_float_to_decimal_test_16);
  tcase_add_test(tc, from_float_to_decimal_test_17);
  tcase_add_test(tc, from_float_to_decimal_test_18);
  tcase_add_test(tc, from_float_to_decimal_test_19);
  tcase_add_test(tc, from_float_to_decimal_test_20);
  tcase_add_test(tc, from_float_to_decimal_test_21);
  tcase_add_test(tc, from_float_to_decimal_test_22);

  suite_add_tcase(s, tc);

  return s;
}