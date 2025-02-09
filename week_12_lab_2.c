#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#define num_exp 5
#define run 10
#define max_size 50000
//สุ่มข้อมูล
void get_data(int n, int *data) {
    int i;
    time_t t;
    srand((unsigned) time(&t));

    for (i = 0; i < n; i++) {
        //printf("%d ", rand() % 10);
        data[i] = rand() % 100;
    }
}
//คำนวณ SD ส่วน mean เวลาหารจำนวนรอบ
double calculate_sd(double data[], int n, double mean) {
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += pow(data[i] - mean, 2);
    return sqrt(sum / n);
}
//ฟังก์ชัน insertion sort
void insertionsort(int data[],int n){
    for(int i=1;i<n;i++){
        int tmp = data[i];
        int j=i;
        while(j>0 && data[j-1]>tmp){
            data[j]  = data[j-1];
            j=j-1;
        }
        data[j]=tmp;
    }
}
//ฟังก์ชัน shell sort
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
//ฟังก์ชัน swap เป็นส่วนของ partition ใน quicksort
void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}
//ฟังก์ชัน partition ของ quick sort เป็น pivot
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
    }
    return j;
}
//ฟังก์ชัน quick sort
void quicksort(int data[], int p, int r){
    if (p<r){
        int j = partition(data, p, r);
        quicksort(data, p, j-1);
        quicksort(data, j+1, r);
    }
}
//ฟังก์ชัน bubble sort
void BubbleSort(int data[],int n){
    int swapped = 1;
    while(swapped==1){
        swapped =0;
        for(int i=0;i<n-1;i++){
            if(data[i] > data[i+1]){
                int tmp = data[i];
                data[i] = data[i+1];
                data[i+1] = tmp;
                swapped = 1;
            }
        }
    }
}
//ฟังก์ชัน selection sort
void Selection(int data[],int n){
    int tmp,j,k;
    for(int i=0;i<n;i++){
        tmp = data[i],k=i;
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
//ฟังก์ชัน merge sort
void Merge(int *A, int p, int q, int r);
void Merge_Sort(int *A,int p,int r){
    if(p<r){
        int q = p+(r-p)/2;
        Merge_Sort(A,p,q);
        Merge_Sort(A,q+1,r);
        Merge(A,p,q,r);
    }
}
//ฟังก์ชัน merge ใน merge sort
void Merge(int *A,int p,int q,int r){
    int n1 = q-p+1;
    int n2 = r-q;
    int L[max_size], R[max_size];
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
//ส่วนหลัก
int main(){
    int exp; //ส่วนกำหนดว่าตอนนี้ควรใช้ข้อมูลใน num[]ใหนจาก 1 ถึง 5
    int i, n, num[5] = {1000,5000,10000,20000,50000};//จำนวนข้อมูลใน data
    int t; //กำหนดจำนวนรอบในการ run
    clock_t begin; //จับเวลา time.h
    clock_t end; //หยุดเวลา time.h
    double t_insertionsort[num_exp][run],t_shellsort[num_exp][run],t_quicksort[num_exp][run],t_bubble[num_exp][run], t_selection[num_exp][run],t_merge[num_exp][run];//ประกาศตัวแปรเวลา
    double mean_bubble=0,mean_selection=0,mean_merge=0,mean_insertionsort=0, mean_shellsort=0, mean_quicksort=0;//กำหนดตัวแปร mean

    for (exp=0; exp<num_exp; exp++){ //run โดยใช้ข้อมูล index ใน num[]
        n = num[exp]; //กำหนดตัวแปร n
        printf("\nn= %d\n", n);//ปริ้น n = ค่า num[exp]
        int data[max_size];//สร้าง arr data
        for (t = 0; t < run; t++) { //ลูปรับจำนวนรอบ
            printf("\nrun %d\t", t + 1);//print run = จำนวนรอบปัจจุบัน
            //////////////////////////////BubbleSort_Zone//////////////////////////////
            get_data(n, data); //รับค่าข้อมูลที่สุ่ม
            begin = clock(); //จับเวลา
            BubbleSort(data,n); //เรียกใช้ฟังก์ชัน
            end = clock(); //หยุดเวลา
            t_bubble[exp][t] = (double)(end - begin) / CLOCKS_PER_SEC; //คำนวณเวลาที่ใช้รัน ฟังก์ชัน
            mean_bubble = mean_bubble+t_bubble[exp][t]; //รวมค่าเวลาแต่ละรอบ
            printf("time_bubble_sort : %f   ",t_bubble[exp][t]); //ปริ้นเวลาที่ใช้ของรอบนั้น
            //////////////////////////////Selection_Zone//////////////////////////////
            get_data(n, data);
            begin = clock();
            Selection(data,n);
            end = clock();
            t_selection[exp][t] = (double)(end - begin) / CLOCKS_PER_SEC;
            mean_selection = mean_selection+t_selection[exp][t];
            printf("time_selection_sort : %f   ", t_selection[exp][t]);

            //////////////////////////////Insertion_Zone//////////////////////////////
            get_data(n, data);
            begin = clock();
            insertionsort(data, n);
            end = clock();
            t_insertionsort[exp][t] = ((double) (end - begin)/ CLOCKS_PER_SEC);
            mean_insertionsort=mean_insertionsort+t_insertionsort[exp][t];
            printf("time_insertion_sort : %f   ", t_insertionsort[exp][t]);

            //////////////////////////////Shell_Zone//////////////////////////////
            get_data(n, data);
            begin = clock();
            shellsort(data, n);
            end = clock();
            t_shellsort[exp][t] = ((double) (end - begin)/ CLOCKS_PER_SEC);
            mean_shellsort=mean_shellsort+t_shellsort[exp][t];
            printf("time_shellsort_sort : %f   ", t_shellsort[exp][t]);

            //////////////////////////////Merge_Zone//////////////////////////////
            get_data(n, data);
            begin = clock();
            Merge_Sort(data,0,n-1);
            end = clock();
            t_merge[exp][t] = (double)(end - begin) / CLOCKS_PER_SEC;
            mean_merge = mean_merge+t_merge[exp][t];
            printf("time_Merge_sort : %f   ",t_merge[exp][t]);

            //////////////////////////////Quick_Zone//////////////////////////////
            get_data(n, data);
            begin = clock();
            quicksort(data, 0, n-1);
            end = clock();
            t_quicksort[exp][t] = ((double) (end - begin)/ CLOCKS_PER_SEC);
            mean_quicksort = mean_quicksort+t_quicksort[exp][t];
            printf("time_quick_sort : %f   ", t_quicksort[exp][t]);

        }
        //คำนวณค่า mean โดยการเอาเวลาที่รวมมาหารจำนวนrun
        mean_insertionsort = mean_insertionsort/run;
        mean_shellsort = mean_shellsort/run;
        mean_quicksort = mean_quicksort/run;
        mean_bubble = mean_bubble/run;
        mean_selection = mean_selection/run;
        mean_merge = mean_merge/run;

        //คำนวนค่า sd โดยการเรียกฟังก์ชัน calculate_sd
        double sd_insertionsort = calculate_sd(t_insertionsort[exp], run, mean_insertionsort);
        double sd_shellsort = calculate_sd(t_shellsort[exp], run, mean_shellsort);
        double sd_quicksort = calculate_sd(t_quicksort[exp], run, mean_quicksort);
        double sd_bubble = calculate_sd(t_bubble[exp], run, mean_bubble);
        double sd_selection = calculate_sd(t_selection[exp], run, mean_selection);
        double sd_merge = calculate_sd(t_merge[exp], run, mean_merge);

        //ปริ้นค่า mean & sd
        printf("\n\nMean_Bubble\t : %f\tSD_Bubble\t : %f\n",mean_bubble,sd_bubble);
        printf("Mean_Selection\t : %f\tSD_Selection\t : %f\n",mean_selection,sd_selection);
        printf("Mean_insertion\t : %f\tSD_insertion\t : %f\n",mean_insertionsort,sd_insertionsort);
        printf("Mean_shell\t : %f\tSD_shell\t : %f\n",mean_shellsort,sd_shellsort);
        printf("Mean_Merge\t : %f\tSD_Merge\t : %f\n",mean_merge,sd_merge);
        printf("Mean_quicksort\t : %f\tSD_quicksort\t : %f\n",mean_quicksort,sd_quicksort);
        printf("\n*********************************************************************************************************************************************************************************************************");

        //reset mean & sd =0 ก่อนจะถึง num[] ตัวต่อไป
        mean_bubble=0,mean_selection=0,mean_merge=0,mean_insertionsort=0, mean_shellsort=0, mean_quicksort=0;
        sd_bubble=0, sd_selection=0, sd_insertionsort=0, sd_shellsort=0, sd_merge=0, sd_quicksort=0;

    }
    return 0;
}
