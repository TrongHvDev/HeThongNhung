/*
    a.Nhan BT1 de thay doi do sang LED
    b.Nhan BT2 de chuyen qua lai 2 che do:
        Chop tat  f = 3hz
        Chuyen qua lai giua cac mau (10 mau)
    c.Nhan giu BT1 trong 2s de tat LED
*/

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

uint8_t  rgb[10][3] = {{100,0,0},{0,100,0},{0,0,100}
                    ,{100,100,0},{0,100,100},{100,0,100}
                    ,{100,100,100},{50,0,100},{0,50,100}
                    ,{100,50,50}}; 

float duty;
uint8_t count = 0;
uint8_t state2 = 0;
uint8_t index = -1;
uint8_t goout = 0;
time_t start_t,end_t;
double diff_t;

void ngat_bt1(void){
    if(count == 0){
       duty += 0.1;
       if (duty >= 1){
        duty = 1;
        count = 1;
       }
    }

    if(count == 1){
       duty -= 0.1;
       if (duty <= 0){
        duty = 0;
        count = 0;
       }
    }
    
    if(digitalRead(BT1) == 1)
    {
      time(&start_t);
      diff_t = 0;
    }

    while((digitalRead(BT1) == 1)&&(diff_t < 2))
    {
      time(&end_t);
      diff_t = difftime(end_t, start_t);
      if(diff_t >= 2){goout = 1;}
    }

}

void ngat_bt2(void){
    state2 ++;
    if(state2 % 2 == 1)     index ++;
    if(state2 >= 2)  state2 = 0;
    if(index > 9)  index = 0;
}

void ngat_bt3(void){

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
}


void Button1(void){
    softPwmWrite(RED, rgb[index][0]*duty);
    softPwmWrite(GREEN, rgb[index][1]*duty);
    softPwmWrite(BLUE, rgb[index][2]*duty);
}


int main(void){
    setup();
    begin:
    duty = 0;  
    goout = 0;
    while(1){
        Button1();
        while(state2 % 2 == 1){
            softPwmWrite(RED, rgb[index][0]*duty);
            softPwmWrite(GREEN, rgb[index][1]*duty);
            softPwmWrite(BLUE, rgb[index][2]*duty);
            printf("%d\n", goout);
            if(goout == 1)  goto begin;
        }
        while(state2 % 2 == 0){
            softPwmWrite(RED, rgb[index][0]*duty);
            softPwmWrite(GREEN, rgb[index][1]*duty);
            softPwmWrite(BLUE, rgb[index][2]*duty);
            delay(167);
            softPwmWrite(RED, 0);
            softPwmWrite(GREEN, 0);
            softPwmWrite(BLUE, 0);
            delay(167);
            printf("%d\n", goout);
            if(goout == 1)  goto begin;
        }
    }
    return 0;
}