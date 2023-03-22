#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define spi0 0
unsigned char data[2];
uint8_t covid19[8]={0x4E,0x7E,0x3E,0x06,0x7E,0x30,0x7B};
uint8_t add[10]={0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B};
uint8_t dis[4];
int dem = 0;
int nghin = 0;
int tram = 0;
int chuc = 0;
int donvi = 0;

void senddata(unsigned char address, unsigned char value){
    data[0] = address;
    data[1] = value;
    wiringPiSPIDataRW(spi0, data, 2);
}

void initMax7219(void){
    // set decode mode : 0x09FF
    senddata(0x09, 0x00);
    // set intensity : 0x0A09
    senddata(0x0A,9);
    // set scanlimit
    senddata(0x0B,7);
    // no shutdown, turn off display test
    senddata(0x0C,1);
    senddata(0x0F,0);
}

void display(int count){
    dis[3] = add[count / 1000]; // nghin
    dis[2] = add[(count%1000)/100];  //tram
    dis[1]  = add[(count%100)/10];      //chuc
    dis[0]  = add[(count%10)%10];  //donvi

    if (count < 1000){
        dis[3] = 0x00;
    }
    if (count <100){
        dis[2] =0x00;
    }
    if (count <10){
        dis[1] =0x00;
    }

}

int main(void){

    // set up SPI interface
    wiringPiSPISetup(spi0, 10000000);
    initMax7219();

    for (int x = 0; x<8; x++){
        senddata(x+1,0x00);
    }

    while(1){
        for (int j = 0; j<10000; j++){
            display(j);
            delay(1000);
            for (int i = 0; i<4; i++){
                senddata(i+1, dis[i]);
            }
        }
    }
    
    // while(1){
    //     for (int i = 0; i<101; i++){
    //         D=i*41;
    //         if (D >4095){
    //             D = 4095;
    //         }
            
    //     }
    // }

}