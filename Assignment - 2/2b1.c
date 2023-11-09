#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>


void bubblesort(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

int main()
{
	char *arg[20], str[20]; // args for execve command and str for converting int to string
	int arr[100];
	int n;

	printf("\nEnter no of elements to entered in array");
	scanf("%d", &n);
	printf("\nEnter the array numbers");
	for (int i = 0; i < n; i++)
	{
		scanf("%d ", &arr[i]);
	}
	printf("\nProcess is with parent having id : %d", getpid());
	printf("\n array before sorting is as follows");
	for (int i = 0; i < n; i++)
	{
		printf(" %d", arr[i]);
	}
	printf("\n");
	printf("\n Calling bubble sort function in parent\n");
	bubblesort(arr, n);
	printf("\n Array after Sorting is as follows\n");
	for (int i = 0; i < n; i++)
	{
		printf(" %d", arr[i]);
	}
	printf("\n");
	printf("\n Forking the process now"); 
	pid_t child = fork();// forking the process now means creating child process
	if (child < 0)
	{
		printf("\n Error while creating child process");
	}
	else if (child == 0)
	{
		// child process is created now and it will execute the execve command
		int i = 0;
		printf("\n Process control is with child process");
		printf("\n Child process id : %d", getpid()); // getpid is child process id
		printf("\n Child parent process id : %d ", getppid()); //ppid is parent process id

		for (i = 0; i < n; i++)
		{
			sprintf(str, "%d", arr[i]); // converting int to string using sprintf
			arg[i] = malloc(sizeof(str));// allocating memory for arg array of char pointers
			strcpy(arg[i], str); // copying the string to arg array of char pointers 
		}
		
		arg[i] = '\0'; // last element of arg array of char pointers is null 
		printf("\nExecuting execve command now in child");
		execve("./2bb2", arg, NULL);
		printf("\n Execve is sussesfully executed now");
		
		printf("\nChild completely executed");
	}
	else
	{ // parent process is executing now 
	  // parent process will wait for child to get complete and then it will execute 
		printf("\nProcess control is with parent process having id : %d", getppid());
		printf("\nWating for child to get complete");
		wait(NULL);
		printf("\n Parent is back again");
		printf("\n parent successsfuly executed");
	}
}
