#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_assign_0_to_decimal(dst);
  if (src < 0) {
    s21_change_sign(dst);
    if (src != __INT32_MAX__ * (-1) - 1)
      src = (-1) * src;
    else
      src = (-1) * src - 1;
  };
  dst->bits[0] = src;
  return CONV_OK;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_assign_0_to_decimal(dst);
  if (dst == NULL || (src != src) || (src == POS_INF) || (src == NEG_INF))
    return CONV_ERR;
  else if (src <= MIN_DECIMAL || src >= MAX_DECIMAL ||
           (src <= 1e-28 && src >= 0))
    return CONV_ERR;

  if (src < 0.0) s21_change_sign(dst);
  double double_src = (double)src;
  double_src = fabsl(double_src);
  int err = CONV_OK, scale = 0;
  for (; !((int)double_src) && scale < MAX_POW; double_src *= 10, scale++)
    ;
  for (int i = 0; double_src < MAX_DECIMAL && scale < MAX_POW &&
                  i < FLOAT_ACCURACY && double_src < powl(10, 6);
       double_src *= 10.0, scale++, i++)
    ;
  double_src = round(double_src);
  if (scale > MAX_POW) err = CONV_ERR;
  if (!err) {
    for (int i = 0; double_src > powl(10.0, -1 * (FLOAT_ACCURACY + 1)) &&
                    i < HIGH_BIT_BORDER;
         i++) {
      double_src = floorl(double_src) / 2;
      if (double_src - floorl(double_src) >
          powl(10.0, -1 * (FLOAT_ACCURACY + 1)))
        s21_set_bit(dst, i);
    }
    s21_set_exp(dst, scale);
  }
  return err;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL) return CONV_ERR;
  *dst = 0;
  if (s21_get_exp(src) < MIN_POW || s21_get_exp(src) > MAX_POW) return CONV_ERR;
  int err = CONV_OK;
  if (s21_get_exp(src)) {
    s21_decimal truncated_src = {{0, 0, 0, 0}};
    err = s21_truncate(src, &truncated_src);
    if (!err) src = truncated_src;
  }
  if (s21_check_bit(src, 31) || src.bits[1] || src.bits[2]) err = 1;
  if (!err) {
    if (s21_current_sign(src)) {
      if (src.bits[0] == __INT32_MAX__)
        *dst = src.bits[0] * (-1) - 1;
      else
        *dst = src.bits[0] * (-1);
    } else
      *dst = src.bits[0];
  }
  return err ? CONV_ERR : CONV_OK;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL) return CONV_ERR;
  *dst = 0.0;
  if (s21_get_exp(src) < MIN_POW || s21_get_exp(src) > MAX_POW) return CONV_ERR;
  double tmp = 0.0;
  for (int i = 0; i < HIGH_BIT_BORDER; i++) {
    if (s21_check_bit(src, i)) {
      tmp += pow(2.0, i);
    }
  }
  int exp = s21_get_exp(src);
  while (exp) {
    tmp /= 10;
    exp--;
  }
  if (s21_current_sign(src)) tmp *= -1;
  *dst = (float)tmp;
  return CONV_OK;
}