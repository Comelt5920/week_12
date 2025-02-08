#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
void get_data(int n, int *data) {
    int i;
    time_t t;
    srand((unsigned) time(&t));

    for (i = 0; i < n; i++) {
        //printf("%d ", rand() % 10);
        data[i] = rand() % 100;
    }
}
double calculate_mean(double data[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) sum += data[i];
    return sum / n;
}
double calculate_sd(double data[], int n, double mean) {
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += pow(data[i] - mean, 2);
    return sqrt(sum / n);
}
void insertionsort(int data[],int n){
    for(int i=1;i<n;i++){
        int tmp = data[i];
        int j=i-1;
        while(j>=0 && data[j]>tmp){
            data[j+1]  = data[j];
            j=j-1;
        }
        data[j+1]=tmp;
    }
}
void shellsort(int data[],int n){
    for(int d=n/2;d>0;d=d/2){
        for(int i=d;i<n;i++){
            int j;
            int tmp=data[i];
            for (j = i; j >= d && data[j - d] > tmp; j -= d)
                data[j] = data[j - d];
            data[j]=tmp;
        }
    }
}
void swap(int* a, int* b);
void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}
void quicksort(int data[], int p, int r){
    if (p<r){
        int j = partition(data, p, r);
        quicksort(data, p, j-1);
        quicksort(data, j+1, r);
    }
}
int partition(int data[], int p, int r){
    int c = data[p];
    int i=p-1;
    int j=r+1;
    while(i<j){
        while(data[--j]>c){}
        while(data[++i]<c){}
        if(i<j){
                swap(&data[i],&data[j]);
        }
    return j;
    }
}
void BubbleSort(int n,int *data){
    int swapped = 1;
    while(swapped==1){
        swapped =0;
        for(int i=0;i<n;i++){
            if(data[i] > data[i+1]){
                int tmp = data[i];
                data[i] = data[i+1];
                data[i+1] = tmp;
                swapped = 1;
            }
        }
    }
}
void Selection(int n,int *data){
    int tmp,j,k;
    for(int i=0;i<n;i++){
        tmp = data[i],k=j;
        for(j=i+1;j<n;j++){
            if(data[j]<tmp){
                tmp = data[j];
                k=j;
            }
        }
        tmp = data[i];
        data[i] = data[k];
        data[k] = tmp;
    }
}
void Merge(int *A,int p,int q,int r){
    int n1 = q-p+1;
    int n2 = r-q;
    int L[n1+1],R[n2+1];
    for(int i=0;i<n1;i++){
        L[i] = A[p+i];
    }
    for(int j=0;j<n2;j++){
        R[j] = A[q+1+j];
    }
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    int i=0,j=0;
    for(int k=p;k<=r;k++){
        if(L[i]<=R[j]){
            A[k] = L[i];
            i=i+1;
        }
        else{
            A[k] =R[j];
            j=j+1;
        }
    }
}
void Merge_Sort(int *A,int p,int r){
    if(p<r){
        int q = p+(r-p)/2;
        Merge_Sort(A,p,q);
        Merge_Sort(A,q+1,r);
        Merge(A,p,q,r);
    }
}
int main(){
    int exp, num_exp = 5;
    int i, n, num[5] = {1000, 5000, 10000, 20000, 50000};
    int t, run = 10;
    clock_t begin;
    clock_t end;
    double t_insertionsort[num_exp][run],t_shellsort[num_exp][run],t_quicksort[num_exp][run],t_bubble[num_exp][run],t_selection[num_exp][run],t_merge[num_exp][run];
    double mean_bubble=0,mean_selection=0,mean_merge=0;

    for (exp=0; exp<num_exp; exp++){
        n = num[exp];
        printf("\nn= %d\n", n);
        int data[n];
        for (t = 0; t < run; t++) {
            printf("\nrun %d\t", t + 1);
            get_data(n, data);

            //////////////////////////////Insertion_Zone//////////////////////////////
            //insertion_timer_Begin
            begin = clock();
            //insertion_function
            insertionsort(data, n);
            //insertion_timer_End
            end = clock();
            //calculate_time
            t_insertionsort[exp][t] = ((double) (end - begin)/ CLOCKS_PER_SEC);
            printf("time_algo1 : %f\t", t_insertionsort[exp][t]);
            //////////////////////////////Insertion_Zone//////////////////////////////

            //////////////////////////////Shell_Zone//////////////////////////////
            //insertion_timer_Begin
            begin = clock();
            //insertion_function
            shellsort(data, n);
            //insertion_timer_End
            end = clock();
            //calculate_time
            t_shellsort[exp][t] = ((double) (end - begin)/ CLOCKS_PER_SEC);
            printf("time_shellsort : %f\t", t_shellsort[exp][t]);
            //////////////////////////////Shell_Zone//////////////////////////////

            //////////////////////////////Quick_Zone//////////////////////////////
            //insertion_timer_Begin
            begin = clock();
            //insertion_function
            quicksort(data, 0, n-1);
            //insertion_timer_End
            end = clock();
            //calculate_time
            t_quicksort[exp][t] = ((double) (end - begin)/ CLOCKS_PER_SEC);
            printf("time_quicksort : %f\t", t_quicksort[exp][t]);
            //////////////////////////////Quick_Zone//////////////////////////////

            //////////////////////////////BubbleSort_Zone//////////////////////////////
            begin = clock();
            Selection(n,data);
            end = clock();
            t_selection[exp][t] = (double)(end - begin) / CLOCKS_PER_SEC;
            mean_selection = mean_selection+t_selection[exp][t];
            printf("Time_Selection_Sort: %f\t", t_selection[exp][t]);
            //////////////////////////////BubbleSort_Zone//////////////////////////////

            //////////////////////////////Selection_Zone//////////////////////////////
            //timer_Begin
            begin = clock();
            //function
            Selection(n,data);
            //timer_End
            end = clock();
            //calculate_time
            t_selection[exp][t] = (double)(end - begin) / CLOCKS_PER_SEC;
            mean_selection = mean_selection+t_selection[exp][t];
            printf("Time_Selection_Sort: %f\t", t_selection[exp][t]);
            //////////////////////////////Selection_Zone//////////////////////////////

            //////////////////////////////Merge_Zone//////////////////////////////
            begin = clock();
            Merge_Sort(data,0,n-1);
            end = clock();
            t_merge[exp][t] = (double)(end - begin) / CLOCKS_PER_SEC;
            mean_merge = mean_merge+t_merge[exp][t];
            printf("Time_Merge_Sort: %f\n",t_merge[exp][t]);
            //////////////////////////////Merge_Zone//////////////////////////////


        }

        //Calculate_mean_Insertion
        double mean_insertionsort = calculate_mean(t_insertionsort[exp], run);
        //Calculate_sd_Insertion
        double sd_insertionsort = calculate_sd(t_insertionsort[exp], run, mean_insertionsort);

        //Calculate_mean_shell
        double mean_shellsort = calculate_mean(t_shellsort[exp], run);
        //Calculate_mean_shell
        double sd_shellsort = calculate_sd(t_shellsort[exp], run, mean_shellsort);

        //Calculate_mean_shell
        double mean_quicksort = calculate_mean(t_quicksort[exp], run);
        //Calculate_mean_shell
        double sd_quicksort = calculate_sd(t_quicksort[exp], run, mean_quicksort);

        mean_bubble = mean_bubble/10;
        mean_selection = mean_selection/10;
        mean_merge = mean_merge/10;

        double SD_Bubble = calculate_sd(t_bubble[exp], run, mean_bubble);
        double SD_Selection = calculate_sd(t_selection[exp], run, mean_selection);
        double SD_Merge = calculate_sd(t_merge[exp], run, mean_merge);


        //Print_insertion_mean_sd
        printf("\nAlgo_insertion: Mean � SD = %.6f � %.6f\n", mean_insertionsort, sd_insertionsort);
        //Print_shell_mean_sd
        printf("Algo_shellsort: Mean � SD = %.6f � %.6f\n", mean_shellsort, sd_shellsort);
        //Print_quick_mean_sd
        printf("Algo_quicksort: Mean � SD = %.6f � %.6f\n", mean_quicksort, sd_quicksort);

        printf("Mean_Bubble : %f\tSD_Bubble : %f\n",mean_bubble,SD_Bubble);
        printf("Mean_Selection : %f\tSD_Selection : %f\n",mean_selection,SD_Selection);
        printf("Mean_Merge : %f\tSD_Merge : %f\n",mean_merge,SD_Merge);

        printf("\n*****************************************************************************************************************************************");
    }
    return 0;
}
