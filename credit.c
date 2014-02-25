/*
Github @rajatbjain
*/

/*
Initals digits of American Express -> 37 and 34; MasterCard -> 51, 52, 53, 54 and 55; Visa -> 4; And checksum gives %10 == 0;
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 16

long long GetLongLong()
{
	long long a;
	scanf("%lld" ,&a);
	return a;
}

int main(int argc, char* argv[]) {

    int i, j;
	printf("NUMBER: ");
	long long cc = GetLongLong();

	//if negative, don't bother.
	if (cc < 0)
	{
		printf("INVALID\n");
		return 1;
	}

	//check the number of digits, without actualy doing anything with it.
	char *tmp = malloc(sizeof (char));
	int len = snprintf(tmp, 0, "%lld", cc);
	free(tmp);

	//if the number of digits is >16 or <13 or == 14 then this is an invalid cc number.
	if (len > 16 || len < 13 || len == 14)
	{
		printf("INVALID\n");
		return 0;
	}

	//make an array to store each digit.
	int card[MAX_LEN];

	//store each digit into the array. From 'LENGTH-1' to '0' for obvious reasons.

	for (i = len - 1; i >= 0; i--)
	{
		int mod = cc % 10;
		card[i] = mod;
		cc = cc / 10;
	}

	//the possible type of the credit card computation
	char* type;
	if (len == 15 && card[0] == 3 && (card[1] == 4 || card[1] == 7))
	{
		type = "AMEX";
	}
	else if (len == 16 && card[0] == 5 && card[1] >= 1 && card[1] <= 5)
	{
		type = "MASTERCARD";
	}
	else if ((len == 13 || len == 16) && card[0] == 4)
	{
		type = "VISA";
	}
	else
	{
		printf("INVALID\n");
		return 0;
	}

	int sum = 0;

	//i counts up, j counts down (j is the array position)
	for (i = 0, j = len - 1; i < len; i++, j--)
	{
		if (i % 2 == 0)
		{
			//the last digit, the third to last digit... etc
			sum += card[j];
		}
		else
		{
			//the second to last digit, the fourth to last digit...etc.
			//2xdigit, and if result > 9 add the digits together
			int tmp = 2 * card[j];
			if (tmp < 10)
				sum += tmp;
			else // (ie. 2x8=16 -> 1+6 = 7)
				sum += (tmp / 10) + (tmp % 10);
		}
	}

	//final check
	if (sum % 10 == 0)
		printf("%s\n", type);
	else
		printf("INVALID\n");

	return (EXIT_SUCCESS);
}
