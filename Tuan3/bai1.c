//Bai1: 
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdint.h>
#define RED 2
#define GREEN 1
#define BLUE 3

uint8_t led[3] ={2,1,3};
int main(void)
{
	wiringPiSetup();
	pinMode(RED, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(BLUE, OUTPUT);
    
	softPwmCreate (RED, 0, 100);
	softPwmCreate (GREEN, 0, 100);
	softPwmCreate (BLUE, 0, 100);
	
	softPwmWrite(RED, 0);
	softPwmWrite(GREEN, 0);
	softPwmWrite(BLUE, 0);
    while(1)
	{	    

	for(int i = 0;i<3;i++)
		{
		for(int j = 0; j <= 100; j++)
			{
			softPwmWrite(led[i], j);
			delay(10);
	    	}
		for(int j = 100; j >= 0; j--)
			{
			softPwmWrite(led[i], j);
			delay(10);
	    	}
		}
	}
return 0;

}