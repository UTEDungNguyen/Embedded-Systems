#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <softPwm.h>

#define Red 0
#define Green 2
#define Blue 3

uint8_t led[3] = {3,0,2};
uint16_t duty=0;
int main(void)
{
    wiringPiSetup();
    
    for (int i=0; i<3; i++){
        pinMode(led[i], OUTPUT);
        softPwmCreate (led[i], 0, 100) ;
    }
    
    while(1){
       for (int i =0; i<3; i++){
            for (int j=0; j<21; j++){
                softPwmWrite(led[i], j*5);
                delay(100);
            }
            for (int x=19; x>=0; x--){
                softPwmWrite(led[i], x*5);
                delay(100);
            }
       }

    }
}