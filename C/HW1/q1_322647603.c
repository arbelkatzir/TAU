#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

char sign(int num);
int absolute(int num);
int sum_digit_func(int num);
int num_digit_func(int num);

int main(void) {
  int num = 0;  // the user will enter a number here
  int base = 0; // the base the user will enter

  int absolute_num = 0;

  printf("Please enter an integer and a base:\n");
  scanf("%d %d", &num, &base);

  while (base != 8 && base != 10 && base != 16) {
    printf("Invalid base.\n");
    printf("Please enter a valid base [8,10,16]:\n");
    scanf("%d", &base);
  }

  printf("Here is some information about the given number:\n");

  // sign
  printf("It's sign is: %c\n", sign(num));

  // Decimal Representation of the absolute value in a formatted string
  absolute_num = absolute(num);
  printf("Decimal Representation of absolute value: %d\n", absolute_num);

  // Sum of digits in the decimal representation in a formatted string
  printf("The sum of digits is: %d\n", sum_digit_func(absolute_num));

  // Number of digits in the decimal representation in a formatted string
  printf("The number of digits is: %d\n", num_digit_func(absolute_num));

  // Representation of the absolute value in the given base with a formatted prefix
  if (base == 10) {
    printf("Base 10 representation was already computed above.\n");
  } else if (base == 8) {
    printf("0d%d = 0%o\n", absolute_num, absolute_num);
  } else {
    printf("0d%d = 0x%x\n", absolute_num, absolute_num);
  }

  return 0;
}

char sign(int num) {
  if (num < 0)
    return '-';
  else if (num > 0)
    return '+';
  else
    return '0';
}

int absolute(int num) {
  int abs_num = num;
  if (num < 0)
    abs_num = -num;
  return abs_num;
}

int sum_digit_func(int num) {
  int sum_of_digits = 0;
  int digit = 0;

  while (num > 0) {
    digit = num % 10;
    sum_of_digits += digit;
    num /= 10;
  }

  return sum_of_digits;
}

int num_digit_func(int num) {
  int num_of_digits = 0;

  if (num == 0)
    return 1;

  while (num > 0) {
    num /= 10;
    num_of_digits++;
  }

  return num_of_digits;
}
