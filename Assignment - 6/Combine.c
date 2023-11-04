#include <stdio.h>
int miss = 0, hit = 0;
int n, f;
int arr[100][100];
int p[100];
int frame[100];

int s = 0;

void display()
{
    int x = 1;
    for (int i = 0; i < f; i++)
    {
        printf("f%d ", x);
        x++;
        for (int j = 0; j < n; j++)
        {
            if (arr[i][j] == -1)
            {
                printf("*  ");
            }
            else
            {
                printf("%d  ", arr[i][j]);
            }
        }
        printf("\n");
    }

    printf("Hit %d\n", hit);
    printf("Miss %d\n", miss);
}
void fifo()
{
    for (int i = 0; i < f; i++)
    {
        frame[i] = -1;
    }
    for (int i = 0; i < n; i++)
    {
        int cnt = 0;
        int j = 0;
        for (; j < f; j++)
        {
            if (frame[j] == -1)
            {
                cnt++;
                break;
            }
        }
        if (cnt != 0)
        {
            miss++;
            frame[j] = p[i];
        }
        else
        {
            int c = 0;

            for (int d = 0; d < f; d++)
            {
                if (frame[d] == p[i])
                {
                    c++;
                    break;
                }
            }
            if (c == 0)
            {
                miss++;
                frame[s] = p[i];
                s += 1 % f;
            }
            else
            {
                hit++;
            }
        }
        for (int k = 0; k < f; k++)
        {
            arr[k][i] = frame[k];
        }
    }
    display();
}
void lru()
{
    for (int i = 0; i < f; i++)
    {
        frame[i] = -1;
    }
    for (int i = 0; i < n; i++)
    {
        int cnt = 0;
        int j = 0;
        for (; j < f; j++)
        {
            if (frame[j] == -1)
            {
                cnt++;
                break;
            }
        }
        if (cnt != 0)
        {
            miss++;
            frame[j] = p[i];
        }
        else
        {
            int count = 0;
            for (int k = 0; k < f; k++)
            {
                // Checking hit condition
                if (p[i] == frame[k])
                {
                    count++;
                    break;
                }
            }
            if (count != 0)
            {
                // If hit then count of hit is added
                hit++;
            }
            else
            {
                miss++;
                int fReplace[f];

                for (int j = 0; j < f; j++)
                {
                    fReplace[j] = -1;
                    /*storing the indexes of the frame elements to find the farthest element*/
                    for (int k = i - 1; k >= 0; k--)
                    {
                        if (p[k] == frame[j])
                        {
                            fReplace[j] = k;
                            break;
                        }
                    }
                }
                // Finding the farthest frame

                int miniIndex = 1e9;
                int ind = -1;
                for (int j = 0; j < f; j++)
                {
                    if (fReplace[j] == -1)
                    {
                        ind = j;
                        break;
                    }
                    if (miniIndex > fReplace[j])
                    {
                        miniIndex = fReplace[j];
                        ind = j;
                    }
                }
                // frame replaced
                // printf("%d-F\n",fReplace);
                frame[ind] = p[i];
            }
        }

        for (int j = 0; j < f; j++)
        {
            arr[j][i] = frame[j];
        }
    }
    display();
}
void optimal()
{
    for (int i = 0; i < f; i++)
    {
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int cnt = 0;
        int j = 0;
        for (; j < f; j++)
        {
            if (frame[j] == -1)
            {
                cnt++;
                break;
            }
        }
        if (cnt != 0)
        {
            miss++;
            frame[j] = p[i];
        }
        else
        {
            int c = 0;

            for (int j = 0; j < f; j++)
            {
                if (frame[j] == p[i])
                {
                    c++;
                    break;
                }
            }
            if (c != 0)
            {
                hit++;
            }
            else
            {
                miss++;
                int l = 0;
                int fr[f];

                int cn = 0;
                for (int k = 0; k < f; k++)
                {
                    fr[k] = -1;
                    for (int j = i + 1; j < n; j++)
                    {
                        if (p[j] == frame[k])
                        {
                            fr[k] = j;
                            cn++;
                            break;
                        }
                    }
                }

                int mx = -1;
                int ind = 0;
                for (int l = 0; l < f; l++)
                {
                    if (fr[l] == -1)
                    {

                        ind = l;
                        break;
                    }
                    if (fr[l] > mx)
                    {
                        mx = fr[l];
                        ind = l;
                    }
                }
                frame[ind] = p[i];
            }
        }
        for (int k = 0; k < f; k++)
        {
            arr[k][i] = frame[k];
        }
    }
    display();
}

int main()
{
    printf("Enter the size of the reference String :: ");
    scanf("%d", &n);
    printf("Enter the reference string :: ");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i]);
    }
    printf("Enter the frame size :: ");
    scanf("%d", &f);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < f; j++)
        {
            arr[j][i] = -1;
        }
    }
    int flag = 1;
    while (flag)
    {
        printf("Menu :: 1) FIFO\t2) LRU\t3) Optimal  4) Exit\nChoice :: ");
        int ch;
        scanf("%d", &ch);
        printf("\n");
        switch (ch)
        {
        case 1:
            fifo();
            break;
        case 2:
            // LRU();
            lru();
            break;
        case 3:
            optimal();
            break;
        case 4:
            flag = 0;
            printf("\nExiting ...\n");
            break;
        default:
            printf("Invalid Input !!!\n\n");
            break;
        }
    }
}
