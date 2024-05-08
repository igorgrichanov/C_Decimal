#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_get_exp(value_1) < MIN_POW || s21_get_exp(value_1) > MAX_POW ||
      s21_get_exp(value_2) < MIN_POW || s21_get_exp(value_2) > MAX_POW) {
    return NO_VALID;
  }
  *result = (s21_decimal){{0, 0, 0, 0}};
  s21_set_bits_one(&result->bits[3], LOW_BIT_BORDER - 1, 0);
  int err = AR_OK;
  s21_decimal value_1_copy = value_1, value_2_copy = value_2;
  int error_norm = s21_normalize(&value_1, &value_2);
  if (error_norm) {
    error_norm =
        s21_post_normalize(&value_1, value_1_copy, &value_2, value_2_copy);
  }
  if (!error_norm) {
    if (s21_current_sign(value_1) == s21_current_sign(value_2)) {
      int exp_change = 0;
      s21_decimal_big value_1_big = {{0}}, value_2_big = {{0}},
                      result_big = {{0}};
      s21_convert_to_big(value_1, &value_1_big);
      s21_convert_to_big(value_2, &value_2_big);
      s21_add_big_decimal(value_1_big, value_2_big, &result_big);
      if (s21_check_big_to_convert(result_big)) {
        s21_convert_big_to_decimal(result_big, result);
      } else if (!s21_get_exp(value_1) && !s21_current_sign(value_1)) {
        err = AR_BIG;
      } else if (!s21_get_exp(value_1) && s21_current_sign(value_1)) {
        err = AR_SMALL;
      } else {
        s21_div_on_ten_big(&result_big);
        s21_convert_big_to_decimal(result_big, result);
        exp_change = 1;
      }
      if (s21_current_sign(value_1)) {
        s21_change_sign(result);
      }
      s21_set_exp(result, s21_get_exp(value_1) - exp_change);
    } else {
      if (s21_compare(value_1, value_2) == 2) {
        s21_switch_decimal(&value_1, &value_2);
      }
      s21_change_sign(&value_2);
      s21_sub(value_1, value_2, result);
    }
  } else {
    if (s21_get_exp(value_1) < s21_get_exp(value_2)) {
      *result = value_1;
    } else {
      *result = value_2;
    }
  }
  return err;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_get_exp(value_1) < MIN_POW || s21_get_exp(value_1) > MAX_POW ||
      s21_get_exp(value_2) < MIN_POW || s21_get_exp(value_2) > MAX_POW) {
    return NO_VALID;
  }
  *result = (s21_decimal){{0, 0, 0, 0}};
  s21_set_bits_one(&result->bits[3], LOW_BIT_BORDER - 1, 0);
  int err = AR_OK;
  s21_decimal value_1_copy = value_1, value_2_copy = value_2;
  int error_norm = s21_normalize(&value_1, &value_2);
  if (error_norm) {
    s21_change_sign(&value_2);
    error_norm =
        s21_post_normalize(&value_1, value_1_copy, &value_2, value_2_copy);
    s21_change_sign(&value_2);
  }
  if (!error_norm) {
    int change_sign = 0;
    if (s21_compare(value_1, value_2) == 2) {
      s21_switch_decimal(&value_1, &value_2);
      change_sign = 1;
    }
    if (s21_current_sign(value_1) == s21_current_sign(value_2)) {
      s21_subtraction(value_1, value_2, result);
      if ((s21_current_sign(value_1) && change_sign) ||
          (!change_sign && !s21_current_sign(value_1))) {
        change_sign = 0;
      } else {
        change_sign = 1;
      }
    } else {
      s21_change_sign(&value_2);
      err = s21_add(value_1, value_2, result);
    }
    if (change_sign) {
      s21_change_sign(result);
    }
    s21_set_exp(result, s21_get_exp(value_1));
  } else {
    if (s21_get_exp(value_1) < s21_get_exp(value_2)) {
      *result = value_1;
    } else {
      *result = value_2;
    }
  }
  return err;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_get_exp(value_1) < MIN_POW || s21_get_exp(value_1) > MAX_POW ||
      s21_get_exp(value_2) < MIN_POW || s21_get_exp(value_2) > MAX_POW) {
    return NO_VALID;
  }
  *result = (s21_decimal){{0, 0, 0, 0}};
  s21_decimal_big value_1_big = {{0}}, value_2_big = {{0}}, result_big = {{0}};
  s21_decimal zero = {{0}};
  int err = AR_OK, zero_count = 0;
  if ((s21_compare(value_1, zero) == 0) || (s21_compare(value_2, zero) == 0)) {
    *result = zero;
    zero_count = 1;
  }
  if (!zero_count) {
    s21_convert_to_big(value_1, &value_1_big);
    s21_convert_to_big(value_2, &value_2_big);
    int plus = 0;
    if (s21_current_sign(value_1) == s21_current_sign(value_2)) {
      plus = 1;
    }
    for (int i = 0; i < HIGH_BIT_BORDER; i++) {
      if (i > 0) {
        s21_left_shift_big(&value_2_big);
      }
      if (s21_get_bits_one(value_1_big.bits[i / LOW_BIT_BORDER],
                           i % LOW_BIT_BORDER)) {
        s21_add_big_decimal(result_big, value_2_big, &result_big);
      }
    }
    int result_exp = s21_get_exp(value_1) + s21_get_exp(value_2);
    err = s21_mul_post_normalize(result_exp, result_big, result);
    if (err) {
      if (!plus) {
        err = AR_SMALL;
      } else {
        err = AR_BIG;
      }
    }
    if (!plus) {
      s21_change_sign(result);
    }
  }
  return err;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_get_exp(value_1) < MIN_POW || s21_get_exp(value_1) > MAX_POW ||
      s21_get_exp(value_2) < MIN_POW || s21_get_exp(value_2) > MAX_POW) {
    return NO_VALID;
  }
  *result = (s21_decimal){{0, 0, 0, 0}};
  s21_decimal zero = {{0}};
  if (!s21_compare(value_2, zero)) {
    return ZERO_DIV;
  }
  int err = AR_OK;
  int error_norm = s21_normalize(&value_1, &value_2);
  if (error_norm) {
    err = s21_div_cases(value_1, value_2);
    if (err == AR_OK) {
      *result = zero;
    }
  } else {
    if (s21_check_bit(value_2, HIGH_BIT_BORDER - 1)) {
      if (s21_compare(value_1, value_2) != 2) {
        s21_decimal temp = {{1, 0, 0, 0}};
        s21_add(*result, temp, result);
      }
    } else {
      s21_division(value_1, value_2, result);
    }
    int res_exp = s21_div_of_rem(value_1, value_2, result);
    s21_set_exp(result, res_exp);
    if (s21_current_sign(value_1) != (s21_current_sign(value_2))) {
      s21_change_sign(result);
    }
  }
  return err;
}

