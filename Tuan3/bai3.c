// Bai 3
#include <wiringPi.h>
#include <softPwm.h>
#include <stdint.h>

// LED Pin - wiringPi pin 0 is BCM_GPIO 17.
#define Red     2
#define Green   1
#define Blue    3
#define BT1     0   //Thay doi mau
#define BT2     4  //Lon len
#define BT3     5  //Nho lai
#define BT4     23

uint8_t led[3] = {2,1,3};
int color = 0;
int x = 0;
uint8_t button[3] ={0,4,5};

uint8_t r[3][5] ={{0,25,50,75,100},{0}   ,{0}};
uint8_t g[3][5] ={{0}   ,{0,25,50,75,100},{0}};
uint8_t b[3][5] ={{0}   ,{0}             ,{0,25,50,75,100}};


void ngat_bt1(void)
{
   color += 1;
   if(color >2)
   {
      color = 0;
   }
}

void ngat_bt2(void)
{  
   x = x + 1;
   if(x>4){x=4;}
}

void ngat_bt3(void)
{  
   x = x - 1;
   if(x<=0){x=0;}

}

int main (void) 
{
   wiringPiSetup();

   for(int i =  0;i<3;i++)
   {
      pinMode (button[i], INPUT);
      pinMode (led[i], OUTPUT);
      softPwmCreate(led[i],0,100);
   }

   wiringPiISR(BT1,INT_EDGE_RISING,&ngat_bt1);
   wiringPiISR(BT2,INT_EDGE_RISING,&ngat_bt2);
   wiringPiISR(BT3,INT_EDGE_RISING,&ngat_bt3);
   
   while(1) 
   {
      printf("%d",color) ;
      printf("%d \n",x);
      softPwmWrite (led[0],r[color][x]);
      softPwmWrite (led[1],g[color][x]);
      softPwmWrite (led[2],b[color][x]);
   }
   
return 0 ;
}
