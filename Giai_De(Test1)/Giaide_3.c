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

#define VNA (+7)

uint8_t led[3] = {21,22,23};
uint8_t btn[4] = {0,2,4,5};
uint8_t state = 0;
int r = 0;
int array[10];
int storage_time_4s = 0;
int storage_time_final = 0;
int storage_time = 0;
int a = 0;
int wait_time = 1000/8;
int time_now;
int time_load;
int count = 0 ;

//Tạo hàm GetRandom để chỉ định phạm vi sinh số ngẫu nhiên
int GetRandom(int min,int max){
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void ngatbtn1(void){
    state = 1;
}

void ngatbtn2(void){
    state = 2;
}

void ngatbtn3(void){
    if (count == 0){
        state = 0;
    }
    else {
        storage_time_final = millis();
        printf("storage time final : %d\n",storage_time_final);
    }
}

int main(void)
{
    wiringPiSetup();

    for (int i=0; i<3; i++){
        pinMode(led[i], OUTPUT);
        softPwmCreate (led[i], 0, 100) ;
    }

    for (int i = 0; i<7; i++){
        array[i] = GetRandom(0,100);      
    }

    wiringPiISR(btn[0], INT_EDGE_RISING, &ngatbtn1);
    wiringPiISR(btn[1], INT_EDGE_RISING, &ngatbtn2);
    wiringPiISR(btn[2], INT_EDGE_RISING, &ngatbtn3);


    state = 0;
    count = 0;

    while(1){
        //Sử dụng hàm srand để thay đổi số nguồn sử dụng trong hàm rand
        srand((unsigned int)time(NULL));

        if (state == 0){
            softPwmWrite(led[0], 0);
            softPwmWrite(led[1], 0);
        }

        while (state == 1){
            softPwmWrite(led[1], 50);
        }
        
        while (state == 2){
            r = GetRandom(20,100); 
            printf("random : %d\n",r);
            delay(1000);
            storage_time = millis();
            printf("storage time : %d\n",storage_time);
            state = 1;
            // storage_time_1s = millis();
            while (state == 1 && r <= 80){
                for (int j=0; j<6; j++){
                    printf("millis up: %d\n",millis());
                    if ((millis() - storage_time) >= 2000){
                        state = 2;
                        break;
                    }
                    a = j*20;
                    softPwmWrite(led[1], a);
                    delay(100);
                    if(a >= 100){
                        a = 100;
                        break;   
                    }
                }
                for (int x=1; x<=4; x++){
                    printf("millis down: %d\n",millis());
                    if ((millis() - storage_time) >= 2000){
                        state = 2;
                        break;
                    }
                    int b = a-x*20;
                    softPwmWrite(led[1], b);
                    delay(100);
                    if(b <= 0){
                        b = 0;
                        break;   
                    }
                }
            }
            softPwmWrite(led[1], 0);
            if (r > 80){
                state = 3;
                printf("Warning !! \n");
                storage_time_4s = millis();
            }
        }

        while (state == 3){
            time_load = millis();
            if  (time_load - time_now >= wait_time){
                time_now = millis();
                if(digitalRead(led[0]) == 0){
                     softPwmWrite(led[0], 80);
                    //  printf("on\n");
                }
                if(digitalRead(led[0]) == 1){
                     softPwmWrite(led[0], 0);
                    //  printf("off\n");
                }
            }
            if ((millis() - storage_time_4s) < 4000 && state == 0){
                break;
            }
            if ((millis() - storage_time_4s) >= 4000){
                count = 1;
                break;
            }
        }

        while (count == 1){
            for (int i = 0; i<7; i++){
                printf("%d\n millis up 1:",millis());
                softPwmWrite(led[0], array[i]); 
                softPwmWrite(led[1], array[10-i]);    
                softPwmWrite(led[2], array[i]);   
                delay(100);  
                if (digitalRead(btn[2])==1){
                    if ((millis() - storage_time_final) >= 2000){
                        state = 0;
                        count = 0;
                        printf("%d\n millis up 2:", millis());
                        for (int i = 0; i<3; i++){
                            softPwmWrite(led[i], 0);
                        }
                    }
                }
            } 
        }
    }
}