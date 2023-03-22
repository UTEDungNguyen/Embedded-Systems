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

uint8_t led[3] = {0,2,3};
uint8_t btn[4] = {21,22,23,24};
uint8_t state = 0;
int n = 0;

void ngatbtn1(void){
    while(digitalRead(btn[0])==0){}
    state += 1;
    if (state > 3){state=1;}   
}

void ngatbtn2(void){
    while(digitalRead(btn[1])==0){}
    n += 25;
    if (n > 100){n=100;};
}

void ngatbtn3(void){
    while(digitalRead(btn[2])==0){}
    n -= 25;
    if (n <= 0){n=0;};
}

int main(void)
{
    wiringPiSetup();

    for (int i=0; i<3; i++){
        pinMode(led[i], OUTPUT);
        softPwmCreate (led[i], 0, 100) ;
    }

    for (int i=0; i<=3; i++){
        pinMode(btn[i], INPUT);
    }
    
    wiringPiISR(btn[0], INT_EDGE_RISING, &ngatbtn1);
    wiringPiISR(btn[1], INT_EDGE_RISING, &ngatbtn2);
    wiringPiISR(btn[2], INT_EDGE_RISING, &ngatbtn3);

    while(1){
        if (state == 1){
            softPwmWrite(led[0], n);
            softPwmWrite(led[1], 0);
            softPwmWrite(led[2], 0);
        }
        if (state == 2){
            softPwmWrite(led[0], 0);
            softPwmWrite(led[1], n);
            softPwmWrite(led[2], 0);
        }
        if (state == 3){
            softPwmWrite(led[0], 0);
            softPwmWrite(led[1], 0);
            softPwmWrite(led[2], n);
        }
    }
}