// Bai 3
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdint.h>

#define RED     9
#define GREEN   7
#define BLUE    8
#define BT1     25
#define BT2     24
#define BT3     23
#define BT4     22

uint8_t led[3] = {8,7,9};
int color = 0;
int x = 0;
uint8_t button[3] ={23, 24, 25};

uint8_t r[7][5] ={{0,25,50,75,100},
                    {0},
                    {0},
                    {0,25,50,75,100},
                    {0,25,50,75,100},
                    {0},
                    {0,25,50,75,100}};

uint8_t g[7][5] ={{0},
                  {0,25,50,75,100},
                  {0},
                  {0,25,50,75,100},
                  {0,25,50,75,100},
                  {0,25,50,75,100},
                  {0}};
                  
uint8_t b[7][5] ={{0},
                  {0},
                  {0,25,50,75,100},
                  {0},
                  {0,25,50,75,100},
                  {0,25,50,75,100},
                  {0,25,50,75,100}};


void ngat_bt1(void)
{
   color += 1;
   if(color >6)
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
