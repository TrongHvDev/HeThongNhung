#include <stdio.h>
#include <time.h>
 
#include <stdlib.h>     
int num, sum;
char avg[10];
void delay(int number_of_seconds)
{
   int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}
 int main()
{
    int i;
    for (i = 0; i < 10; i++) {
        sum = 0;
        for (int j = 0; j <= 10; j++){
            num =  rand() % 100 + 1;
            avg[j] = num;
            sum = sum + num;
            
        }
        for(int k =0; k<=10; k++){
                printf("%d \t", avg[k]);

            }
        float a ;
            a = sum /10.0;
            delay(1000);
            printf("%.2f \n", a);

        
        


    }
    return 0;
}