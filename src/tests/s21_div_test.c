#include "s21_decimal_suites.h"

START_TEST(div_test_1) {
  // 150/16=9.375
  s21_decimal first = {{150, 0, 0, 0}};
  s21_decimal second = {{16, 0, 0, 0}};
  s21_decimal exp = {{9375, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_div(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_2) {
  // 150/-16=-9.375
  s21_decimal first = {{150, 0, 0, 0}};
  s21_decimal second = {{16, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal exp = {{9375, 0, 0, 0b10000000000000110000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_div(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_3) {
  //-150/16=-9.375
  s21_decimal first = {{150, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal second = {{16, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal exp = {{9375, 0, 0, 0b10000000000000110000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_div(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_4) {
  //-150/-16=9.375
  s21_decimal first = {{150, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal second = {{16, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal exp = {{9375, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_div(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_5) {
  // 150/13=11.538461538461538461538461538
  s21_decimal first = {{150, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal second = {{13, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal exp = {
      {0b00010010011101100010011101100010, 0b01011011011001011100011110101011,
       0b100101010010000110010001000101, 0b00000000000110110000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_div(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_6) {
  // 150/0=err
  s21_decimal first = {{150, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal second = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal exp = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_div(first, second, &res);
  int exp_int = 3;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_7) {
  // 150/-0=err
  s21_decimal first = {{150, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal second = {{0, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal exp = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_div(first, second, &res);
  int exp_int = 3;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_8) {
  // 0/150=0
  s21_decimal first = {{150, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal second = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal exp = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_div(second, first, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_9) {
  // 150/150=1
  s21_decimal first = {{150, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal second = {{150, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal exp = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_div(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_10) {
  // max/max=1
  s21_decimal first = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b00000000000000000000000000000000}};
  s21_decimal second = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b00000000000000000000000000000000}};
  s21_decimal exp = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_div(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_11) {
  // min/min=1
  s21_decimal first = {{1, 0, 0, 0b00000000000111000000000000000000}};
  s21_decimal second = {{1, 0, 0, 0b00000000000111000000000000000000}};
  s21_decimal exp = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_div(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_12) {
  // max/1=max
  s21_decimal first = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b00000000000000000000000000000000}};
  s21_decimal second = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal exp = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b00000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_div(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_13) {
  // min/1=0
  s21_decimal first = {{1, 0, 0, 0b00000000000111000000000000000000}};
  s21_decimal second = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal exp = {{0, 0, 0, 0b00000000000111000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_div(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_14) {
  // max/2^46=281474976710657
  s21_decimal first = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b00000000000000000000000000000000}};
  s21_decimal second = {
      {0xFFFFFFFF, 0xFFFF, 0, 0b00000000000000000000000000000000}};
  s21_decimal exp = {{0b00000000000000000000000000000001,
                      0b00000000000000010000000000000000, 0,
                      0b00000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_div(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_15) {
  // max/-2^46=-281474976710657
  s21_decimal first = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b00000000000000000000000000000000}};
  s21_decimal second = {
      {0xFFFFFFFF, 0xFFFF, 0, 0b10000000000000000000000000000000}};
  s21_decimal exp = {{0b00000000000000000000000000000001,
                      0b00000000000000010000000000000000, 0,
                      0b10000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_div(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_16) {
  // 2^46/max=0
  s21_decimal first = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b00000000000000000000000000000000}};
  s21_decimal second = {
      {0xFFFFFFFF, 0xFFFF, 0, 0b00000000000000000000000000000000}};
  s21_decimal exp = {{0, 0, 0, 0b00000000000011100000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_div(second, first, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_17) {
  // max/1/10^28=err(1)
  s21_decimal first = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b00000000000000000000000000000000}};
  s21_decimal second = {{1, 0, 0, 0b00000000000111000000000000000000}};
  s21_decimal exp = {{0}};
  s21_decimal res = {{0}};
  int err = s21_div(first, second, &res);
  int exp_int = 1;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_18) {
  // max/-1/10^28=err(2)
  s21_decimal first = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b00000000000000000000000000000000}};
  s21_decimal second = {{1, 0, 0, 0b10000000000111000000000000000000}};
  s21_decimal exp = {{0}};
  s21_decimal res = {{0}};
  int err = s21_div(first, second, &res);
  int exp_int = 2;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_19) {
  //-max/1/10^28=err(2)
  s21_decimal first = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b10000000000000000000000000000000}};
  s21_decimal second = {{1, 0, 0, 0b00000000000111000000000000000000}};
  s21_decimal exp = {{0}};
  s21_decimal res = {{0}};
  int err = s21_div(first, second, &res);
  int exp_int = 2;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_20) {
  //-max/-1/10^28=err(1)
  s21_decimal first = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b10000000000000000000000000000000}};
  s21_decimal second = {{1, 0, 0, 0b10000000000111000000000000000000}};
  s21_decimal exp = {{0}};
  s21_decimal res = {{0}};
  int err = s21_div(first, second, &res);
  int exp_int = 1;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_21) {
  // 1/10^28/max=0
  s21_decimal first = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b00000000000000000000000000000000}};
  s21_decimal second = {{1, 0, 0, 0b00000000000111000000000000000000}};
  s21_decimal exp = {{0}};
  s21_decimal res = {{0}};
  int err = s21_div(second, first, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_22) {
  //-1/10^28/max=0
  s21_decimal first = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b00000000000000000000000000000000}};
  s21_decimal second = {{1, 0, 0, 0b10000000000111000000000000000000}};
  s21_decimal exp = {{0}};
  s21_decimal res = {{0}};
  int err = s21_div(second, first, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_23) {
  //-1/10^28/-max=0
  s21_decimal first = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b10000000000000000000000000000000}};
  s21_decimal second = {{1, 0, 0, 0b10000000000111000000000000000000}};
  s21_decimal exp = {{0}};
  s21_decimal res = {{0}};
  int err = s21_div(second, first, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_24) {
  // 1/10^28/-max=0
  s21_decimal first = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b10000000000000000000000000000000}};
  s21_decimal second = {{1, 0, 0, 0b00000000000111000000000000000000}};
  s21_decimal exp = {{0}};
  s21_decimal res = {{0}};
  int err = s21_div(second, first, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_28) {
  // res not 0
  s21_decimal first = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b10000000000000000000000000000000}};
  s21_decimal second = {{1, 0, 0, 0b00000000000111000000000000000000}};
  s21_decimal exp = {{0}};
  s21_decimal res = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b00000000000000000000000000000000}};
  int err = s21_div(second, first, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_29) {
  // random
  s21_decimal first = {{0, 0, 0, 0}};
  s21_from_float_to_decimal((float)73351.34435, &first);
  s21_decimal second = {{0, 0, 0, 0}};
  s21_from_float_to_decimal((float)73351.34435, &second);
  s21_decimal exp = {{1, 0, 0, 0}};
  s21_decimal res = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b00000000000000000000000000000000}};
  int err = s21_div(second, first, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_30) {
  // random big
  s21_decimal first = {{0, 4352435, 456345, 0}};
  s21_decimal second = {{0, 4352435, 456345, 0}};
  s21_decimal exp = {{1, 0, 0, 0}};
  s21_decimal res = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b00000000000000000000000000000000}};
  int err = s21_div(second, first, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_31) {
  // res empty
  s21_decimal first = {{0, 4352435, 456345, 0}};
  s21_decimal second = {{0, 4352435, 456345, 0}};
  s21_decimal exp = {{1, 0, 0, 0}};
  s21_decimal res = {};
  int err = s21_div(second, first, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(div_test_killer) {
  // res uninitialized
  s21_decimal first = {{0, 4352435, 456345, 0}};
  s21_decimal second = {{0, 4352435, 456345, 0}};
  s21_decimal exp = {{1, 0, 0, 0}};
  s21_decimal res;
  int err = s21_div(second, first, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST
// 0.00000000000000355271
// 79228162514264337593543950335/281474976710655 = 281474976710657
// 00100101010010000110010001000101 01011011011001011100011110101011
// 00010010011101100010011101100010
//   100101010010000110010001000101 01011011011001011100011110101011
//   00010010011101100010011101100010
// 111011101001110000011011010101010111110000100100111111011110000001110110001001110110001001
// 111011101001110000011011010101010111110000100100111111011110000001110110001001110110001001
Suite *s21_div_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_div");
  tc = tcase_create("s21_div_case");

  tcase_add_test(tc, div_test_1);
  tcase_add_test(tc, div_test_2);
  tcase_add_test(tc, div_test_3);
  tcase_add_test(tc, div_test_4);
  tcase_add_test(tc, div_test_5);
  tcase_add_test(tc, div_test_6);
  tcase_add_test(tc, div_test_7);
  tcase_add_test(tc, div_test_8);
  tcase_add_test(tc, div_test_9);
  tcase_add_test(tc, div_test_10);
  tcase_add_test(tc, div_test_11);
  tcase_add_test(tc, div_test_12);
  tcase_add_test(tc, div_test_13);
  tcase_add_test(tc, div_test_14);
  tcase_add_test(tc, div_test_15);
  tcase_add_test(tc, div_test_16);
  tcase_add_test(tc, div_test_17);
  tcase_add_test(tc, div_test_18);
  tcase_add_test(tc, div_test_19);
  tcase_add_test(tc, div_test_20);
  tcase_add_test(tc, div_test_21);
  tcase_add_test(tc, div_test_22);
  tcase_add_test(tc, div_test_23);
  tcase_add_test(tc, div_test_24);
  tcase_add_test(tc, div_test_28);
  tcase_add_test(tc, div_test_29);
  tcase_add_test(tc, div_test_30);
  tcase_add_test(tc, div_test_31);
  tcase_add_test(tc, div_test_killer);

  suite_add_tcase(s, tc);

  return s;
}