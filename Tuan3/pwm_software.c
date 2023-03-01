#include <stdio.h>
#include <wiringPi.h>
#include <stdint.h>
#include <softPwm.h>

#define LED     1
#define BT1     0
#define BT2     2

uint16_t duty = 0; 

void ngat_bt1(void){
    duty = duty + 51; 
    if(duty > 1023)
        duty = 1023;
    pwmWrite(LED, duty)
}

int main(void){
    wiringPiSetup();
    pinMode(BT1, INPUT);
    pinMode(BT2, INPUT);
    pinMode(LED, PWM_OUTPUT);

    pwmWrite(LED, duty);
    // pwmSetMode(PWM_MODE_MS);
    // pwmSetClock(...);            // neu can chinh xac thi dung 3 dong nay
    // pwmSetRange(...);
    
    // khai bao ngat
    wiringPiISR(BT1, INT_EDGE_RISING, &ngat_bt1);
    wiringPiISR(BT2, INT_EDGE_RISING, &ngat_bt2);

    while(1){

    }
    return 0;
}