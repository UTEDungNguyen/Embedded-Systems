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
uint8_t btn[2] = {0,2};
uint8_t state = 0;
int storage_time = 0;
int storage_time_1 = 0;
int n = 0;
int r=0;
int count = 0;
int A,R,G,B;
int array[10];
int a = 0;
char string[3];
char string_1[3];
char dot[1];
int min_on,hour_on;
int min_off,hour_off;

//Tạo hàm GetRandom để chỉ định phạm vi sinh số ngẫu nhiên
int GetRandom(int min,int max){
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

int main(void)
{
    wiringPiSetup();

    for (int i=0; i<3; i++){
        pinMode(led[i], OUTPUT);
        softPwmCreate (led[i], 0, 100) ;
    }

    for (int i = 0; i<10; i++){
        array[i] = GetRandom(0,100);      
    }

    for (int i = 0; i<10; i++){
        array[i] = GetRandom(0,100);      
    }

    state = 0;

    scanf("%d %d %d %d", &array[0], &array[1], &array[2], &array[3]);
    printf("%d %d %d %d\n", array[0], array[1], array[2], array[3]);

    scanf("%s %2d %s %02d", string, &hour_on, dot, &min_on);
    printf("%s %2d %s %02d\n", string, hour_on, dot, min_on);

    scanf("%s %2d %s %02d", string_1, &hour_off, dot, &min_off);
    printf("%s %2d %s %02d\n", string_1, hour_off, dot, min_off);

    while(1){
        //Sử dụng hàm srand để thay đổi số nguồn sử dụng trong hàm rand
        srand((unsigned int)time(NULL));

        time_t rawtime;
        struct tm *info;

        time(&rawtime);
        /* Get GMT time */
        info = gmtime(&rawtime );

        if (string[1]== 'n' && hour_on == (info->tm_hour+VNA)%24 && min_on == info->tm_min){
            state = 1;
        }

        if (string_1[1]== 'f' && hour_off == (info->tm_hour+VNA)%24 && min_off == info->tm_min){
            state = 0;
            for (int i = 0; i<3; i++){
                softPwmWrite(led[i], 0);
            }
        }

        // printf("Tại VNAM: %2d:%02d\n", (info->tm_hour+VNA)%24, info->tm_min);

        // Display PwmLed
        if (state == 1){
            softPwmWrite(led[0], array[1]*array[0]);
            softPwmWrite(led[1], array[2]*array[0]);
            softPwmWrite(led[2], array[3]*array[0]);
            state = 2;
        }
        storage_time = millis();
        // printf("%d\n storage time :",storage_time);
        // int a = array[0];
        // Chon 3s
        while(state == 2){
            a = array[0];
            for (int j=0; j<6; j++){
                printf("%d\n millis up:",millis());
                if ((millis() - storage_time) >= 2000){
                    state = 3;
                    break;
                }
                softPwmWrite(led[0], array[1]*(a + j*20));
                softPwmWrite(led[1], array[2]*(a + j*20));
                softPwmWrite(led[2], array[3]*(a + j*20));              
                delay(100);
                printf("%d\n", array[1]*(a + j*20));
                if(array[1]*(a + j*20) >= 100){
                    a = 100;
                    break;   
                }
            }
            for (int x=1; x<=4; x++){
                printf("%d\n millis down:",millis());
                if ((millis() - storage_time) >= 2000){
                    state = 3;
                    break;
                }
                softPwmWrite(led[0], array[1]*(a - x*20));
                softPwmWrite(led[1], array[2]*(a - x*20));
                softPwmWrite(led[2], array[3]*(a - x*20));
                printf("%d\n", array[1]*(a - x*20));
                delay(100);
            }
            a = 0;
        }

        storage_time_1 = millis();
        // printf("%d\n storage time 1:",storage_time_1);

        while (state == 3){
            for (int i = 0; i<10; i++){
                printf("%d\n millis up 1:",millis());
                if ((millis() - storage_time_1) >= 2000){
                    state = 1;
                    break;
                }
                softPwmWrite(led[0], array[i]); 
                softPwmWrite(led[1], array[10-i]);    
                softPwmWrite(led[2], array[i]);   
                delay(100);  
            }

        }

    }
        // if (state == 2){
        //     for (int i = 0; i<10; i++){
        //         if (state == 1){break;}
        //         if (digitalRead(btn[0])==1){break;}
        //         softPwmWrite(led[0], array[i]); 
        //         softPwmWrite(led[1], array[10-i]);    
        //         softPwmWrite(led[2], array[i]);   
        //         delay(1000);     
        //     }
        // }
        // if (digitalRead(btn[0])==1){
        //     if ((millis() - storage_time) >= 2000){
        //         state = 0;
        //         printf("%d\n millis :", millis());
        //         for (int i = 0; i<3; i++){
        //             softPwmWrite(led[i], 0);
        //         }
        //     }
        // }

    
}