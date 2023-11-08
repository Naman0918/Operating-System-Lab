#include <stdio.h>
#include <stdlib.h>

int hit = 0;
int pagefault = 0;
int p[100];
int frame[20];
int n;
int nf;

void getprocess()
{
    printf("Enter number of process : ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter process number : ");
        scanf("%d", &p[i]);
    }
    printf("Enter frame size : ");
    scanf("%d", &nf);
}

void init()
{
    int hit = 0;
    int pagefault = 0;
    for (int i = 0; i < nf; i++)
    {
        frame[i] = 9999;
    }
}

void pagedisplay()
{
    for (int i = 0; i < nf; i++)
    {
        if (frame[i] != 9999)
        {
            printf("%d ", frame[i]);
        }
    }
}

int ishit(int page) // return index if hit else return -1
{
    // explain function
    // if hit return index of page in frame
    int ishit = -1;
    for (int i = 0; i < nf; i++)
    {
        if (frame[i] == page)
        {
            ishit = i;
            hit++;
        }
    }
    return ishit;
}

void fifo()
{
    init(); // initialize frame
    printf("----------------------fifo--------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("\nfor process id -> %d", p[i]); // p[i] is page in process array
        int j = 0;
        if (ishit(p[i]) == -1)
        {
            printf(" Miss : ");
            for (j = 0; j < nf - 1; j++) // explain for loop and j<nf-1 condition
            // j<nf-1 because we are shifting frame to left by 1 position and we are inserting new page at last position
            {
                frame[j] = frame[j + 1]; // shift frame to left by 1 position to make space for new page
            }
            frame[j] = p[i]; // insert new page at last position
            // what is value of j here if nf = 3
            // j=2
            pagefault++;   // increment pagefault
            pagedisplay(); // display frame
        }
        else
        {
            printf(" Hit  : ");
            pagedisplay();
        }
    }
    printf("\n");
    printf("\nTotal No.of page fault are :%d", pagefault);
    printf("\nTotal No.of hits are :%d", (n - pagefault));
}

void lru() // full form of lru - least recently used
{
    init();
    printf("------------------------LRU-----------------------\n");
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        printf("\nfor process id -> %d", p[i]);
        int key = ishit(p[i]);
        if (ishit(p[i]) == -1)
        {
            printf(" Miss : ");
            for (j = 0; j < nf - 1; j++)
            {
                frame[j] = frame[j + 1];
            }
            frame[j] = p[i];
            pagedisplay();
            pagefault++;
        }
        else
        {
            printf(" Hit  : ");
            for (j = key; j < nf - 1; j++) // explain for loop and j<nf-1 condition
            // j<nf-1 because we are shifting frame to left by 1 position and we are inserting new page at last position
            // j=key because we are shifting frame to left by 1 position and we are inserting new page at last position
            // key is index of page in frame
            // if key=1 and nf=3
            // if key = 4 then j=4 and j<nf-1 is false so loop will not execute
            {
                frame[j] = frame[j + 1];
            }
            frame[j] = p[i];
            pagedisplay();
        }
    }
    printf("\n");
    printf("\nTotal No.of page fault are :%d", pagefault);
    printf("\nTotal No.of hits are :%d", (n - pagefault));
}

void optimal()
{
    init();
    printf("-----------------optimal-----------------\n");
    int opt[n];

    int i, j, k;
    for (i = 0; i < n; i++)
    {
        if (ishit(p[i]) == -1)
        {
            printf(" Miss : ");
            for (j = 0; j < nf; j++)
            {
                int pg = frame[j]; // pg is page in frame meaning page in frame at index j
                // pg is page in frame
                int found = 0;
                for (k = i + 1; k < n; k++) // IMPORTANT RANGE
                {
                    if (p[k] == pg)
                    {
                        opt[j] = k; // why j is used here
                        // j is index of page in frame
                        // opt is array which stores index of page in process array
                        found = 1;
                        // if page is found in process array then break loop
                    }
                }
                if (!found)
                {
                    opt[j] = 99999;
                }
            }

            int max = -99999;
            int maxind;
            for (int i = 0; i < nf; i++)
            // explain for loop
            // we are finding page which is not used for longest time
            {
                if (opt[i] > max) // opt[i] is index of page in process array
                {
                    max = opt[i];
                    maxind = i;
                }
            }
            // explain maxind
            // maxind is index of page in frame which is not used for longest time
            // if maxind=1 then page at index 1 in frame is not used for longest time
            frame[maxind] = p[i]; // insert new page at index maxind in frame
            pagedisplay();
            pagefault++;
        }
        else
        {
            printf(" Hit  : ");
            pagedisplay();
        }
    }
    printf("\n");
    printf("\nTotal No.of page fault are :%d", pagefault);
    printf("\nTotal No.of hits are :%d", (n - pagefault));
}

int main()
{
    int choice;
    

    while (choice != 4)
    {
        printf("**********MENU**********\n");
        printf("1.FIFO\n2.LRU\n3.Optimal\n4.EXIT\n");
        printf("************************\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        getprocess();
        switch (choice)
        {
        case 1:
            fifo();
            break;
            printf("\n");
        case 2:
            lru();
            break;
            printf("\n");
        case 3:
            optimal();
            break;
            printf("\n");
        default:
            printf("Invalid choice");
            break;
        }
    }

    return 0;
}
