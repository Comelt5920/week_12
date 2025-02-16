#include <stdio.h>
#include <string.h>
//ฟังก์ชั่นเปรียบเทียบค่าที่มากที่สุด
int max(int a,int b){
    if(a>b){
        return a;
    }
    else{return b;}
}
//ฟังก์ชั่น Knapsack (สร้างตาราง)
void Knapsack(int w[],int v[],int W,int n){
    int b[n+1][W+1];
    int max_W=0;
    memset(b, 0, sizeof(b));
    for(int i=1;i<=n;i++){
        for(int j=0;j<=W;j++){
            if(w[i]>j){
                b[i][j] = b[i-1][j];
            }
            else{b[i][j] = max(b[i-1][j],b[i-1][j-w[i]]+v[i]);}
        }
    }
    //คำนวณค่า Weight ที่มากสุด
    int j = W;
    for (int i = n; i > 0 && j > 0; i--) {
        if (b[i][j] != b[i-1][j]) {
            max_W += w[i];  
            j -= w[i]; 
        }
    }
    printf("\nMaximum value : %d",b[n][W]);
    printf("\nMaximum weight : %d\n",max_W);
}

int main(){
    //กำหนดค่าต่างๆที่ใช้
    int n=4,W=5;
    int w[]={0,2,1,3,2};
    int v[]={0,12,10,20,15};
    Knapsack(w,v,W,n);
    return 0;
}