int s21_addition(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
                 int *temp) {
  for (int i = 0; i < 3; i++) {
    s21_mantis_add(value_1.bits[i], value_2.bits[i], &result->bits[i], temp);
  }
  return *temp;
}

// только вычитаем мантисы
void s21_subtraction(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result) {
  int temp = 0;
  int credit_index = -1;
  for (int i = 0; i < HIGH_BIT_BORDER; i++) {
    int bit_1 =
        s21_get_bits_one(value_1.bits[i / LOW_BIT_BORDER], i % LOW_BIT_BORDER);
    int bit_2 =
        s21_get_bits_one(value_2.bits[i / LOW_BIT_BORDER], i % LOW_BIT_BORDER);
    if (credit_index == i) {
      bit_1 = 0;
      temp = 0;
    }
    if ((bit_1 + temp) >= bit_2) {
      s21_set_bits_one(&result->bits[i / LOW_BIT_BORDER], i % LOW_BIT_BORDER,
                       (bit_1 + temp - bit_2));
    } else {
      int j = i + 1;
      while (temp == 0) {
        if (s21_get_bits_one(value_1.bits[j / LOW_BIT_BORDER],
                             j % LOW_BIT_BORDER)) {
          credit_index = j;
          temp = 0b10;
        }
        j++;
      }
      s21_set_bits_one(&result->bits[i / LOW_BIT_BORDER], i % LOW_BIT_BORDER,
                       (bit_1 + temp - bit_2));
      temp = 1;
    }
  }
}

