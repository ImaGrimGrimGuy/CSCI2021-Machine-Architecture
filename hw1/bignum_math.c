
/**************************
 * bignum_math.c -- an outline for CLab1
 *
 * orginially written by Andy Exley
 * modified by Daniel Hartmann
 **************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bignum_math.h"

/*----------------------------------------------------------------------------*/

/*
 * Returns true if the given char is a digit from 0 to 9
 */
bool is_digit(char c) {
	return c >= '0' && c <= '9';
}

/*----------------------------------------------------------------------------*/

/*
 * Returns true if lower alphabetic character
 */
bool is_lower_alphabetic(char c) {
	return c >= 'a' && c <= 'z';
}

/*----------------------------------------------------------------------------*/

/*
 * Returns true if upper alphabetic character
 */
bool is_upper_alphabetic(char c) {
	return c >= 'A' && c <= 'Z';
}

/*----------------------------------------------------------------------------*/

/*
 * Convert a string to an integer
 * returns 0 if it cannot be converted.
 */
int string_to_integer(char* input) {
	int result = 0;
	int length = strlen(input);
    int num_digits = length;
	int sign = 1;

	int i = 0;
    int factor = 1;

    if (input[0] == '-') {
		num_digits--;
		sign = -1;
    }

	for (i = 0; i < num_digits; i++, length--) {
		if (!is_digit(input[length-1])) {
			return 0;
		}
		if (i > 0) factor*=10;
		result += (input[length-1] - '0') * factor;
	}

    return sign * result;
}

/*----------------------------------------------------------------------------*/

/*
 * Returns true if the given base is valid.
 * that is: integers between 2 and 36
 */
bool valid_base(int base) {
	if(!(base >= 2 && base <= 36)) {
		return false;
	}
	return true;
}

/*----------------------------------------------------------------------------*/

/*
 * TODO
 * Returns true if the given string (char array) is a valid input,
 * that is: digits 0-9, letters A-Z, a-z
 * and it should not violate the given base and should not handle negative numbers
 */
bool valid_input(char* input, int base) {
	if (input[0] == '-')
	{
		return false;
	}

	/*check valid characters for base 2 to 10*/
	if (base >= 2 && base <= 10)
	{
		int i;
		for (i = 0; i < strlen(input) ; i++)
		{
			if (!(input[i] >= '0' && input[i] <= ('0' + (base-1)) ))
			{
				return false;
			}
		}
	}

	/*check valid characters for base 11 to 36*/
	if (base >= 11 && base <= 36)
	{
		int i;
		for (i = 0; i < strlen(input); i++)
		{
			/*check that all characters are within the ranges of numbers, or the
			appropriate ranges of the alphabet*/
			if (!((input [i] >= '0' && input[i] <= '9' )|| (input[i] >= 'A' && input[i] <= ('Z' - (36-base))) || (input[i] >= 'a' && input[i] <= ('z'- (36-base)))))
			{
				return false;
			}
		}
	}

	return true;
}

/*----------------------------------------------------------------------------*/
/*
 * converts from an array of characters (string) to an array of integers
 */
int* string_to_integer_array(char* str) {
	int* result;
	int i, str_offset = 0;
		result = malloc((strlen(str) + 1) * sizeof(int));
		result[strlen(str)] = -1;
	for(i = str_offset; str[i] != '\0'; i++) {
		if(is_digit(str[i])) {
			result[i - str_offset] = str[i] - '0';
		} else if (is_lower_alphabetic(str[i])) {
			result[i - str_offset] = str[i] - 'a' + 10;
		} else if (is_upper_alphabetic(str[i])) {
			result[i - str_offset] = str[i] - 'A' + 10;
		} else {
			printf("I don't know how got to this point!\n");
		}
	}
	return result;
}

/*----------------------------------------------------------------------------*/

/*
 * finds the length of a bignum...
 * simply traverses the bignum until a negative number is found.
 */
int bignum_length(const int* num) {
	int len = 0;
	while(num[len] >= 0) { len++; }
	return len;
}

/*----------------------------------------------------------------------------*/

