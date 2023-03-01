//Bai 2:

#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdint.h>
#define RED     2
#define GREEN   1
#define BLUE    3
#define BT1     0
#define BT2     21
#define BT3     22
#define BT4     23

int main(void)
{
	wiringPiSetup();
	pinMode(RED, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(BLUE, OUTPUT);    
	softPwmCreate (RED, 0, 100);
		
	softPwmWrite(RED, 0);
	digitalWrite(GREEN, 0);
	digitalWrite(BLUE, 0);
    
    while(1)
	{	    
        if(digitalRead(BT1) == 1)   softPwmWrite(RED, 25);
        if(digitalRead(BT2) == 1)   softPwmWrite(RED, 50);
        if(digitalRead(BT3) == 1)   softPwmWrite(RED, 75);
        if(digitalRead(BT4) == 1)   softPwmWrite(RED, 100);
	
	}
return 0;

}