int s21_mul_post_normalize(int result_exp, s21_decimal_big result_big,
                           s21_decimal *result) {
  int err = 0;
  if ((result_exp > MAX_POW) || (!s21_check_big_to_convert(result_big))) {
    while (result_exp > MAX_POW) {
      s21_div_on_ten_big(&result_big);
      result_exp--;
    }
    while (!s21_check_big_to_convert(result_big) && (result_exp > MIN_POW)) {
      s21_div_on_ten_big(&result_big);
      result_exp--;
    }
    if (s21_check_big_to_convert(result_big)) {
      s21_convert_big_to_decimal(result_big, result);
      err = s21_set_exp(result, result_exp);
    } else {
      err = 1;
    }
  } else {
    s21_convert_big_to_decimal(result_big, result);
    err = s21_set_exp(result, result_exp);
  }
  return err;
}

// Деление мантис без остатка
void s21_division(s21_decimal src, s21_decimal delim, s21_decimal *result) {
  s21_decimal copy_delim = delim;
  if (s21_compare(src, delim) == 2) {
    return;
  } else {
    int i = 0;
    s21_decimal two = {{0b1, 0, 0, 0}};
    while (i >= 0) {
      int compare = 0;
      if (s21_check_bit(copy_delim, HIGH_BIT_BORDER - 1)) {
        compare = -1;
      }
      if (i > 0 && compare != -1) {
        s21_left_shift(&copy_delim);
      }
      if (compare != -1) {
        compare = s21_compare(src, copy_delim);
      }
      if (compare == 1) {
        s21_left_shift(&two);
        i++;
      } else if (compare == 0) {
        s21_add(*result, two, result);
        i = -1;
        s21_subtraction(src, copy_delim, &src);
      } else {
        s21_right_shift(&two);
        if (compare != -1) {
          s21_right_shift(&copy_delim);
        }
        s21_add(*result, two, result);
        i = -1;
        s21_subtraction(src, copy_delim, &src);
        s21_division(src, delim, result);
      }
    }
  }
}

int s21_div_of_rem(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  s21_decimal temp = {{0}};
  s21_decimal remainder = {{0}};
  s21_decimal zero = {{0}};
  s21_mul(*result, value_2, &temp);
  s21_subtraction(value_1, temp, &remainder);
  int flag = 0;
  int res_exp = 0;
  while (!flag) {
    if (s21_compare(remainder, zero) == 0) {
      flag = 1;
    }
    if (!flag) {
      flag = s21_mul_on_ten(&remainder);
    }
    if (!flag) {
      flag = s21_mul_on_ten(result);
    }
    if (!flag) {
      res_exp++;
    }
    if (res_exp == 28) {
      flag = 1;
    }
    if (!flag) {
      if (s21_compare(remainder, value_2) != 2) {
        temp = (s21_decimal){{0, 0, 0, 0}};
        s21_division(remainder, value_2, &temp);
        s21_add(*result, temp, result);
        s21_mul(temp, value_2, &temp);
        s21_subtraction(remainder, temp, &remainder);
      }
    }
  }
  return res_exp;
}

