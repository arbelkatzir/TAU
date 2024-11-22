#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void) {
	int grade;
	int invalid_grade_counter = 0;

	printf("Please enter your exam score (0-100):\n");
	scanf("%d", &grade);

	while (grade<0 || grade>100) {
		invalid_grade_counter++;
		if (invalid_grade_counter == 3) {
			printf("The user has inserted 3 consecutive times an invalid score.\nExiting the program!\n");
			return 1;
		}
		printf("Invalid input score:\nPlease enter a new exam score in the range 0 - 100:\n");
		scanf("%d", &grade);
	}

	switch (grade/10) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			printf("Grade: F\nYou failed, better luck next time!\n");
			break;
		case 5:
			printf("Grade: E\nYou barely passed - please review the material once again.\n");
			break;
		case 6:
			printf("Grade: D\nYou passed, but you need work harder next time!\n");
			break;
		case 7:
			printf("Grade: C\nNot bad! But you can do better..\n");
			break;
		case 8:
			printf("Grade: B\nGood job!There is room for improvement.\n");
			break;
		case 9:
		case 10:
			printf("Grade: A\nWell Done!\n");
			break;

	}
	return 0;
}