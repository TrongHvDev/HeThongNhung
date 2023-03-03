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

uint8_t led[3] ={RED, GREEN, BLUE};
uint8_t redFlag = 0;
uint8_t greenFlag = 0;
uint8_t blueFlag = 0;
uint8_t state = 0;
//------ Interrupt Function----------------------

void ngat_bt1(void){
    redFlag = 1;
    if(state == 1){
      for (int j = 0; j <= 3; j++){  
        for(int i = 0; i < 3; i++){
            digitalWrite(led[i], HIGH);
            delay(100);
            digitalWrite(led[i], LOW);
            delay(100);
        }
      }
    }
}

void ngat_bt2(void){
    if(state == 2){
      for (int j = 0; j <= 3; j++){  
        for(int i = 0; i < 3; i++){
            digitalWrite(led[i], HIGH);
            delay(100);
            digitalWrite(led[i], LOW);
            delay(100);
        }
      }
    }    
}

void ngat_bt3(void){
    if(state == 3){
      for (int j = 0; j <= 3; j++){  
        for(int i = 0; i < 3; i++){
            digitalWrite(led[i], HIGH);
            delay(100);
            digitalWrite(led[i], LOW);
            delay(100);
        }
      }
    }   
}
//-------------------------------------------

int main(void){
// ----------------- Set up---------------
    wiringPiSetup();
	pinMode(RED, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(BLUE, OUTPUT);
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
// ---------------------------------------
//-------- Ngat ngoai cho cac nut nhan----
    wiringPiISR(BT1,INT_EDGE_RISING,&ngat_bt1);
    wiringPiISR(BT2,INT_EDGE_RISING,&ngat_bt2);
    wiringPiISR(BT3,INT_EDGE_RISING,&ngat_bt3);
//-----------------------------------------------
    while(1){
        digitalWrite(RED, HIGH);
        state = 1;
        delay(500);
        state = 0;
        printf("LED = RED\n");
        delay(2000);
        digitalWrite(RED, LOW);

        digitalWrite(GREEN, HIGH);
        state = 2;
        delay(500);
        state = 0;
        printf("LED = GREEN \n");
        delay(2000);
        digitalWrite(GREEN, LOW);

        digitalWrite(BLUE, HIGH);
        state = 3;
        delay(500);
        state = 0;
        printf("LED = BLUE\n");
        delay(3000);
        digitalWrite(BLUE, LOW);


        delay(5000);
    }

    return 0;
}


