#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (s21_get_exp(value) < MIN_POW || s21_get_exp(value) > MAX_POW ||
      result == NULL) {
    return CONV_ERR;
  }
  *result = value;
  s21_decimal value2 = {{1, 0, 0, 0}};
  s21_decimal result2 = {{0, 0, 0, 0}};
  if (s21_get_exp(value) > MIN_POW) {
    if (!s21_current_sign(*result)) {
      s21_truncate(*result, result);
    } else if (s21_current_sign(*result)) {
      s21_sub(*result, value2, &result2);
      s21_truncate(result2, result);
    }
  }
  return CONV_OK;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  if (s21_get_exp(value) < MIN_POW || s21_get_exp(value) > MAX_POW ||
      result == NULL)
    return CONV_ERR;
  if (s21_get_exp(value) == 0) {
    *result = value;
    return CONV_OK;
  }
  if (s21_get_exp(value)) {
    s21_decimal half = {{5, 0, 0, 0}};
    s21_set_exp(&half, 1);
    int a = 0, chet_nechet = 0;
    if (s21_current_sign(value) == 0) {
      chet_nechet = 0;
    } else if (s21_current_sign(value) != 0) {
      chet_nechet = 1;
      s21_change_sign(&value);
    }
    *result = value;
    s21_decimal value2 = value;
    s21_decimal value3 = {{0, 0, 0, 0}};
    s21_decimal result2 = {{0, 0, 0, 0}};
    a = s21_normalize_lower(&value2, 0);
    if (a == 0) {
      s21_add(value2, half, &value3);
    }

    if (s21_is_equal(value3, value) == TRUE) {
      if (!s21_check_bit(value2, 0)) {
        s21_truncate(value, result);
      }  // четное
      else if (s21_check_bit(value2, 0)) {
        s21_add(value, half, result);
      }  // нечетное
    } else if (s21_is_less(value, value3) == TRUE) {
      s21_truncate(value, result);
    } else if (s21_is_greater(value, value3) == TRUE) {
      s21_add(*result, ((s21_decimal){{1, 0, 0, 0}}), &result2);
      s21_truncate(result2, result);
    }
    if (chet_nechet == 1) {
      s21_change_sign(result);
    }
  }
  return CONV_OK;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (s21_get_exp(value) < MIN_POW || s21_get_exp(value) > MAX_POW ||
      result == NULL)
    return CONV_ERR;
  *result = value;
  int err = CONV_OK;
  if (s21_get_exp(value) > MIN_POW) {
    err = s21_normalize_lower(result, 0);
    if (err == 1) *result = (s21_decimal){{0, 0, 0, 0}};
  }
  return CONV_OK;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (s21_get_exp(value) < MIN_POW || s21_get_exp(value) > MAX_POW ||
      result == NULL)
    return CONV_ERR;
  *result = value;
  s21_change_sign(result);
  return CONV_OK;
}

// /**
//  * @brief формирует и возвращает число (0.5) в виде decimal
//  *
//  * @author Hubert Furr (hubertfu@student.21-school.ru)
//  * @return s21_decimal число (0.5)
//  */
// s21_decimal s21_decimal_get_zerofive(void) {
//     s21_decimal result = {{0x5, 0x0, 0x0, 0x10000}};

//     return result;
// }

//   s21_decimal one = {{1, 0, 0, 0}};
//   s21_decimal ten = {{1, 0, 0, 0}};
//   s21_decimal half = {{5, 0, 0, 0}};
//   int sign = s21_get_sign(value);
//   s21_set_exp(&half, 1);