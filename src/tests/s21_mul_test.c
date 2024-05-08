#include "s21_decimal_suites.h"

START_TEST(mul_test_1) {
  // 127*11=1397
  s21_decimal first = {{127, 0, 0, 0}};
  s21_decimal second = {{11, 0, 0, 0}};
  s21_decimal exp = {{1397, 0, 0, 0}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_2) {
  // 127*-11=-1397
  s21_decimal first = {{127, 0, 0, 0}};
  s21_decimal second = {{11, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal exp = {{1397, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_3) {
  //-127*11=-1397
  s21_decimal first = {{127, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal second = {{11, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal exp = {{1397, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_4) {
  //-127*-11=1397
  s21_decimal first = {{127, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal second = {{11, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal exp = {{1397, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_5) {
  // 127*0=0
  s21_decimal first = {{127, 0, 0, 0}};
  s21_decimal second = {{0, 0, 0, 0}};
  s21_decimal exp = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_6) {
  // 0*11=0
  s21_decimal first = {{0, 0, 0, 0}};
  s21_decimal second = {{11, 0, 0, 0}};
  s21_decimal exp = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_7) {
  //-127*0=0
  s21_decimal first = {{127, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal second = {{0, 0, 0, 0}};
  s21_decimal exp = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_8) {
  // 0*-11=0
  s21_decimal first = {{0, 0, 0, 0}};
  s21_decimal second = {{11, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal exp = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_9) {
  // 2^48 * 2^48 = 2^96
  s21_decimal first = {{0b11111111111111111111111111111111,
                        0b00000000000000001111111111111111, 0, 0}};
  s21_decimal second = {{0b11111111111111111111111111111111,
                         0b00000000000000001111111111111111, 0, 0}};
  s21_decimal exp = {{0b00000000000000000000000000000001,
                      0b11111111111111100000000000000000,
                      0b11111111111111111111111111111111, 0}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_10) {
  // 2^48 * -2^48 = 2^96
  s21_decimal first = {{0b11111111111111111111111111111111,
                        0b00000000000000001111111111111111, 0, 0}};
  s21_decimal second = {{0b11111111111111111111111111111111,
                         0b00000000000000001111111111111111, 0,
                         0b10000000000000000000000000000000}};
  s21_decimal exp = {
      {0b00000000000000000000000000000001, 0b11111111111111100000000000000000,
       0b11111111111111111111111111111111, 0b10000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_11) {
  //-2^48 * -2^48 = 2^96
  s21_decimal first = {{0b11111111111111111111111111111111,
                        0b00000000000000001111111111111111, 0,
                        0b10000000000000000000000000000000}};
  s21_decimal second = {{0b11111111111111111111111111111111,
                         0b00000000000000001111111111111111, 0,
                         0b10000000000000000000000000000000}};
  s21_decimal exp = {{0b00000000000000000000000000000001,
                      0b11111111111111100000000000000000,
                      0b11111111111111111111111111111111, 0}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_12) {
  // 2^48 * 2^49 = err
  s21_decimal first = {{0b11111111111111111111111111111111,
                        0b00000000000000001111111111111111, 0, 0}};
  s21_decimal second = {{0b11111111111111111111111111111111,
                         0b00000000000000011111111111111111, 0,
                         0b00000000000000000000000000000000}};
  s21_decimal exp = {{0}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 1;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_13) {
  // 2^48 * -2^49 = err
  s21_decimal first = {{0b11111111111111111111111111111111,
                        0b00000000000000001111111111111111, 0, 0}};
  s21_decimal second = {{0b11111111111111111111111111111111,
                         0b00000000000000011111111111111111, 0,
                         0b10000000000000000000000000000000}};
  s21_decimal exp = {{0, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 2;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_14) {
  //-2^48 * -2^49 = err
  s21_decimal first = {{0b11111111111111111111111111111111,
                        0b00000000000000001111111111111111, 0,
                        0b10000000000000000000000000000000}};
  s21_decimal second = {{0b11111111111111111111111111111111,
                         0b00000000000000011111111111111111, 0,
                         0b10000000000000000000000000000000}};
  s21_decimal exp = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 1;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_15) {
  // 123456789 * 1.23456789 = 152415787.50190521
  s21_decimal first = {{0b111010110111100110100010101, 0b0, 0,
                        0b00000000000000000000000000000000}};
  s21_decimal second = {{0b111010110111100110100010101, 0b0, 0,
                         0b00000000000010000000000000000000}};
  s21_decimal exp = {{0b10010111001110001010001110111001,
                      0b1101100010011000100010, 0,
                      0b00000000000010000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_16) {
  // 1.23456789987654321 * 1.23456789987654321 = 1.5241578994055784200731595789
  s21_decimal first = {{0b11100000010100101111101010110001,
                        0b1101101101001101101001011, 0,
                        0b00000000000100010000000000000000}};
  s21_decimal second = {{0b11100000010100101111101010110001,
                         0b1101101101001101101001011, 0,
                         0b00000000000100010000000000000000}};
  s21_decimal exp = {
      {0b00011101001101111001010000001101, 0b11011111100011000101110100000110,
       0b00110001001111111000100111100100, 0b00000000000111000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_17) {
  // 1.8765432109876543210987654321 * 1.8765432109876543210987654321
  // = 3.5214144227038561211455570799
  s21_decimal first = {
      {0b01100001110001110000110010110001, 0b00001110110100001000101000110000,
       0b111100101000100110011011010001, 0b00000000000111000000000000000000}};
  s21_decimal second = {
      {0b01100001110001110000110010110001, 0b00001110110100001000101000110000,
       0b111100101000100110011011010001, 0b00000000000111000000000000000000}};
  s21_decimal exp = {
      {0b10100100100101110000001101101111, 0b10101000100111011001011011001010,
       0b1110001110010000111010100010111, 0b00000000000111000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_18) {
  // 1.23456789987654321 * -1.23456789987654321 =
  // -1.5241578994055784200731595789
  s21_decimal first = {{0b11100000010100101111101010110001,
                        0b1101101101001101101001011, 0,
                        0b00000000000100010000000000000000}};
  s21_decimal second = {{0b11100000010100101111101010110001,
                         0b1101101101001101101001011, 0,
                         0b10000000000100010000000000000000}};
  s21_decimal exp = {
      {0b00011101001101111001010000001101, 0b11011111100011000101110100000110,
       0b00110001001111111000100111100100, 0b10000000000111000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_19) {
  // 1.8765432109876543210987654321 * -1.8765432109876543210987654321 =
  // -3.5214144227038561211455570799
  s21_decimal first = {
      {0b01100001110001110000110010110001, 0b00001110110100001000101000110000,
       0b111100101000100110011011010001, 0b00000000000111000000000000000000}};
  s21_decimal second = {
      {0b01100001110001110000110010110001, 0b00001110110100001000101000110000,
       0b111100101000100110011011010001, 0b10000000000111000000000000000000}};
  s21_decimal exp = {
      {0b10100100100101110000001101101111, 0b10101000100111011001011011001010,
       0b1110001110010000111010100010111, 0b10000000000111000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_20) {
  // 0.00000001234 * 0.00000987 = 0.0000000000001217958
  s21_decimal first = {
      {0b10011010010, 0, 0, 0b00000000000010110000000000000000}};
  s21_decimal second = {
      {0b1111011011, 0, 0, 0b00000000000010000000000000000000}};
  s21_decimal exp = {
      {0b100101001010110100110, 0, 0, 0b00000000000100110000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

// REVERSE

START_TEST(mul_test_21) {
  // 11*127=1397
  s21_decimal first = {{127, 0, 0, 0}};
  s21_decimal second = {{11, 0, 0, 0}};
  s21_decimal exp = {{1397, 0, 0, 0}};
  s21_decimal res = {{0}};
  int err = s21_mul(second, first, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_22) {
  //-11*127=-1397
  s21_decimal first = {{127, 0, 0, 0}};
  s21_decimal second = {{11, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal exp = {{1397, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_mul(second, first, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_23) {
  // 11*-127=-1397
  s21_decimal first = {{127, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal second = {{11, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal exp = {{1397, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_mul(second, first, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_24) {
  //-11*-127=1397
  s21_decimal first = {{127, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal second = {{11, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal exp = {{1397, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_mul(second, first, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_25) {
  // 2^49 * 2^48 = err
  s21_decimal first = {{0b11111111111111111111111111111111,
                        0b00000000000000001111111111111111, 0, 0}};
  s21_decimal second = {{0b11111111111111111111111111111111,
                         0b00000000000000011111111111111111, 0,
                         0b00000000000000000000000000000000}};
  s21_decimal exp = {{0}};
  s21_decimal res = {{0}};
  int err = s21_mul(second, first, &res);
  int exp_int = 1;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_26) {
  //-2^49 * 2^48 = err
  s21_decimal first = {{0b11111111111111111111111111111111,
                        0b00000000000000001111111111111111, 0, 0}};
  s21_decimal second = {{0b11111111111111111111111111111111,
                         0b00000000000000011111111111111111, 0,
                         0b10000000000000000000000000000000}};
  s21_decimal exp = {{0, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_mul(second, first, &res);
  int exp_int = 2;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_27) {
  //-2^49 * -2^48 = err
  s21_decimal first = {{0b11111111111111111111111111111111,
                        0b00000000000000001111111111111111, 0,
                        0b10000000000000000000000000000000}};
  s21_decimal second = {{0b11111111111111111111111111111111,
                         0b00000000000000011111111111111111, 0,
                         0b10000000000000000000000000000000}};
  s21_decimal exp = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  int err = s21_mul(second, first, &res);
  int exp_int = 1;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_28) {
  // 1.23456789 * 123456789 = 152415787.50190521
  s21_decimal first = {{0b111010110111100110100010101, 0b0, 0,
                        0b00000000000000000000000000000000}};
  s21_decimal second = {{0b111010110111100110100010101, 0b0, 0,
                         0b00000000000010000000000000000000}};
  s21_decimal exp = {{0b10010111001110001010001110111001,
                      0b1101100010011000100010, 0,
                      0b00000000000010000000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_mul(second, first, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_29) {
  // 0.00000987 * 0.00000001234= 0.0000000000001217958
  s21_decimal first = {
      {0b10011010010, 0, 0, 0b00000000000010110000000000000000}};
  s21_decimal second = {
      {0b1111011011, 0, 0, 0b00000000000010000000000000000000}};
  s21_decimal exp = {
      {0b100101001010110100110, 0, 0, 0b00000000000100110000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_mul(second, first, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_30) {
  // 187654321098.76543210987654321 * 1876543.2109876543210987654321 =
  // 352141442270385612.1145557099
  s21_decimal first = {
      {0b01100001110001110000110010110001, 0b00001110110100001000101000110000,
       0b111100101000100110011011010001, 0b00000000000100010000000000000000}};
  s21_decimal second = {
      {0b01100001110001110000110010110001, 0b00001110110100001000101000110000,
       0b111100101000100110011011010001, 0b00000000000101100000000000000000}};
  s21_decimal exp = {
      {0b10100100100101110000001101101111, 0b10101000100111011001011011001010,
       0b01110001110010000111010100010111, 0b00000000000010110000000000000000}};
  s21_decimal res = {{0}};
  int err = s21_mul(first, second, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

START_TEST(mul_test_killer) {
  // res uninitialized
  s21_decimal first = {
      {0b01100001110001110000110010110001, 0b00001110110100001000101000110000,
       0b111100101000100110011011010001, 0b00000000000100010000000000000000}};
  s21_decimal second = {
      {0b01100001110001110000110010110001, 0b00001110110100001000101000110000,
       0b111100101000100110011011010001, 0b00000000000101100000000000000000}};
  s21_decimal exp = {
      {0b10100100100101110000001101101111, 0b10101000100111011001011011001010,
       0b01110001110010000111010100010111, 0b00000000000010110000000000000000}};
  s21_decimal res;
  int err = s21_mul(second, first, &res);
  int exp_int = 0;
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(res.bits[i], exp.bits[i]);
  }
  ck_assert_int_eq(err, exp_int);
}
END_TEST

// 00000000000000000000000000000000 00000000000000000000000000000000
// 00000000000000000010010010011111
//     1011011000001101100010000010 01011101101010010101101111100001
//     00010000011101011000000001101011
//   111100101000100110011011010001 00001110110100001000101000110000
//   01100001110001110000110010110001

Suite *s21_mul_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_mul");
  tc = tcase_create("s21_mul_case");

  tcase_add_test(tc, mul_test_1);
  tcase_add_test(tc, mul_test_2);
  tcase_add_test(tc, mul_test_3);
  tcase_add_test(tc, mul_test_4);
  tcase_add_test(tc, mul_test_5);
  tcase_add_test(tc, mul_test_6);
  tcase_add_test(tc, mul_test_7);
  tcase_add_test(tc, mul_test_8);
  tcase_add_test(tc, mul_test_9);
  tcase_add_test(tc, mul_test_10);
  tcase_add_test(tc, mul_test_11);
  tcase_add_test(tc, mul_test_12);
  tcase_add_test(tc, mul_test_13);
  tcase_add_test(tc, mul_test_14);
  tcase_add_test(tc, mul_test_15);
  tcase_add_test(tc, mul_test_16);
  tcase_add_test(tc, mul_test_17);
  tcase_add_test(tc, mul_test_18);
  tcase_add_test(tc, mul_test_19);
  tcase_add_test(tc, mul_test_20);
  tcase_add_test(tc, mul_test_21);
  tcase_add_test(tc, mul_test_22);
  tcase_add_test(tc, mul_test_23);
  tcase_add_test(tc, mul_test_24);
  tcase_add_test(tc, mul_test_25);
  tcase_add_test(tc, mul_test_26);
  tcase_add_test(tc, mul_test_27);
  tcase_add_test(tc, mul_test_28);
  tcase_add_test(tc, mul_test_29);
  tcase_add_test(tc, mul_test_30);
  tcase_add_test(tc, mul_test_killer);
  suite_add_tcase(s, tc);

  return s;
}