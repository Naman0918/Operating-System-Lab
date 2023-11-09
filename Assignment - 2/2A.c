#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int n;
int arr[100];
int choice = 0;

void bubblesort(int arr[], int n)
{
  int temp;
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        temp = arr[j + 1];
        arr[j + 1] = arr[j];
        arr[j] = temp;
      }
    }
  }
}
void zombie()
{
  int p_id = getpid();
  printf("\n Parent's process id is %d ", p_id);
  printf("\n Forking the process");
  pid_t id = fork(); // forking the process now means creating child process
  if (id == -1)
  {
    printf("\n The child is not created ");
  }
  else if (id == 0) // child process is created now and it will execute the execve command
  {
    printf("\n In child process ");
    printf("\n The child process id is %d", getpid());
    printf("\n This child parent id is %d", getppid());
    printf("\n Array before sorting is : ");
    for (int i = 0; i < n; i++)
    {
      printf(" %d", arr[i]);
    }
    printf("\nUsing bubble sort sorting the array");
    bubblesort(arr, n);
    printf("\nPrinting the sorted array(Bubble sort) : ");
    for (int i = 0; i < n; i++)
    {
      printf(" %d", arr[i]);
    }
    printf("\n Above is the sorted array using bubble sort");
    printf("\n The child process executed successfully");
    exit(0); // child process is terminated now
  }
  else // parent process
  {
    sleep(40); // sleep for 40 seconds so that child process can be terminated and become zombie process
    printf("\nProcess is with parent its id is : %d", getpid());
    printf("\nChild is terminated after wait with pid: ");
    printf("\n Array before sorting is : ");
    for (int i = 0; i < n; i++)
    {
      printf(" %d", arr[i]);
    }
    printf("\nUsing merge sort sorting the array");
    bubblesort(arr, n);
    printf("\nPrinting the sorted array(Bubble sort) : ");
    for (int i = 0; i < n; i++)
    {
      printf(" %d", arr[i]);
    }
    printf("Parent executed successfully\n");
    sleep(30); // sleep for 30 seconds so that child process can be terminated
  }
}
void normal()
{
  pid_t p_id = getpid();
  printf("\n Parent's process id is %d ", p_id);
  printf("\n Forking the process");
  pid_t id = fork();
  if (id == -1)
  {
    printf("\n The child is not created ");
  }
  else if (id == 0)
  {
    printf("\n In child process ");
    printf("\n The child process id is %d", getpid());
    printf("\n This child parent id is %d", getppid());
    printf("\n Array before sorting is : ");
    for (int i = 0; i < n; i++)
    {
      printf(" %d", arr[i]);
    }
    printf("\nUsing bubble sort sorting the array");
    bubblesort(arr, n);
    printf("\nPrinting the sorted array(Bubble sort) : ");
    for (int i = 0; i < n; i++)
    {
      printf(" %d", arr[i]);
    }
    printf("\n Above is the sorted array using bubble sort");
    printf("\n The child process executed successfully");
  }
  else
  {
    printf("\nProcess is with parent its id is : %d", getpid());
    pid_t cpid = wait(NULL); // wait for child process to terminate and then execute the parent process
    // significance of null is that it will wait for any child process to terminate
    printf("\nChild is terminated after wait with pid: %d", cpid);
    printf("\n Array before sorting is : ");
    for (int i = 0; i < n; i++)
    {
      printf(" %d", arr[i]);
    }
    printf("\nUsing merge sort sorting the array");
    bubblesort(arr, n);
    printf("\nPrinting the sorted array(Merge sort) : ");
    for (int i = 0; i < n; i++)
    {
      printf(" %d", arr[i]);
    }
    printf("\nParent executed successfully\n");
  }
}

void orphan()
{
  pid_t p_id = getpid();
  printf("\n Parent's process id is %d ", p_id);
  printf("\n Forking the process");
  pid_t id = fork();
  if (id == -1)
  {
    printf("\n The child is not created ");
  }
  else if (id == 0)
  {
    printf("\n In child process ");
    printf("\n The child process id is %d", getpid());
    printf("\n This child parent id is %d", getppid());
    printf("\n Array before sorting is : ");
    for (int i = 0; i < n; i++)
    {
      printf(" %d", arr[i]);
    }
    printf("\nUsing bubble sort sorting the array");
    bubblesort(arr, n);
    printf("\nPrinting the sorted array(Bubble sort) : ");
    for (int i = 0; i < n; i++)
    {
      printf(" %d", arr[i]);
    }
    printf("\n Above is the sorted array using bubble sort");
    sleep(30);// sleep for 30 seconds so that parent process can be terminated and child process can be orphan
    printf("\n The child process executed successfully");
    printf("\n The child process id is %d", getpid());
    printf("\n This child parent id is %d", getppid());
  }
  else
  {
    printf("\nProcess is with parent its id is : %d", getpid());
    // pid_t cpid = wait(NULL);
    // printf("\nChild is terminated after wait with pid: %d", cpid);
    printf("\n Array before sorting is : ");
    for (int i = 0; i < n; i++)
    {
      printf(" %d", arr[i]);
    }
    printf("\nUsing merge sort sorting the array");
    bubblesort(arr, n);
    printf("\nPrinting the sorted array(Merge sort) : ");
    for (int i = 0; i < n; i++)
    {
      printf(" %d", arr[i]);
    }
    printf("\nParent executed successfully\n");
  }
}

void input()
{
  printf("\nEnter no of elements : ");
  scanf("%d", &n);
  printf("\nEnter elements of array : ");
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &arr[i]);
  }
  printf("\n---------------- MENU ----------------\n");
  printf("1) Normal Execution\n");
  printf("2) Zombie\n");
  printf("3) Orphan\n");
  printf("Please enter your choice: \n");
  scanf("%d", &choice);
  if (choice == 1)
  {
    normal();
  }
  else if (choice == 2)
  {
    zombie();
  }
  else if (choice == 3)
  {
    orphan();
  }
}

int main()
{
  input();
  return 0;
}
