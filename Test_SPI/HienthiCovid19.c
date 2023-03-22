#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdint.h>

#define spi0 0
unsigned char data[2];
uint8_t covid19[8]={0x4E,0x7E,0x3E,0x06,0x7E,0x30,0x7B};
uint8_t add[8]={0,1,4,6,4,9,0};

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

int main(void){

    // set up SPI interface
    wiringPiSPISetup(spi0, 10000000);
    initMax7219();

    for (int i = 0; i<8; i++){
        senddata(i+1, covid19[7-i]);
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