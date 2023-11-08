#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void SCAN()
{
    int request[100], i, j, n, seek_count = 0, head, size, move;
    printf("Enter the number of Requests\n");
    scanf("%d", &n);

    printf("Enter the Requests sequence\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &request[i]);
    }

    printf("Enter head position\n");
    scanf("%d", &head);

    printf("Enter total disk size\n");
    scanf("%d", &size);

    printf("Enter the head movement direction for high 1 and for low 0\n");
    scanf("%d", &move);
// sorting the request array in ascending orders
    for (i = 0; i < n -1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (request[j] > request[j + 1])
            {
                int temp = request[j];
                request[j] = request[j + 1];
                request[j + 1] = temp;
            }
        }
    }

    int index = -1;
    for (i = 0; i < n; i++)// find index of head in request array
    {
        if (head < request[i]) // head < request[i] because we have to find the index of the first request which is greater than head
        {
            index = i;
            break;
        }
    }
    // seek_count == seek_count
    if (move == 1)
    {
        for (i = index; i < n; i++)
        {
            seek_count += abs(request[i] - head);
            head = request[i];
        }
        // for last request
        seek_count += abs((size - 1) - request[n -1 ] );// request[i - 1] because we have to find the last request which is less than head
        head = size - 1;
        for (i = index - 1; i >= 0; i--)// index - 1 because we have to start from the request just before the head
        {
            seek_count += abs(request[i] - head);
            head = request[i];
        }
    }

    else // if move == 0
    {
        for (i = index - 1; i >= 0; i--)
        {
            seek_count += abs(request[i] - head); // abs because head > request[i]
            head = request[i];
        }
        seek_count +=  abs(request[0] - 0);// for last request
        head = 0;
        for (i = index; i < n; i++)// index because we have to start from the request just after the head
        {
            seek_count += abs(request[i] - head);// abs because head < request[i]
            head = request[i];// head = request[i] because we have to move the head to the next request
        }
    }
    // printf("Seek Sequence (C-LOOK): ");
    // for (int j = 0; j < n; j++)
    // {
    //     printf("P%d",);
    //     if (j != n - 1)
    //     {
    //         printf(" -> ");
    //     }
    // }
    printf("\n");
    printf("Total Seek Count = %d\n", seek_count);

}

int main()
{
    SCAN();
    return 0;
}
