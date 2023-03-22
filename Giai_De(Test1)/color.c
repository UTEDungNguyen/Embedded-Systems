#include<stdio.h>
#include<stdint.h>
#include<wiringPi.h>
#include<softPwm.h>
#include <stdlib.h>
#include <time.h>

// int d_sang, r , g ,b;
uint8_t led_pin[3]={0,2,3};
int array[4]={};
int main(){
    wiringPiSetUp();
    // khoi tao softpwm
    for(int i=0; i<3; i++){
        softPwmCreate(led_pin[i],0,100);
    }
    while(1){
     
        scanf("%d %d %d %d",&array[0],&array[1],&array[2],&array[3]);
        printf("%d %d %d %d ",array[0],array[1],array[2],array[3]);

        for(int x=0;x<3;x++){
            
            softPwmWrite(led_pin[x],array[0]*array[x+1]);
        }

    }
   
}