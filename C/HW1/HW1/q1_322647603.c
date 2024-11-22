//#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//
//char sign(int num);
//int absolute(int num);
//int sum_digit_func(int num);
//int num_digit_func(int num);
//
//
//
//int main(void)
//{
//	int num; // the user will enter a umber here
//	int base; // the base the user will enter
//
//	char sign_chr;
//	int abs_num;
//	int sum_of_digit;
//	int num_of_digits;
//
//	
//	printf("Please enter an integer and a base:\n");
//	scanf("%d %d", &num, &base);
//	
//	
//	while (base != 8 && base != 10 && base != 16){
//		printf("Invalid base\n");
//		printf("Please enter a valid base [8,10,16]:\n");
//		scanf("%d", &base);
//	}
//
//	printf("Here is some information about the given number:\n");
//	
//	// sign
//	sign_chr = sign(num);
//	printf("It’s sign is: %c\n", sign_chr);
//	
//
//	// Decimal Representation of the absolute value in a formatted string
//	abs_num = absolute(num);
//	printf("Decimal Representation of absolute value: %d\n", abs_num);
//
//	// Sum of digits in the decimal representation in a formatted string
//	sum_of_digit = sum_digit_func(num);
//	printf("The sum of digits is: %d\n", sum_of_digit);
//
//	// Number of digits in the decimal representation in a formatted string :
//	num_of_digits = num_digit_func(num);
//	printf("The number of digits is: %d\n", num_of_digits);
//
//	// Representation of the absolute value in the given base with a formatted prefix:
//	if (base == 10) {
//		printf("Base 10 representation was already computed above.\n");
//	}
//	else if (base == 8) {
//		printf("0d%d = 0%o\n", abs_num, abs_num);
//	}
//	else {
//		printf("0d%d = 0x%x\n", abs_num, abs_num);
//	}
//
//
//	return 0;
//}
//
//char sign(int num) {
//	if (num < 0)
//		return '-';
//	else if (num > 0)
//		return '+';
//	else
//		return '0';
//}
//
//int absolute(int num) {
//	int abs_num = num;
//	if (num < 0)
//		abs_num = -num;
//	return abs_num;
//}
//
//
//int sum_digit_func(int num) {
//	num = absolute(num);
//	int sum_of_digits = 0;
//	int digit;
//
//	while (num > 0) {
//		digit = num % 10; 
//		sum_of_digits += digit;
//		num /= 10; 
//	}
//	return sum_of_digits;
//}
//
//int num_digit_func(int num) {
//	num = absolute(num);
//	int num_of_digits = 0;
//
//	if (num == 0)
//		return 1;
//
//	while (num > 0) {
//		num /= 10;
//		num_of_digits++;
//	}
//	return num_of_digits;
//}