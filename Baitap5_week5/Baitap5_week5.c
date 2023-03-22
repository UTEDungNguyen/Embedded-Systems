#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <softPwm.h>
#include <stdlib.h>
#include <time.h>

uint8_t led[3] = {0,2,3};
uint8_t btn[4] = {21,22,23,24};
uint8_t state = 0;
int count = 0;
int r,total,average,del;
int n=0;
int time_now;
int time_wait = 1000;

//Tạo hàm GetRandom để chỉ định phạm vi sinh số ngẫu nhiên
int GetRandom(int min,int max){
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void ngat_btn_1(void){
    while(digitalRead(btn[0])==0){}
    state = 1;
}


int main(void)
{
    wiringPiSetup();

    for (int i=0; i<3; i++){
        pinMode(led[i], OUTPUT);
        digitalWrite(led[i], LOW);
    }

    pinMode(btn[0], INPUT);
    
    wiringPiISR(btn[0], INT_EDGE_RISING, &ngat_btn_1); 

    while(1){
        //Sử dụng hàm srand để thay đổi số nguồn sử dụng trong hàm rand
        srand((unsigned int)time(NULL));
        while(n<=11){
            n++;
            total += time_now;
            // printf("%d\n", total);
            if (n==11){
                average = total/10;
                printf("Thoi gian nhan nut trung binh sau 10 lan nhan la : %d ms\n", average);
                return 0;
            }
            int r = GetRandom(1,3);
            state =0;
            count =0;
            time_now = 0;
            digitalWrite(led[r-1], HIGH);
            for (int i=1; i<=time_wait; i++){
                delay(1);  
                if (state == 0 && count ==0){time_now++;}
                if (state == 1 && count == 0){
                    digitalWrite(led[r-1], LOW);              
                    printf("Thoi gian nhan nut lan %d la : %d ms\n",n, time_now);
                    state = 0;
                    count++;
                }
                if (i>=time_wait && count == 0){
                    time_now = 0;
                    printf("...\n");
                    digitalWrite(led[r-1], LOW);    
                }
            }
            int del = GetRandom(1,3);
            delay(del*1000);
        }
        
    }
}