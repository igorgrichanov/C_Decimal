#include "s21_decimal.h"

// 0 если равны, 1 если больше первое, 2 если второе.
int s21_compare(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  int i = 95;
  while (i >= 0) {
    int bit_1 = s21_get_bits_one(value_1.bits[i / 32], i % 32);
    int bit_2 = s21_get_bits_one(value_2.bits[i / 32], i % 32);
    if (bit_1 > bit_2) {
      result = 1;
      i = -1;
    } else if (bit_1 < bit_2) {
      result = 2;
      i = -1;
    } else {
      i--;
    }
  }
  return result;
}

// Берет два положительных децимала с одинаковой степенью и возвращает 1, если
// val_1 < val_2 и вовзаращет 0, если это неверно.
int positive_less(s21_decimal value_1, s21_decimal value_2) {
  int res = 1;
  for (int i = 2; i >= 0; i--) {
    unsigned val_1 = (unsigned)value_1.bits[i];
    unsigned val_2 = (unsigned)value_2.bits[i];
    res = val_1 < val_2;
    if (val_1 > val_2 || val_1 < val_2) {
      break;
    }
  }
  return res;
}

int s21_is_null(s21_decimal val) {
  int flag = 1;
  for (int i = 0; i <= 2; ++i) {
    flag = flag && (val.bits[i] == 0);
  }

  return flag;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  if (s21_get_exp(value_1) < MIN_POW || s21_get_exp(value_1) > MAX_POW)
    return FALSE;
  else if (s21_get_exp(value_2) < MIN_POW || s21_get_exp(value_2) > MAX_POW)
    return FALSE;

  int err = s21_normalize(&value_1, &value_2);
  int res = FALSE;
  if (err == 0) {
    int sign1 = s21_current_sign(value_1);
    int sign2 = s21_current_sign(value_2);

    if (s21_is_null(value_1) && s21_is_null(value_2)) {
      res = FALSE;

    } else if (sign1 != sign2) {
      if (sign1 != 0) {
        res = TRUE;
      } else {
        res = FALSE;
      }
    } else {
      if (sign1 != 0) {
        res = positive_less(value_2, value_1);
      } else {
        res = positive_less(value_1, value_2);
      }
    }
  }
  return res;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  if (s21_get_exp(value_1) < MIN_POW || s21_get_exp(value_1) > MAX_POW)
    return FALSE;
  else if (s21_get_exp(value_2) < MIN_POW || s21_get_exp(value_2) > MAX_POW)
    return FALSE;
  return s21_is_less(value_2, value_1);
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  if (s21_get_exp(value_1) < MIN_POW || s21_get_exp(value_1) > MAX_POW)
    return FALSE;
  else if (s21_get_exp(value_2) < MIN_POW || s21_get_exp(value_2) > MAX_POW)
    return FALSE;
  return !s21_is_less(value_1, value_2) && !s21_is_less(value_2, value_1);
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  if (s21_get_exp(value_1) < MIN_POW || s21_get_exp(value_1) > MAX_POW)
    return FALSE;
  else if (s21_get_exp(value_2) < MIN_POW || s21_get_exp(value_2) > MAX_POW)
    return FALSE;
  return !s21_is_equal(value_1, value_2);
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  if (s21_get_exp(value_1) < MIN_POW || s21_get_exp(value_1) > MAX_POW)
    return FALSE;
  else if (s21_get_exp(value_2) < MIN_POW || s21_get_exp(value_2) > MAX_POW)
    return FALSE;
  return s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  if (s21_get_exp(value_1) < MIN_POW || s21_get_exp(value_1) > MAX_POW)
    return FALSE;
  else if (s21_get_exp(value_2) < MIN_POW || s21_get_exp(value_2) > MAX_POW)
    return FALSE;
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}