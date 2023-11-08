#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void clook()
{
    int request[100], n, head, size;

    printf("Enter the number of Requests\n");
    scanf("%d", &n);

    printf("Enter the Requests sequence\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &request[i]);
    }

    printf("Enter head head posidon\n");
    scanf("%d", &head);

    printf("Enter total disk size\n");
    scanf("%d", &size);

    int seek_sequence[n];
    int seek_count = 0;

    // Sort the requests in ascending order
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (request[j] > request[j + 1])
            {
                // Swap requests
                int temp = request[j];
                request[j] = request[j + 1];
                request[j + 1] = temp;
            }
        }
    }

    // Find the index of the first request greater than the head position
    int start = -1;
    for (int i = 0; i < n; i++)// find index of head in request array
    {
        if (head < request[i]) // head < request[i] because we have to find the index of the first request which is greater than head
        {
            start = i;
            break;
        }
    }

    // The head moves towards the greater request
    int i = 0;
    for (int j = start; j < n; j++)
    {
        seek_sequence[i] = request[j];
        seek_count += abs(head - request[j]);
        head = request[j];
        i++;
    }

    // Once it reaches the end, it jumps to the first request
    for (int j = 0; j < start; j++)
    {
        seek_sequence[i] = request[j];
        seek_count += abs(head - request[j]);
        head = request[j];
        i++;
    }

    printf("Seek Sequence (C-LOOK): ");
    for (int j = 0; j < n; j++)
    {
        printf("%d", seek_sequence[j]);
        if (j != n - 1)
        {
            printf(" -> ");
        }
    }
    printf("\n");
    printf("Total Seek Count = %d\n", seek_count);
}

int main()
{

    clook();
    return 0;
}
