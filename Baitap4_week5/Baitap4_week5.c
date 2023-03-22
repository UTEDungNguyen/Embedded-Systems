#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <softPwm.h>
#include <stdlib.h>
#include <time.h>

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
int count = 0;
int r;
int n=0;

//Tạo hàm GetRandom để chỉ định phạm vi sinh số ngẫu nhiên
int GetRandom(int min,int max){
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void ngat_btn_red(void){
    while(digitalRead(btn[0])==0){}
    state = 1;
}

void ngat_btn_green(void){
    while(digitalRead(btn[1])==0){}
    state = 2;
}

void ngat_btn_blue(void){
    while(digitalRead(btn[2])==0){}
    state = 3;
}

int main(void)
{
    wiringPiSetup();

    for (int i=0; i<3; i++){
        pinMode(led[i], OUTPUT);
        digitalWrite(led[i], LOW);
    }

    for (int i=0; i<=3; i++){
        pinMode(btn[i], INPUT);
    }
    
    wiringPiISR(btn[0], INT_EDGE_RISING, &ngat_btn_red);
    wiringPiISR(btn[1], INT_EDGE_RISING, &ngat_btn_green);
    wiringPiISR(btn[2], INT_EDGE_RISING, &ngat_btn_blue);

    while(1){
        //Sử dụng hàm srand để thay đổi số nguồn sử dụng trong hàm rand
        srand((unsigned int)time(NULL));
        int r = GetRandom(1,3);
        state =0;
        count =0;
        // printf("%d\n",r);
        digitalWrite(led[r-1], HIGH);
        for (int i=1; i<=30; i++){
            count++;
            delay(100);
            // printf("%d\n state :", state);
            // printf("%d\n r :", r);
            // printf("%d\n count :", count);
            if (count <= 20){   // 2s
                if (r == state){
                    digitalWrite(led[r-1], LOW);
                    for (int i =0; i<3; i++){
                        digitalWrite(led[i], HIGH);
                        delay(1000/(3*2));
                        digitalWrite(led[i], LOW);
                        delay(1000/(3*2));
                    }
                    printf("You Won The Game\n");
                    break;
                }
            }

            if (count==30 && state >= 0){
                count=30;
                printf("You Lose The Game\n");
                digitalWrite(led[r-1], LOW);    
                while(count==30){}
            }
        }
    }
}