int s21_div_cases(s21_decimal value_1, s21_decimal value_2) {
  int err = 0;
  if (s21_get_exp(value_1) < (s21_get_exp(value_2))) {
    if (s21_current_sign(value_1) == s21_current_sign(value_2)) {
      err = AR_BIG;
    } else {
      err = AR_SMALL;
    }
  }
  return err;
}

// суммирование в одной мантисе
void s21_mantis_add(int value_1, int value_2, int *result, int *temp) {
  for (int i = 0; i < LOW_BIT_BORDER; i++) {
    int bit_1 = s21_get_bits_one(value_1, i);
    int bit_2 = s21_get_bits_one(value_2, i);
    int sum = *temp + bit_1 + bit_2;
    s21_set_bits_one(result, i, s21_get_bits_one(sum, 0));
    *temp = s21_get_bits_one(sum, 1);
  }
}

int s21_post_normalize(s21_decimal *value_1, s21_decimal value_1_cp,
                       s21_decimal *value_2, s21_decimal value_2_cp) {
  int error_norm = 1;
  if (s21_get_exp(*value_1) > s21_get_exp(*value_2)) {
    s21_switch_decimal(value_1, value_2);
    s21_switch_decimal(&value_1_cp, &value_2_cp);
  }
  if ((s21_get_exp(value_1_cp) == 0 && s21_get_exp(*value_2) == 1)) {
    if (s21_common_banking_round(*value_1, *value_2, value_2_cp)) {
      value_2->bits[0] = 0b1;
    } else {
      value_2->bits[0] = 0b0;
    }
    s21_set_exp(value_2, s21_get_exp(*value_1));
    error_norm = 0;
  } else if (s21_get_exp(*value_1) + 1 == s21_get_exp(*value_2)) {
    if (s21_current_sign(*value_1)) {
      s21_set_bits_one(&value_2->bits[1], 0, 1);
    }
    if (s21_current_sign(*value_2)) {
      s21_set_bits_one(&value_2->bits[1], 1, 1);
    }
    if (s21_common_round(*value_2)) {
      value_2->bits[0] = 0b1;
    } else {
      value_2->bits[0] = 0b0;
    }
    s21_set_bits_one(&value_2->bits[1], 0, 0);
    s21_set_bits_one(&value_2->bits[1], 1, 0);
    s21_set_exp(value_2, s21_get_exp(*value_1));
    error_norm = 0;
  }
  return error_norm;
}

int s21_common_round(s21_decimal src) {
  int res = 0;
  int number = 0;
  for (int i = 0; i < 4; i++) {
    number += s21_check_bit(src, i);
  }
  if (number > 5) {
    res = 1;
  }
  if (number == 5) {
    if (s21_get_bits_one(src.bits[1], 0) == s21_get_bits_one(src.bits[1], 1)) {
      res = 1;
    }
  }
  return res;
}

int s21_common_banking_round(s21_decimal value_1, s21_decimal value_2,
                             s21_decimal value_2_copy) {
  int res = 0;
  int number = 0;
  for (int i = 0; i < 4; i++) {
    number += s21_check_bit(value_2, i);
  }
  if (number > 5) {
    res = 1;
  } else if (number == 5) {
    s21_normalize_upper(&value_2, s21_get_exp(value_2_copy));
    if (s21_compare(value_2_copy, value_2) == 1) {
      res = 1;
    } else {
      s21_decimal value_1_ten = {{0}};
      s21_decimal value_1_copy = value_1;
      int err = s21_div_on_ten(&value_1);
      if (err == 2) {
        s21_set_exp(&value_1, 1);
        s21_div_on_ten(&value_1);
      }
      s21_mul_on_ten(&value_1);
      s21_set_exp(&value_1, s21_get_exp(value_1_copy));
      s21_subtraction(value_1_copy, value_1, &value_1_ten);
      number = 0;
      for (int i = 0; i < 4; i++) {
        number += s21_check_bit(value_1_ten, i);
      }
      if (number % 2 != 0) {
        res = 1;
      }
    }
  }
  return res;
}

