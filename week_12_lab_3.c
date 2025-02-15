#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define INF 999

void AllPairShortestPath_DP(int n, int d[][n], int p[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            p[i][j] = d[i][j];
        }
    }

    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if (d[i][k] != INF && d[k][j] != INF && d[i][k] + d[k][j] < d[i][j]) {
                d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }

    // ปริ้น matrix หลังหาเส้นทาง
    printf("Result :\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            printf("%d\t", d[i][j]);
        printf("\n");
    }
}


int main(){
    int i, j, m, n;
    int u, v, e;

    //รับค่าโหนดในกราฟ และเส้นเชื่อมในกราฟ
    printf("Input node and edge  :\n");
    scanf("%d %d", &n, &m);

    int d[n][n];
    int p[n][n];

    // กำหนดค่าเริ่มต้น matrix d, p
    for(i=0;i<n;i++){
        for (j=0;j<n;j++){
            p[i][j] = -1;
            if (i==j)
                d[i][j] = 0;
            else
                d[i][j] = INF;
        }
    }

    // รับข้อมูลเส้นเชื่อมในกราฟ
    // โหนด   U---weight---V
    printf("Input edges (u v weight) :\n");
    for(i=1;i<=m;i++){
        scanf("%d %d %d", &u, &v, &e);
        d[u-1][v-1] = e;
        d[v-1][u-1] = e;
    }

    // ปริ้น matrix หลังกำหนดค่า
    printf("Input :\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            printf("%d\t", d[i][j]);
        printf("\n");
    }

    AllPairShortestPath_DP(n, d, p);


    return 0;
}