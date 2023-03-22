#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <softPwm.h>

#define Red 0
#define Green 2
#define Blue 3

#define BTN1 21
#define BTN2 22
#define BTN3 23
#define BTN4 24

uint8_t led[3] = {3,0,2};
uint8_t btn[4] = {21,22,23,24};
uint16_t duty=0;

void ngatbtn1(void){
    softPwmWrite(Red, 25);
}

void ngatbtn2(void){
    softPwmWrite(Red, 50);
}

void ngatbtn3(void){
    softPwmWrite(Red, 75);
}

void ngatbtn4(void){
    softPwmWrite(Red, 100);
}

int main(void)
{
    wiringPiSetup();
    pinMode(Red, OUTPUT);
    softPwmCreate (Red, 0, 100) ;
    softPwmWrite(Red, 0);

    for (int i=0; i<=3; i++){
        pinMode(btn[i], INPUT);
        pullUpDnControl (btn[i], PUD_UP);
    }
    
    wiringPiISR(btn[0], INT_EDGE_BOTH, &ngatbtn1);
    wiringPiISR(btn[1], INT_EDGE_BOTH, &ngatbtn2);
    wiringPiISR(btn[2], INT_EDGE_BOTH, &ngatbtn3);
    wiringPiISR(btn[3], INT_EDGE_BOTH, &ngatbtn4);

    while(1){

    }
}