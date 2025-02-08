#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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
    for (int i = 0; i < n; i++) sum += pow(data[i] - mean, 2);
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

int main(){
    int exp, num_exp = 5;
    int i, n, num[5] = {1000, 5000, 10000, 20000, 50000};
    int t, run = 10;
    clock_t begin;
    clock_t end;
    double t_insertionsort[num_exp][run],t_shellsort[num_exp][run],t_quicksort[num_exp][run];

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

        //Print_insertion_mean_sd
        printf("\nAlgo_insertion: Mean � SD = %.6f � %.6f\n", mean_insertionsort, sd_insertionsort);
        //Print_shell_mean_sd
        printf("Algo_shellsort: Mean � SD = %.6f � %.6f\n", mean_shellsort, sd_shellsort);
        //Print_quick_mean_sd
        printf("Algo_quicksort: Mean � SD = %.6f � %.6f\n", mean_quicksort, sd_quicksort);
        printf("\n******************************************************************************************************************************************");
    }
    return 0;
}
