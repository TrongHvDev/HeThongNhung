#include <stdio.h>
#include <wiringPi.h>

#define LED 1   //pin12
#define BT  0   //pin11

void interrupt_func (void)
{
    if(digitalRead(BT) == 1)
        digitalWrite(LED, HIGH);
    else
        digitalWrite(LED, LOW)
}

int main(void)
{
    wiringPiSetup();
    pinMode(BT, INPUT);
    pinMode(LED, OUTPUT);
    wiringPiISR (BT, INT_EDGE_BOTH, &interrupt_func);    //khai bao ngat, moi nut nhan 1 ham ngat

}

