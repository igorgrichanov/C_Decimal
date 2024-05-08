#ifndef S21_DECIMAL
#define S21_DECIMAL

#include <math.h>
#include <stdlib.h>

#define MAX_DECIMAL powl(2.0, 96)
#define MIN_DECIMAL -1 * MAX_DECIMAL
#define MAX_POW 28
#define MIN_POW 0
#define LOW_BIT_BORDER 32
#define MIDDLE_BIT_BORDER 64
#define HIGH_BIT_BORDER 96
#define BIG_BIT_BORDER 192
#define FLOAT_ACCURACY 7
#define BYTE_MASK 0xFF
#define MANTISSA_MASK 0x7FFFFF
#define POS_INF 1.0 / 0.0
#define NEG_INF -1.0 / 0.0
#define DECIMAL_MAX 79228162514264337593543950335.0
#define DECIMAL_MIN -1 * DECIMAL_MAX
#define S21_BIT_MAX 0xFFFFFFFF
#define FALSE 0
#define TRUE 1

#define CONV_OK 0
#define CONV_ERR 1

#define AR_OK 0
#define AR_BIG 1
#define AR_SMALL 2
#define ZERO_DIV 3
#define NO_VALID 4

typedef struct s21_decimal {
  int bits[4];
} s21_decimal;

typedef struct s21_decimal_big {
  int bits[7];
} s21_decimal_big;

enum s21_decimal_type { DECIMAL, DECIMAL_BIG };

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

void s21_change_sign(s21_decimal *src);
int s21_current_sign(s21_decimal src);
int s21_get_exp(s21_decimal src);
int s21_set_exp(s21_decimal *src, int exp);
int s21_check_bit(s21_decimal src, int bit);
void s21_set_bit(s21_decimal *src, int bit);
void s21_assign_0_to_decimal(s21_decimal *src);

/* ------ работа с битами ------ */
void s21_set_bits_one(int *number, int index, int bit);
int s21_get_bits_one(int number, int index);
void s21_right_shift(s21_decimal *src);
void s21_left_shift(s21_decimal *src);

/* ------ сложение ------ */
void s21_mantis_add(int value_1, int value_2, int *result, int *temp);
int s21_addition(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
                 int *temp);

/* ------ вычитание ------ */
void s21_subtraction(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result);

/* ------ умножение ------ */

int s21_mul_post_normalize(int result_exp, s21_decimal_big result_big,
                           s21_decimal *result);

/* ------ деление ----- */
int s21_div_cases(s21_decimal value_1, s21_decimal value_2);
void s21_division(s21_decimal src, s21_decimal delim, s21_decimal *result);
int s21_div_of_rem(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);

/* ------  нормализация ------ */
int s21_normalize_upper(s21_decimal *src, int index);
int s21_normalize_lower(s21_decimal *src, int index);
int s21_mul_on_ten(s21_decimal *src);
int s21_div_on_ten(s21_decimal *src);
int s21_normalize(s21_decimal *value_1, s21_decimal *value_2);
int s21_post_normalize(s21_decimal *value_1, s21_decimal value_1_cp,
                       s21_decimal *value_2, s21_decimal value_2_cp);

/* -----  big_decimal ----- */

int s21_check_bit_big(s21_decimal_big src, int bit);
void s21_add_big_decimal(s21_decimal_big value_1, s21_decimal_big value_2,
                         s21_decimal_big *result);
void s21_sub_big_decimal(s21_decimal_big value_1, s21_decimal_big value_2,
                         s21_decimal_big *result);
void s21_div_big_decimal(s21_decimal_big value_1, s21_decimal_big delim,
                         s21_decimal_big *result);
int s21_compare_big(s21_decimal_big value_1, s21_decimal_big value_2);
void s21_left_shift_big(s21_decimal_big *src);
void s21_right_shift_big(s21_decimal_big *src);
void s21_convert_to_big(s21_decimal src, s21_decimal_big *target);
void s21_convert_big_to_decimal(s21_decimal_big src, s21_decimal *target);
int s21_check_big_to_convert(s21_decimal_big src);
void s21_div_on_ten_big(s21_decimal_big *src);

/* вспомогательные */
int s21_compare(s21_decimal value_1, s21_decimal value_2);
int s21_common_round(s21_decimal src);
void s21_switch_decimal(s21_decimal *value_1, s21_decimal *value_2);
int s21_common_banking_round(s21_decimal value_1, s21_decimal value_2,
                             s21_decimal value_2_copy);

#endif
