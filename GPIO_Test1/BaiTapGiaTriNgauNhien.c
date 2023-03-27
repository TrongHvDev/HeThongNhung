/*
    a.Nhan BT1 de bat LED GREEN, do sang 50%
    b.Nhan BT2 de tao so ngau nhien (20, 100) moi 2s,
    in ra man hinh
        Voi gia tri <= 80, LED GREEN tang giam do sang
          voi chu ki 1s
        Voi gia tri > 80, ngung tao so ngau nhien va
          in ra man hinh chu "Warning"
    c.Sau khi he thong warning, nhan BT3 trong vong 4s
    de reset he thong, neu trong vong 4s khong kip nhan BT3
    led chuyen sang che do doi mau, va chi reset khi nhan giu
    BT3 trong 2s
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

uint8_t state1 = 0;
uint8_t state2 = 0;
uint8_t state3 = 0;
uint8_t goout = 0;
unsigned int start = 0,  end = 0;
unsigned int time_millis = 0;
uint8_t randomNumber = 0;
time_t start_t,end_t;
double diff_t;

uint8_t  rgb[10][3] = {{100,0,0},{0,100,0},{0,0,100}
                    ,{100,100,0},{0,100,100},{100,0,100}
                    ,{100,100,100},{50,0,100},{0,50,100}
                    ,{100,50,50}}; 

void ngat_bt1(void){
    state1 = 1;

}
void ngat_bt2(void){
    state2 = 1;

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


int main(void){
    setup();
    begin:
    state1 = state2 = state3 = goout = 0;
    softPwmWrite(RED, 0);
    softPwmWrite(GREEN, 0);
    softPwmWrite(BLUE, 0);
    while(1){
// -----------------------Button 1----------------------------------------------------
    if(state1 == 1)     softPwmWrite(GREEN, 50);
//--------------------Button 2----------------------------------------
    while(state2 == 1){
        srand((unsigned int)time(NULL));
        randomNumber = GetRandom(20, 100);
        printf("%d\n", randomNumber);
        if(randomNumber <= 80){
            TangDoSang();
            GiamDoSang();
        }
        if(randomNumber > 80){
            start = millis();
            while(1){ 
                softPwmWrite(GREEN, 0);              
                softPwmWrite(RED, 80);
                delay(125);
                softPwmWrite(RED, 0);
                delay(125);
                printf("Warning !\n");
                end = millis();
                time_millis = end - start;
                if(time_millis > 4000){
                    while(1){
                        DoiMau();
                        if(goout == 1)  goto begin;
                    }
                }
                if (state3 == 1)    goto begin;
            }
        }
    }

    }
    return 0;
}