#include "s21_decimal.h"

int s21_check_bit_big(s21_decimal_big src, int bit) {
  int num_int = bit / LOW_BIT_BORDER;
  int num_bit = bit % LOW_BIT_BORDER;
  return (src.bits[num_int] & (1 << num_bit));
}

void s21_add_big_decimal(s21_decimal_big value_1, s21_decimal_big value_2,
                         s21_decimal_big *result) {
  int temp = 0;
  for (int i = 0; i < 7; i++) {
    s21_mantis_add(value_1.bits[i], value_2.bits[i], &result->bits[i], &temp);
  }
}

void s21_sub_big_decimal(s21_decimal_big value_1, s21_decimal_big value_2,
                         s21_decimal_big *result) {
  int temp = 0;
  int credit_index = -1;
  for (int i = 0; i < BIG_BIT_BORDER; i++) {
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

// возвращает 1 если можно конвертировать, 0 если нельзя
int s21_check_big_to_convert(s21_decimal_big src) {
  int ready = 1;
  int flag = 1;
  int i = BIG_BIT_BORDER - 1;
  while (flag == 1 && i >= HIGH_BIT_BORDER) {
    if (s21_get_bits_one(src.bits[i / LOW_BIT_BORDER], i % LOW_BIT_BORDER)) {
      ready = 0;
      flag = 0;
    }
    i--;
  }
  while (flag == 1 && i >= 0) {
    ready = 0;
    if (s21_get_bits_one(src.bits[i / LOW_BIT_BORDER], i % LOW_BIT_BORDER)) {
      ready = 1;
      flag = 0;
    }
    i--;
  }
  return ready;
}

void s21_left_shift_big(s21_decimal_big *src) {
  int bits[] = {0, 0, 0, 0, 0};
  for (int i = 0; i < 5; i++) {
    bits[i] = s21_get_bits_one(src->bits[i], LOW_BIT_BORDER * (i + 1) - 1);
  }
  for (int i = 0; i < 6; i++) {
    src->bits[i] <<= 1;
  }
  for (int i = 0; i < 5; i++) {
    if (bits[i]) {
      s21_set_bits_one(&src->bits[i + 1], 0, 1);
    }
  }
}

void s21_right_shift_big(s21_decimal_big *src) {
  int bits[] = {0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 6; i++) {
    bits[i] = s21_get_bits_one(src->bits[i + 1], 0);
  }
  for (int i = 0; i < 6; i++) {
    src->bits[i] >>= 1;
  }
  for (int i = 0; i < 6; i++) {
    s21_set_bits_one(&src->bits[i], LOW_BIT_BORDER - 1, bits[i]);
  }
}

int s21_compare_big(s21_decimal_big value_1, s21_decimal_big value_2) {
  int result = 0;
  int i = 191;
  while (i >= 0) {
    int bit_1 =
        s21_get_bits_one(value_1.bits[i / LOW_BIT_BORDER], i % LOW_BIT_BORDER);
    int bit_2 =
        s21_get_bits_one(value_2.bits[i / LOW_BIT_BORDER], i % LOW_BIT_BORDER);
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

void s21_convert_to_big(s21_decimal src, s21_decimal_big *target) {
  target->bits[0] = src.bits[0];
  target->bits[1] = src.bits[1];
  target->bits[2] = src.bits[2];
  target->bits[6] = src.bits[3];
}

void s21_convert_big_to_decimal(s21_decimal_big src, s21_decimal *target) {
  for (int i = 0; i < 3; i++) {
    target->bits[i] = src.bits[i];
  }
}

void s21_div_on_ten_big(s21_decimal_big *src) {
  s21_decimal_big ten = {{0b1010, 0, 0, 0}};
  s21_decimal_big result = {{0}};
  s21_div_big_decimal(*src, ten, &result);
  *src = result;
}

void s21_div_big_decimal(s21_decimal_big value_1, s21_decimal_big delim,
                         s21_decimal_big *result) {
  s21_decimal_big copy_delim = delim;
  if (s21_compare_big(value_1, delim) == 2) {
    return;
  } else {
    int i = 0;
    s21_decimal_big two = {{0b1, 0, 0, 0, 0, 0, 0}};
    while (i >= 0) {
      int compare = 0;
      if (s21_check_bit_big(copy_delim, BIG_BIT_BORDER - 1)) {
        compare = -1;
      }
      if (i > 0 && compare != -1) {
        s21_left_shift_big(&copy_delim);
      }
      if (compare != -1) {
        compare = s21_compare_big(value_1, copy_delim);
      }
      if (compare == 1) {
        s21_left_shift_big(&two);
        i++;
      } else if (compare == 0) {
        s21_add_big_decimal(*result, two, result);
        i = -1;
        s21_sub_big_decimal(value_1, copy_delim, &value_1);
      } else {
        s21_right_shift_big(&two);
        if (compare != -1) {
          s21_right_shift_big(&copy_delim);
        }
        s21_add_big_decimal(*result, two, result);
        i = -1;
        s21_sub_big_decimal(value_1, copy_delim, &value_1);
        s21_div_big_decimal(value_1, delim, result);
      }
    }
  }
}