#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define RED     7
#define GREEN   9
#define BLUE    8
#define BT1     25
#define BT2     24
#define BT3     23
#define BT4     22
#define VN (+7)

time_t rawtime;
struct tm *info;
uint8_t state3;
uint8_t goout;
time_t start_t,end_t;
double diff_t;
uint8_t  rgb[10][3] = {{100,0,0},{0,100,0},{0,0,100}
                    ,{100,100,0},{0,100,100},{100,0,100}
                    ,{100,100,100},{50,0,100},{0,50,100}
                    ,{100,50,50}}; 

void ngat_bt1(void){

}
void ngat_bt2(void){

}
void ngat_bt3(void){
    state3 = 1;
    if(digitalRead(BT3) == 1)
    {
      time(&start_t);
      diff_t = 0;
    }

    while((digitalRead(BT3) == 1)&&(diff_t < 2))
    {
      time(&end_t);
      diff_t = difftime(end_t, start_t);
      if(diff_t >= 2){goout = 1;}
    }
}
void ngat_bt4(void){

}

void TangDoSang(void){
    for(int i = 0; i <= 100; i ++){
        softPwmWrite(GREEN, i);
        delay(10);
    }
}

void GiamDoSang(void){
    for(int i = 100; i >= 0; i --){
        softPwmWrite(GREEN, i);
        delay(10);
    }
}

void DoiMau(void){
    for(int i = 0; i <= 9; i ++){
        softPwmWrite(RED, rgb[i][0]);
        softPwmWrite(GREEN, rgb[i][1]);
        softPwmWrite(BLUE, rgb[i][2]);
        delay(100);
    }
}

void setup(void){
    wiringPiSetup();
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);   
    pinMode(BT1, INPUT);
    pinMode(BT2, INPUT);
    pinMode(BT3, INPUT);
    pinMode(BT4, INPUT);

    softPwmCreate (RED, 0, 100);
    softPwmCreate (GREEN, 0, 100);
    softPwmCreate (BLUE, 0, 100);

    wiringPiISR(BT1,INT_EDGE_RISING,&ngat_bt1);
    wiringPiISR(BT2,INT_EDGE_RISING,&ngat_bt2);
    wiringPiISR(BT3,INT_EDGE_RISING,&ngat_bt3);
    wiringPiISR(BT4,INT_EDGE_RISING,&ngat_bt4);
}

int GetRandom(int min,int max){
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void realTime(void){
    time(&rawtime);
    /* Get GMT time */
    info = gmtime(&rawtime);
    printf("Tại VN: %2d:%02d\n", (info->tm_hour+VN)%24, info->tm_min);
   // return info;
}

int main(void){
    setup();
    while(1){
        DoiMau();
    }
    return 0;
}