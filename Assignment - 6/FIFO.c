#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m, i, j, k, hit = 0;
    printf("Enter number of frames\n");
    scanf("%d", &n);
    printf("Enter number of processes\n");
    scanf("%d", &m);

    int p[m];
    int hi[m];
    printf("Enter processes\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &p[i]);
    }

    int a[n][m];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            a[i][j] = -1;
        }
    }

    int mp[m];
    for (i = 0; i < m; i++) {
        mp[i] = 0;
    }

    for (i = 0; i < m; i++) {
        int c[m][2];
        int idx = 0;
        for (int q = 0; q < m; q++) {
            c[idx][0] = mp[q];
            c[idx][1] = q;
            idx++;
        }

        for (int p1 = 0; p1 < idx; p1++) {
            for (int p2 = p1 + 1; p2 < idx; p2++) {
                if (c[p1][0] > c[p2][0]) {
                    int temp0 = c[p1][0];
                    int temp1 = c[p1][1];
                    c[p1][0] = c[p2][0];
                    c[p1][1] = c[p2][1];
                    c[p2][0] = temp0;
                    c[p2][1] = temp1;
                }
            }
        }

        int hasrun = 0;
        for (j = 0; j < n; j++) {
            if (a[j][i] == p[i]) {
                hit++;
                hi[i] = 1;
                mp[p[i]]++;
                hasrun = 1;
                break;
            }
            if (a[j][i] == -1) {
                for (k = i; k < m; k++)
                    a[j][k] = p[i];
                mp[p[i]]++;
                hasrun = 1;
                break;
            }
        }

        if (j == n || hasrun == 0) {
            for (j = 0; j < n; j++) {
                if (a[j][i] == c[m - 1][1]) {
                    mp[a[j][i]] = 0;
                    for (k = i; k < m; k++)
                        a[j][k] = p[i];
                    mp[p[i]]++;
                    break;
                }
            }
        }

        for (int q = 0; q < m; q++) {
            if (q != p[i]) {
                mp[q]++;
            }
        }
    }

    printf("Process ");
    for (i = 0; i < m; i++) {
        printf("%d ", p[i]);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("Frame %d ", i);
        for (j = 0; j < m; j++) {
            if (a[i][j] == -1)
                printf("E ");
            else
                printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < m; i++) {
        if (hi[i] == 0)
            printf("  ");
        else
            printf("%d ", hi[i]);
    }
    printf("\n");

    printf("Hit %d\nPage Fault %d\n", hit, m - hit);
    return 0;
}
