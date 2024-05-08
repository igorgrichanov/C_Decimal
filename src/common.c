#include "s21_decimal.h"

void s21_change_sign(s21_decimal *src) {
  src->bits[3] ^= 1 << (LOW_BIT_BORDER - 1);
}

// если знак -, вернет отличное от нуля число. При + вернет 0
int s21_current_sign(s21_decimal src) {
  return (1 << (LOW_BIT_BORDER - 1)) & src.bits[3];
}

int s21_get_exp(s21_decimal src) {
  int bit_with_exp = src.bits[3];
  if (s21_current_sign(src)) {
    bit_with_exp ^= 1 << (LOW_BIT_BORDER - 1);
  }
  return bit_with_exp >> 16;
}

// возвращает ошибку, если не 0 < exp < 28
int s21_set_exp(s21_decimal *src, int exp) {
  if (exp > MAX_POW || exp < MIN_POW) {
    return CONV_ERR;
  }
  exp <<= 16;
  if (s21_current_sign(*src)) exp |= 1 << (LOW_BIT_BORDER - 1);
  src->bits[3] = exp;
  return CONV_OK;
}

// вернет 0 если бит = 0, не 0 если бит = 1
int s21_check_bit(s21_decimal src, int bit) {
  int num_int = bit / LOW_BIT_BORDER;
  int num_bit = bit % LOW_BIT_BORDER;
  return (src.bits[num_int] & (1 << num_bit));
}

void s21_set_bit(s21_decimal *src, int bit) {
  int num_int = bit / LOW_BIT_BORDER;
  int num_bit = bit % LOW_BIT_BORDER;
  src->bits[num_int] |= 1 << num_bit;
}

// получить бит в рамках одной мантисы
int s21_get_bits_one(int number, int index) {
  int bit = number & (1 << index);
  bit = bit >> index;
  if (bit == -1) {
    bit = 1;
  }
  return bit;
}

// установить бит в рамках одной мантисы
void s21_set_bits_one(int *number, int index, int bit) {
  if (bit == 1) {
    *number = *number | (1 << index);
  } else {
    int zero_bit = 0;
    s21_set_bits_one(&zero_bit, index, 1);
    zero_bit = ~zero_bit;
    *number = *number & zero_bit;
  }
}

void s21_left_shift(s21_decimal *src) {
  int bits[] = {0, 0, 0};
  for (int i = 0; i < 3; i++) {
    bits[i] = s21_get_bits_one(src->bits[i], 32 * (i + 1) - 1);
  }
  for (int i = 0; i < 3; i++) {
    src->bits[i] <<= 1;
  }
  for (int i = 0; i < 3; i++) {
    if (bits[i]) {
      s21_set_bits_one(&src->bits[i + 1], 0, 1);
    }
  }
}

void s21_right_shift(s21_decimal *src) {
  int bits[] = {0, 0, 0};
  for (int i = 0; i < 3; i++) {
    bits[i] = s21_get_bits_one(src->bits[i + 1], 0);
  }
  for (int i = 0; i < 3; i++) {
    src->bits[i] >>= 1;
  }
  for (int i = 0; i < 3; i++) {
    s21_set_bits_one(&src->bits[i], 32 - 1, bits[i]);
  }
}

void s21_assign_0_to_decimal(s21_decimal *src) {
  src->bits[0] = 0;
  src->bits[1] = 0;
  src->bits[2] = 0;
  src->bits[3] = 0;
}

void s21_switch_decimal(s21_decimal *value_1, s21_decimal *value_2) {
  s21_decimal temp = *value_1;
  *value_1 = *value_2;
  *value_2 = temp;
}