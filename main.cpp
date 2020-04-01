#include "mbed.h"


Serial pc( USBTX, USBRX );
AnalogIn Ain(A0);
DigitalIn  Switch(SW3);
DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);
BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);
AnalogOut Aout(DAC0_OUT);


char table[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
int i = 0;
float j = 0;
float data;
int freq;
float ADCdata[500];

int main(){

  for (i = 0; i < 430; i++){
    data = Ain;
    pc.printf("%1.3f\r\n", data);
    wait(1./430);

  }

  while(1){

    if( Switch == 0 ){
      greenLED = 1;
      redLED = 0;
      display = table[freq/100];
      wait(1);        

      display = table[(freq/10)%10];
      wait(1);
      
      if( i%10== 0)
          display = 0xBF;
      else
          display = table[freq%10];
      wait(1);
    }


    

    else{
      redLED = 1;
      greenLED = 0;
      display = 00000000;
      if(freq == 0){
        for(i = 0; i < 500; i++){
          ADCdata[i] = Ain;
          wait(0.002);
        }
        for(i = 0; i < 500; i++){
          if(ADCdata[i-1] < ADCdata[i] && ADCdata[i] > ADCdata[i+1])
            freq++;
        }
      }
      else{
        for(j = 0; j < 2; j += 0.02){
          Aout = 0.5 + 0.5 * sin(j*3.14159);
          wait(1./100);
        }
      }

    }

  }

}