#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) // argc is the number of command line arguments passed to the program including the name of the program
{
	int a[100]; // array to store the command line arguments
	int n;
	printf("\n Enter number to find in array :");
	scanf("%d", &n);
	for (int i = 0; i < argc; i++)
	{
		a[i] = atoi(argv[i]); // converting the command line arguments to integer and storing in array
		// atoi is used to convert string to integer
	}
	// for loop to print reverse numbers
	//reverse numbers
	for (int i = 0; i < argc; i++) // argc is the number of command line arguments passed to the program including the name of the program
	{
		if (a[i] == n)
		{
			printf("\n Entered number is found in array");
			return 0;
		}
	}
	printf("\n Entered number is not in array");
	return 0;
}