/*
 * TODO
 * Prints out a bignum using digits and lower-case characters
 * Current behavior: prints integers
 * Expected behavior: prints characters
 */
 void bignum_print(int* num) {
  int start = 0;
  if(num == NULL) { return; }

  /* Negative numbers terminate with -2, positive with -1 */
  int sign = bignum_length(num);
 	if (num[sign] == -2) {
 	 printf("-");
  }
	//trim off any leading zeros//
  while (num[start] == 0) {
 	 start++;
  }


  /* Then, print each digit */
  for(int i = start; i < sign; i++) {
 		if (num[i] >= 0 && num[i] < 10){
 		 printf("%d",num[i]);
 	 }
 	 else{
 		 printf("%c",(num[i]-10)+'a');
 		}
 	 }
  printf("\n");
 }

/*----------------------------------------------------------------------------*/

/*
 *	Helper for reversing the result that we built backward.
 *  see add(...) below
 */
void reverse(int* num) {
	int i, len = bignum_length(num);
	for(i = 0; i < len/2; i++) {
		int temp = num[i];
		num[i] = num[len-i-1];
		num[len-i-1] = temp;
	}
}

/*----------------------------------------------------------------------------*/
/*goes through a list and checks elements to see which is greater!*/
bool greaterthan(const int* input1, const int* input2) {
	int len1 = bignum_length(input1);
	int len2 = bignum_length(input2);
    int num1, num2;
  //if the lengths are different then that's all you need to know//
	if (len1 > len2) {
		return true;
	}
	else if (len1 < len2) {
		return false;
	}
	//look for the first number in input1 greater than one in input2//
	else {
		bool tic = false;
		for(int i = 0 ; i < len1 ; i++) {
			if (input1[i] > input2[i]){
				tic = true;
			}
		}
			return tic;
		}
	}

/*----------------------------------------------------------------------------*/
/*
 * used to add two numbers with the same sign
 * GIVEN FOR GUIDANCE
 */
int* add(int* input1, int* input2, int base) {
	int len1 = bignum_length(input1);
	int len2 = bignum_length(input2);
	int resultlength = ((len1 > len2)? len1 : len2) + 2;
	int* result = (int*) malloc (sizeof(int) * resultlength);
	int r = 0;
	int carry = 0;
	int sign = input1[len1];
    int num1, num2;

	len1--;
	len2--;

	while (len1 >= 0 || len2 >= 0) {
        if (len1 >= 0) {
            num1 = input1[len1];
        } else {
            num1 = 0;
        }

        if (len2 >= 0) {
            num2 = input2[len2];
        } else {
            num2 = 0;
        }
		result[r] = (num1 + num2 + carry) % base;
		carry = (num1 + num2 + carry) / base;
		len1--;
		len2--;
		r++;
	}
	if (carry > 0) {
        result[r] = carry;
        r++;
    }
	result[r] = sign;
	reverse(result);
	return result;
}

/*----------------------------------------------------------------------------*/

int* subtract(int* input1, int* input2, int base) {
  /*initialize a memory block for the funtion*/
  int len1 = bignum_length(input1);
	int len2 = bignum_length(input2);
	int resultlength = ((len1 < len2) ? len1 : len2);
	int* result = (int*)malloc(sizeof(int) * resultlength);
	int r = 0;
	int carry = 0;
	int num1, num2;
  bool tic = false;

	len1--;
	len2--;

//flip results if subtraction will result in a negative number,//
//make a note of that//
if (!greaterthan(input1, input2)) {
  int* temp = input1;
  input1 = input2;
  input2 = temp;
	int temp2 = len1;
	len1 = len2;
	len2 = temp2;

  tic = true;
}

	while (len1 >= 0 || len2 >= 0) {
				if (len1 >= 0) {
						num1 = input1[len1];
				} else {
						num1 = 0;
				}

				if (len2 >= 0) {
						num2 = input2[len2];
				} else {
						num2 = 0;
				}
    //this simulates doing math on paper, you check if you need to carry, and//
		//if so, you add a base and subtract one from the next one up//
    if ((num1 - carry) >= num2) {
		result[r] = (num1 - num2 - carry) % base;
    carry = 0;
		}
		else {
			result[r] = (base + num1 - num2 - carry) % base;
			carry = 1;
		}
	len1--;
	len2--;
	r++;
  }
  //here is where I keep track of negatives with the note I took earlier//
  if (tic) {
    result[r] = -2;
  }
  else{
    result[r] = -1;
  }
  reverse(result);
  return result;
  }

