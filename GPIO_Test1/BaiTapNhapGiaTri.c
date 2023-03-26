/*
    a.Nhap gia tri: (Do sang, R, G, B) va hien thi dung
    b.Chuyen qua lai 2 che do:
        Tang giam do sang
        Chuyen qua lai giua cac mau (10 mau)
    yeu cau giu duoc mau sac, do sang khi doi che do
    c.Them chuc nang on/off cho he thong theo thoi gian thuc

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
#define VN (+7)

time_t rawtime, timeGet;
int timer[2];
uint8_t doSang, R, G, B;
struct tm *info;
uint8_t hour_on, min_on;
uint8_t hour_off, min_off;

uint8_t r[] ={100, 0,   0,  100, 100,   0,  100,    70,     100,   20};

uint8_t g[] ={0, 100,   0,  100, 100, 100,    0,    20,      50,  100};
                  
uint8_t b[] ={0,   0, 100,    0, 100, 100,  100,   100,      30,   30};


int GetRandom(int min,int max){
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void setup(void){
    wiringPiSetup();
    pinMode(RED, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(BLUE, OUTPUT);   

    softPwmCreate (RED, 0, 100);
    softPwmCreate (GREEN, 0, 100);
    softPwmCreate (BLUE, 0, 100);
}

int main(void){
    begin:
    setup();
    time(&rawtime);
    /* Get GMT time */
    info = gmtime(&rawtime);
    printf("Tại VN: %2d:%02d\n", (info->tm_hour+VN)%24, info->tm_min);

    printf("Nhap gia tri theo cu phap: (Do_Sang R G B): \n");
    scanf("%d, %d, %d, %d", &doSang, &R, &G, &B);

    printf("Nhap gia tri thoi gian on (09:41):\n");
    scanf("%d:%d", &hour_on, &min_on);

    printf("Nhap gia tri thoi gian off (09:41):\n");
    scanf("%d:%d", &hour_off, &min_off);

    printf("Hen gio thanh cong\n");
    printf("Thoi gian ON la: %d:%d\n", hour_on, min_on);
    printf("Thoi gian OFF la: %d:%d\n", hour_off, min_off);
// Cho den thoi gian on
    while(1){
        time(&rawtime);
        info = gmtime(&rawtime);
        if((info->tm_hour+VN)%24 == hour_on && info->tm_min == min_on)  break;
    }

    if(R == 1)      softPwmWrite(RED, doSang);
    if(G == 1)      softPwmWrite(GREEN, doSang);
    if(B == 1)      softPwmWrite(BLUE, doSang);
     
    delay(1000);
    while(1){
       
            for (int i = 0; i <= 10; i++){  
                for (float j = 1; j >= 0; j -= 0.1){
                    softPwmWrite(RED, r[i]*j);
                    softPwmWrite(GREEN, g[i]*j);
                    softPwmWrite(BLUE, b[i]*j);
                    delay(100);
                } 

                time(&rawtime);
                info = gmtime(&rawtime);    
                if((info->tm_hour+VN)%24 == hour_off && info->tm_min == min_off)   goto begin;  

                for (float j = 0; j <= 1; j += 0.1){
                    softPwmWrite(RED, r[i]*j);
                    softPwmWrite(GREEN, g[i]*j);
                    softPwmWrite(BLUE, b[i]*j);
                    delay(100);
                } 
                delay(GetRandom(2, 3) *1000);
            }
    }
}