// возвращает 0 при успехе, или 1 при неудаче (одно из чисел слишком мало)
int s21_normalize(s21_decimal *value_1, s21_decimal *value_2) {
  int exp_1 = s21_get_exp(*value_1);
  int exp_2 = s21_get_exp(*value_2);
  s21_decimal temp_1 = *value_1;
  s21_decimal temp_2 = *value_2;
  int change = 0;
  int no_result = 1;
  if (exp_1 == exp_2) {
    no_result = 0;
  } else if (exp_2 > exp_1) {
    s21_switch_decimal(&temp_1, &temp_2);
    exp_1 = exp_2;
    change = 1;
  }
  if (no_result) {
    no_result = s21_normalize_upper(&temp_2, exp_1);
  }
  if (no_result) {
    no_result = s21_normalize_lower(&temp_1, s21_get_exp((temp_2)));
  }
  if (change) {
    *value_1 = temp_2;
    *value_2 = temp_1;
  } else {
    *value_1 = temp_1;
    *value_2 = temp_2;
  }
  return no_result;
}

// 0-при успешной нормализации, 1 при переполнении
int s21_normalize_upper(s21_decimal *src, int index) {
  int current_exp = s21_get_exp(*src);
  int error = 0;
  while (error == 0 && (current_exp < index)) {
    for (int i = HIGH_BIT_BORDER - 1; i >= HIGH_BIT_BORDER - 3; i--) {
      int bit = s21_check_bit(*src, i);
      if (bit != 0) {
        error = 1;
      }
    }
    if (!error) {
      error = s21_mul_on_ten(src);
    }
    if (!error) {
      current_exp++;
    }
  }
  s21_set_exp(src, current_exp);
  return error;
}

// 0-при успешной нормализации, 1 при невозможности
int s21_normalize_lower(s21_decimal *src, int index) {
  int err = 0;
  int current_exp = s21_get_exp(*src);
  while (current_exp > index && err == 0) {
    err = s21_div_on_ten(src);
    current_exp = s21_get_exp(*src);
  }
  return err;
}

// без остатка
// 0 если прошло успешно
// 1 если вернется 0 в мантисе
// 2 если следующая экспонента будет равно -1
int s21_div_on_ten(s21_decimal *src) {
  int plus = s21_current_sign(*src);
  s21_decimal ten = {{0b1010, 0, 0, 0}};
  s21_decimal result = {{0}};
  int err = 0;
  int exp = s21_get_exp(*src);
  if (exp == 0) {
    err = 2;
  } else if (s21_compare(*src, ten) == 2) {
    err = 1;
  } else {
    s21_division(*src, ten, &result);
    *src = result;
    s21_set_exp(src, exp - 1);
    if (plus) {
      s21_change_sign(src);
    }
  }
  return err;
}

// возвращает 1 при невозможности умножения из за переполнения
int s21_mul_on_ten(s21_decimal *src) {
  int temp = 0;
  int plus = s21_current_sign(*src);
  s21_decimal result = {0};
  s21_decimal ten = {{0b1010, 0, 0, 0}};
  if (s21_check_bit(*src, HIGH_BIT_BORDER - 1) ||
      s21_check_bit(*src, HIGH_BIT_BORDER - 2) ||
      s21_check_bit(*src, HIGH_BIT_BORDER - 3)) {
    temp = 1;
  }
  if (!temp) {
    for (int i = 0; i < HIGH_BIT_BORDER - 3; i++) {
      if (i > 0) {
        s21_left_shift(&ten);
      }
      if (s21_get_bits_one(src->bits[i / LOW_BIT_BORDER], i % LOW_BIT_BORDER)) {
        s21_addition(result, ten, &result, &temp);
      }
    }
  }
  if (!temp) {
    *src = result;
    if (plus) {
      s21_change_sign(src);
    }
  }
  return temp;
}