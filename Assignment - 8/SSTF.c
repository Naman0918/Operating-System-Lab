#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void sstf()
{
    int n, head;
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int request[n];

    printf("Enter the head ");
    scanf("%d", &head);

    printf("Enter the request queue: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &request[i]);
    }

    int seek_sequence[n];
    int seek_count = 0;

    int visited[n];

    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        int min_seek = INT_MAX;
        int min_seek_index = -1;

        for (int j = 0; j < n; j++)
        {
            if (!visited[j])
            {
                int seek = abs(head - request[j]);
                if (seek < min_seek)
                {
                    min_seek = seek;
                    min_seek_index = j;
                }
            }
        }
        visited[min_seek_index] = 1;
        seek_sequence[i] = request[min_seek_index];
        seek_count += min_seek;
        head = request[min_seek_index];
    }

    printf("Seek Sequence (SSTF): ");
    for (int i = 0; i < n; i++)
    {
        printf("%d", seek_sequence[i]);
        if (i != n - 1)
        {
            printf(" -> ");
        }
    }
    printf("\n");
    printf("Total Seek Count = %d\n", seek_count);
}

int main()
{

    sstf();
    return 0;
}
