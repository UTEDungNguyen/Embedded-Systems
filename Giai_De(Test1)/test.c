#include<stdio.h>
#include<stdint.h>
#include<wiringPi.h>
#include<softPwm.h>
#include <stdlib.h>
#include <time.h>
#include<stdbool.h>

#define BT1 0
#define BT2 2
uint8_t led_pin[3]={21,22,23};
uint8_t state_bt1;
uint8_t state_bt2;
int count =1;
int channel=0;
unsigned char color[10];
bool run= true;
int t1;
int t2;
void bt1(void){
    t1=time(INT_EDGE_RISING);
    t2=time(INT_EDGE_FALLING);
    if (digitalRead(BT1)==0){
        state_bt1=1;
        count ++;
        if(count>5){
            count=1;
        }
    }
}
void bt2(void){
    if (digitalRead(BT2)==0){
        state_bt2=1;
        channel++;
        if (channel>2){channel=0;}
    }
}

int GetRandom(int min,int max){
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}
int main(){
    wiringPiSetupGpio();
    // khai bao vao ra cho button
    pinMode(BT1,INPUT);
    pinMode(BT2,INPUT);
    // khai bao ngo ra cho led
    for (int i=0; i<3; i++){
        pinMode(led_pin[i] ,OUTPUT);
        softPwmCreate(led_pin[i],0,100);
        
    }
    // khai bao ham ngat cho BT1
    wiringPiISR(BT1, INT_EDGE_RISING,&bt1);
    wiringPiISR(BT2, INT_EDGE_RISING,&bt2);
    // tao 10 gia tri mau 
    for (int x=0; x<10;x++){
        color[x]=GetRandom(0,100);
    }

    
    int diff_t=difftime(t2,t1);
    while(run){ 
        if ((diff_t)>=2000){
            run=false;
    }
        if (state_bt1==1){
            softPwmWrite(led_pin[0],count*20 );}
                }
        if (state_bt2==1){
            if(channel==1){
                digitalWrite(led_pin[0],HIGH);
                delay(100);
                digitalWrite(led_pin[0],LOW);
                delay(100);}
                
            else if(channel==2){
                for(int y=0; y<10;y++){
                     digitalWrite(led_pin[0],color[y]);
                     digitalWrite(led_pin[1],color[10-y]);
                     digitalWrite(led_pin[2],color[y]);
                }
               
            }
        }

    }
    