/*----------------------------------------------------------------------------*/
/*
 * TODO
 * This function is where you will write the code that performs the heavy lifting,
 * actually performing the calculations on input1 and input2.
 * Return your result as an array of integers.
 * HINT: For better code structure, use helper functions.
 */
int* perform_math(int* input1, int* input2, char op, int base) {

	/*
	 * this code initializes result to be large enough to hold all necessary digits.
	 * if you don't use all of its digits, just put a -1 at the end of the number.
	 * you may omit this result array and create your own.
     */

    int len1 = bignum_length(input1);
    int len2 = bignum_length(input2);
	int resultlength = ((len1 > len2)? len1 : len2) + 1;
	int* result = (int*) malloc (sizeof(int) * resultlength);

  /*adition*/
	if(op == '+') {
		result = add(input1, input2, base);
	}
	/*subtraction*/
	if (op == '-') {
		result = subtract(input1, input2, base);
	}
	/*check the statement, print answer, and exit*/
	if (op == '>') {
		if (greaterthan(input1, input2)) {
			printf("Result: true\n");
			exit(0);
		}
		else{
			printf("Result: false\n");
			exit(0);
		}
	}
	/*just flip the arguments*/
	if (op == '<') {
		if (greaterthan(input2, input1)) {
			printf("Result: true\n");
			exit(0);
		}
		else {
			printf("Result: false\n");
			exit(0);
		}
	}
	/*if B<=A<=B, then A=B or "B is neither greater than or less than A"*/
	if (op == '=') {
		if (!(greaterthan(input1,input2)||greaterthan(input2,input1))) {
			printf("Result: true\n");
			exit(0);
		}
		else {
			printf("Result: false\n");
			exit(0);
		}
	}

	return result;
}

/*----------------------------------------------------------------------------*/

/*
 * Print to "stderr" and exit program
 */
void print_usage(char* name) {
	fprintf(stderr, "----------------------------------------------------\n");
	fprintf(stderr, "Usage: %s base input1 operation input2\n", name);
	fprintf(stderr, "base must be number between 2 and 36, inclusive\n");
	fprintf(stderr, "input1 and input2 are arbitrary-length integers\n");
	fprintf(stderr, "Two operations are allowed '+' and '-'\n");
	fprintf(stderr, "----------------------------------------------------\n");
	exit(1);
}

/*----------------------------------------------------------------------------*/

/*
 * MAIN: Run the program and tests your functions.
 * sample command: ./bignum 4 12 + 13
 * Result: 31
 */
int main(int argc, char** argv) {

	int input_base;

    int* input1;
    int* input2;
    int* result;

	if(argc != 5) {
		print_usage(argv[0]);
	}

	input_base = string_to_integer(argv[1]);

	if(!valid_base(input_base)) {
		fprintf(stderr, "Invalid base: %s\n", argv[1]);
		print_usage(argv[0]);
	}

	if(!valid_input(argv[2], input_base)) {
		fprintf(stderr, "Invalid input1: %s\n", argv[2]);
		print_usage(argv[0]);
	}

	if(!valid_input(argv[4], input_base)) {
		fprintf(stderr, "Invalid input2: %s\n", argv[4]);
		print_usage(argv[0]);
	}

        char op = argv[3][0];
	if(op != '-' && op != '+' && op != '<' && op != '>' && op != '=') {
		fprintf(stderr, "Invalid operation: %s\n", argv[3]);
		print_usage(argv[0]);
	}

	input1 = string_to_integer_array(argv[2]);
    input2 = string_to_integer_array(argv[4]);

    result = perform_math(input1, input2, argv[3][0], input_base);

    printf("Result: ");
    bignum_print(result);
	printf("\n");

	exit(0);
}
