#include <stdio.h>
#include <stdlib.h>

int finish[10], process_name[10], arrival_time[10], burst_time[10], remaining_burst[10], waiting_time[10], trunaround_time[10], ct[10];
int n, ctime, pending, count;
int total_wating, total_tat;
void input()
{
    // printf("\nEnter no of process");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        process_name[i] = i + 1;
        // printf("\nEnter arrival time for %d ",i+1);
        scanf("%d", &arrival_time[i]);
        // printf("\nEnter burst time for %d ",i+1);
        scanf("%d", &burst_time[i]);
        remaining_burst[i] = burst_time[i];
    }
}

void roundrobin()
{
    int timespan;
    printf("\nEnter timespan");
    scanf("%d", timespan);
    input();
    for (int i = 0; i < n; i++)
    {
        finish[i] = 0;
        waiting_time[i] = 0;
    }
    printf("\n printing Gantt chart ");
    ctime = 0;
    count = 0;
    pending = n;
    while (pending > 0)
    {
        if (finish[count] != 1 && arrival_time[count] <= ctime && remaining_burst[count] <= timespan)
        {
            ctime += remaining_burst[count];
            pending--;
            finish[count] = 1;
            ct[count] = ctime;

            trunaround_time[count] = ct[count] - arrival_time[count];
            waiting_time[count] = trunaround_time[count] - burst_time[count];
            for (int i = 0; i < remaining_burst[count]; i++)
            {
                printf("p%d", process_name[count]);
            }
            remaining_burst[count] = 0;
        }
        else if (finish[count] != 1 && arrival_time[count] <= ctime && remaining_burst[count] > timespan)
        {
            ctime += timespan;
            remaining_burst[count] -= timespan;
            for (int i = 0; timespan; i++)
            {
                printf("p%d", process_name[count]);
            }
        }
        count = (count + 1) % n;
    }
}
void displaydetail()
{
    printf("\nProcess Id\tArrival Time\tBurst Time\tWaiting Time\tTurn Around Time");
    printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    for (int i = 0; i < n; i++)
    {
        // Calculating the total waiting time
        total_wating += waiting_time[i];
        // Calculating total turn around time
        total_tat += trunaround_time[i];

        printf("P%d\t\t %d\t\t %d\t\t %d\t\t %d", process_name[i], arrival_time[i], burst_time[i], waiting_time[i], trunaround_time[i]);
        printf("\n");
    }
}
void sort()
{
    int temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (remaining_burst[i] < remaining_burst[j])
            {
                temp = remaining_burst[i];
                remaining_burst[i] = remaining_burst[j];
                remaining_burst[j] = temp;

                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;

                temp = arrival_time[i];
                arrival_time[i] = arrival_time[j];
                arrival_time[j] = temp;

                temp = process_name[i];
                process_name[i] = process_name[j];
                process_name[j] = temp;

                temp = finish[i];
                finish[i] = finish[j];
                finish[j] = temp;

                temp = waiting_time[i];
                waiting_time[i] = waiting_time[j];
                waiting_time[j] = temp;

                temp = trunaround_time[i];
                trunaround_time[i] = trunaround_time[j];
                trunaround_time[j] = temp;

                temp = ct[i];
                ct[i] = ct[j];
                ct[j] = temp;
            }
            else if (remaining_burst[i] == remaining_burst[j])
            {
                if (arrival_time[i] < arrival_time[j])
                {
                    temp = remaining_burst[i];
                    remaining_burst[i] = remaining_burst[j];
                    remaining_burst[j] = temp;

                    temp = burst_time[i];
                    burst_time[i] = burst_time[j];
                    burst_time[j] = temp;

                    temp = arrival_time[i];
                    arrival_time[i] = arrival_time[j];
                    arrival_time[j] = temp;

                    temp = process_name[i];
                    process_name[i] = process_name[j];
                    process_name[j] = temp;

                    temp = finish[i];
                    finish[i] = finish[j];
                    finish[j] = temp;

                    temp = waiting_time[i];
                    waiting_time[i] = waiting_time[j];
                    waiting_time[j] = temp;

                    temp = trunaround_time[i];
                    trunaround_time[i] = trunaround_time[j];
                    trunaround_time[j] = temp;

                    temp = ct[i];
                    ct[i] = ct[j];
                    ct[j] = temp;
                }
            }
        }
    }
}
void sjf_premptive()
{
    input();
    pending = n;
    printf("\nprinting gantt chart ");
    for (int i = 0; i < n; i++)
    {
        finish[i] = 0;
        waiting_time[i] = 0;
    }
    ctime = 0;
    count = 0;
    while (pending > 0)
    {
        sort();
        for (count = 0; count < n; count++)
        {
            if (finish[count] != 1 && arrival_time[count] <= ctime)
            {
                ctime += 1;
                remaining_burst[count] -= 1;
                printf("p%d", process_name[count]);
                if (remaining_burst[count] == 0)
                {
                    finish[count] = 1;
                    pending--;
                    ct[count] = ctime;

                    trunaround_time[count] = ct[count] - arrival_time[count];
                    waiting_time[count] = trunaround_time[count] - burst_time[count];
                }
                break;
            }
        }
    }
}
int main()
{
    sjf_premptive();
    return 0;
}
