#include "s21_decimal_suites.h"

START_TEST(from_decimal_to_float_test_1) {
  s21_decimal src = {{0x1, 0, 0, 0}};
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, 1.0, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_2) {
  s21_decimal src = {{0xF, 0, 0, 0}};
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, 15.0, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_3) {
  s21_decimal src = {{0xF, 0, 0, 0}};
  s21_set_exp(&src, 1);
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, 1.5, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_4) {
  s21_decimal src = {{0xFF, 0, 0, 0}};
  s21_set_exp(&src, 2);
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, 2.55, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_5) {
  s21_decimal src = {{0xFF, 0, 0, 0}};
  float *v1_float = NULL;
  ck_assert_int_eq(s21_from_decimal_to_float(src, v1_float), CONV_ERR);
}
END_TEST

START_TEST(from_decimal_to_float_test_6) {
  s21_decimal src = {{0, 0, 0, 0}};
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, 0.0, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_7) {
  s21_decimal src = {{0, 0, 0, 0}};
  s21_set_exp(&src, 2);
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, 0.0, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_8) {
  s21_decimal src = {{0xFFFF, 0, 0, 0}};
  s21_set_exp(&src, 10);
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, 0.0000065535, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_9) {
  s21_decimal src = {{0xFFFF, 0, 0, 0}};
  s21_set_exp(&src, 5);
  s21_change_sign(&src);
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, -0.65535, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_10) {
  s21_decimal src = {{0xFFFF, 0, 0, 0}};
  s21_set_exp(&src, 29);
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, 65535.0, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_11) {
  s21_decimal src = {{0xFFFF, 0, 0, 0xFF0000}};
  float v1_float = 0.0;
  int err = s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, 0.0, S21_EPS_TEST);
  ck_assert_int_eq(1, err);
}
END_TEST

START_TEST(from_decimal_to_float_test_12) {
  s21_decimal src = {{S21_BIT_MAX, S21_BIT_MAX, S21_BIT_MAX, 0}};
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, DECIMAL_MAX, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_13) {
  s21_decimal src = {{S21_BIT_MAX, S21_BIT_MAX, S21_BIT_MAX, 0}};
  s21_change_sign(&src);
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, DECIMAL_MIN, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_14) {
  s21_decimal src = {{S21_BIT_MAX, S21_BIT_MAX, S21_BIT_MAX, 0}};
  s21_set_exp(&src, 2);
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, 792281625142643375935439503.35,
                         S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_15) {
  s21_decimal src = {{0xFFF, 0xFFF0, 0, 0}};
  s21_set_exp(&src, 2);
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, 2814062572380.15, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_16) {
  s21_decimal src = {{0, 0, 0, 0}};
  s21_set_exp(&src, 20);
  s21_change_sign(&src);
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, 0.0, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_17) {
  s21_decimal src = {{0xFFFF, 0, 0, 0}};
  s21_set_exp(&src, 12);
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, 0.000000065535, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_18) {
  s21_decimal src = {{0xFFFFFF, 0, 0, 0}};
  s21_set_exp(&src, 12);
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, 0.000016777215, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_19) {
  s21_decimal src = {{0xFFFFFF, 0, 0, 0}};
  s21_set_exp(&src, 4);
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, 1677.7215, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_20) {
  s21_decimal src = {{0xFFFFFF, 0, 0, 0}};
  s21_set_exp(&src, 2);
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, 167772.15, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_21) {
  s21_decimal src = {{0xFFFFFF5, 0, 0, 0}};
  s21_set_exp(&src, 2);
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, 2684354.45, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_22) {
  s21_decimal src = {{0xFFFFFF5, 0, 0, 0}};
  s21_set_exp(&src, 5);
  s21_change_sign(&src);
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, -2684.35445, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_23) {
  s21_decimal src = {{0xFFFFFF5, 0, 0, 0}};
  s21_set_exp(&src, 7);
  s21_change_sign(&src);
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, -26.8435445, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_24) {
  s21_decimal src = {{0xF74DFF5, 0, 0, 0}};
  s21_set_exp(&src, 8);
  s21_change_sign(&src);
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, -2.59317749, S21_EPS_TEST);
}
END_TEST

START_TEST(from_decimal_to_float_test_25) {
  s21_decimal src = {{0xF74DFF5, 0, 0, 0}};
  s21_set_exp(&src, 3);
  s21_change_sign(&src);
  float v1_float = 0.0;
  s21_from_decimal_to_float(src, &v1_float);
  ck_assert_float_eq_tol(v1_float, -259317.749, S21_EPS_TEST);
}
END_TEST

Suite *s21_from_decimal_to_float_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_from_decimal_to_float");
  tc = tcase_create("s21_from_decimal_to_float_case");

  tcase_add_test(tc, from_decimal_to_float_test_1);
  tcase_add_test(tc, from_decimal_to_float_test_2);
  tcase_add_test(tc, from_decimal_to_float_test_3);
  tcase_add_test(tc, from_decimal_to_float_test_4);
  tcase_add_test(tc, from_decimal_to_float_test_5);
  tcase_add_test(tc, from_decimal_to_float_test_6);
  tcase_add_test(tc, from_decimal_to_float_test_7);
  tcase_add_test(tc, from_decimal_to_float_test_8);
  tcase_add_test(tc, from_decimal_to_float_test_9);
  tcase_add_test(tc, from_decimal_to_float_test_10);
  tcase_add_test(tc, from_decimal_to_float_test_11);
  tcase_add_test(tc, from_decimal_to_float_test_12);
  tcase_add_test(tc, from_decimal_to_float_test_13);
  tcase_add_test(tc, from_decimal_to_float_test_14);
  tcase_add_test(tc, from_decimal_to_float_test_15);
  tcase_add_test(tc, from_decimal_to_float_test_16);
  tcase_add_test(tc, from_decimal_to_float_test_17);
  tcase_add_test(tc, from_decimal_to_float_test_18);
  tcase_add_test(tc, from_decimal_to_float_test_19);
  tcase_add_test(tc, from_decimal_to_float_test_20);
  tcase_add_test(tc, from_decimal_to_float_test_21);
  tcase_add_test(tc, from_decimal_to_float_test_22);
  tcase_add_test(tc, from_decimal_to_float_test_23);
  tcase_add_test(tc, from_decimal_to_float_test_24);
  tcase_add_test(tc, from_decimal_to_float_test_25);

  suite_add_tcase(s, tc);

  return s;
}