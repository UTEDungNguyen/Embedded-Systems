#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <softPwm.h>
#include <stdlib.h>
#include <time.h>

#define Red 21
#define Green 22
#define Blue 23

#define BTN1 0
#define BTN2 2

uint8_t led[3] = {21,22,23};
uint8_t btn[2] = {0,2};
uint8_t state = 0;
int storage_time = 0;
int n = 0;
int r=0;
int count = 0;

unsigned char array[10];

//Tạo hàm GetRandom để chỉ định phạm vi sinh số ngẫu nhiên
int GetRandom(int min,int max){
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void ngatbtn1(void){
    storage_time = millis();
    printf("%d\n state :", storage_time);
    
    n += 25;
    if (n > 100){n=0;};
}

void ngatbtn2(void){
    while(digitalRead(btn[1])==0){}
    state += 1;
    if (state > 2){state=1;}   
    if (state == 1){
        for (int i = 0; i<3; i++){
            softPwmWrite(led[i], 0);
        }
    }
}


int main(void)
{
    wiringPiSetup();

    for (int i=0; i<3; i++){
        pinMode(led[i], OUTPUT);
        softPwmCreate (led[i], 0, 100) ;
    }

    for (int i=0; i<=1; i++){
        pinMode(btn[i], INPUT);
    }
    
    wiringPiISR(btn[0], INT_EDGE_RISING, &ngatbtn1);
    wiringPiISR(btn[1], INT_EDGE_RISING, &ngatbtn2);

    for (int i = 0; i<10; i++){
        array[i] = GetRandom(0,100);      
    }

    while(1){
        //Sử dụng hàm srand để thay đổi số nguồn sử dụng trong hàm rand
        srand((unsigned int)time(NULL));
        // int r = GetRandom(0,2);
        if (state == 1){
            softPwmWrite(led[1], n);
            delay(1000/6);
            softPwmWrite(led[1], 0);
            delay(1000/6);
        }
        if (state == 2){
            for (int i = 0; i<10; i++){
                if (state == 1){break;}
                if (digitalRead(btn[0])==1){break;}
                softPwmWrite(led[0], array[i]); 
                softPwmWrite(led[1], array[10-i]);    
                softPwmWrite(led[2], array[i]);   
                delay(1000);     
            }
        }
        if (digitalRead(btn[0])==1){
            if ((millis() - storage_time) >= 2000){
                state = 0;
                printf("%d\n millis :", millis());
                for (int i = 0; i<3; i++){
                    softPwmWrite(led[i], 0);
                }
            }
        }
    }
}