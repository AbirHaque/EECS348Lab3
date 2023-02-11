#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define buf_len 100
#define true 1
#define false 0
#define num_months 12
#define round_2(val) (round(val*100)/100)

void bubble_sort_hi2lo_indices(double* arr, int* sorted_indices, int len){
    for (int i = 0; i < len;i++){
        sorted_indices[i]=i;
    }
    double elem1,elem2;
    int tmp,sorted;
    sorted=false;
    while(!sorted){
        sorted=true;
        for(int i = 0; i < len-1;i++){
            elem1 =arr[sorted_indices[i]];
            elem2 =arr[sorted_indices[i+1]];
            if (elem2>elem1){
                tmp=sorted_indices[i];
                sorted_indices[i]=sorted_indices[i+1];
                sorted_indices[i+1]=tmp;
                sorted=false;
            }
        }
    }
}
double average(double* arr, int start, int end, int len){
    double avg=0;
    for(int i=start;i<end;i++)
        avg+=arr[i];
    avg/=((double)len);
    return avg;
}

int main(void) {
    char filename[buf_len];
    char* data[num_months][buf_len];
    double sales[num_months];
    char* months[num_months]={"January","February","March","April","May","June","July","August","September","October","November","December"};
    int sorted_indices_hi2lo[num_months];

    printf("Enter filename: ");
    fflush( stdout );
    scanf("%s",filename);
    FILE* fp;
    fp = fopen(filename, "r");
    printf("Monthly sales report for 2022\n\nMonth Sales\n");
    for (int i = 0; i < num_months; i++) {
        fgets((char * restrict) data[i], buf_len, fp);
        printf("%-15s$%s",(char*)months[i],(char*)data[i]);
        sales[i]=atof((const char *)data[i]);
    }
    fclose(fp);
    
    bubble_sort_hi2lo_indices(sales,sorted_indices_hi2lo,num_months);

    printf("\n\nSales summary:\n");
    printf("%-15s$%.2f (%s)\n","Minimum sales",sales[sorted_indices_hi2lo[num_months-1]],months[sorted_indices_hi2lo[num_months-1]]);
    printf("%-15s$%.2f (%s)\n","Maximum sales",sales[sorted_indices_hi2lo[0]],months[sorted_indices_hi2lo[0]]);
    printf("%-15s$%.2f\n","Average sales",round_2(average(sales,0,num_months,num_months)));

    printf("\nSix-Month moving average report:\n");
    int window_size=6;
    for(int i = 0; i < window_size+1;i++)
        printf("%-10s- %-15s$%.2f\n",months[i],months[window_size+i-1],round_2(average(sales,i,window_size+i,window_size)));
    

    printf("\nSales report (highest to lowest):\n\nMonth Sales\n");
    for(int i = 0; i < num_months; i ++)
        printf("%-15s$%.2f\n",months[sorted_indices_hi2lo[i]],sales[sorted_indices_hi2lo[i]]);

    fflush( stdout );
    return 0;
}
