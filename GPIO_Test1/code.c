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

void ngat_bt1(void){

}
void ngat_bt2(void){

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
int main(void){
    setup();
    while(1){
        
    }
    return 0;
}