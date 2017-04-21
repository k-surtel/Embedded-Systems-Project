#include <targets/AT91SAM7.h>
#include"adc.h"
#include"lcd.h"
#define AUDIO_OUT PIOB_SODR_P19 
#define SW_1 PIOB_SODR_P24 
#define SW_2 PIOB_SODR_P25 
#define LCD_BACKLIGHT PIOB_SODR_P20

void delay(int n) __attribute__ ((section(".fast"))); // konfiguracja delay
void delay(int n) {
 volatile int i;
 for(i=3000*n; i>0; i--){
 __asm__("nop");
 }
}

void pocisk(int x){

}

int main() {
 PMC_PCER = PMC_PCER_PIOB; // w³¹czenie obs³ugi przerwañ
 PIOB_OER = AUDIO_OUT | LCD_BACKLIGHT;
 PIOB_PER = AUDIO_OUT | LCD_BACKLIGHT;

 int kanal;
 int w;

  int x=0, y=9; // pozycja graczaq na górze

  int x2= 0, y2 = 117; // pozycja graczaq na górze
 char* bufor;
 InitLCD(); //inicjalizacja LCD
 InitADC(); // inicjalizacja ADC
 LCDSettings(); //ustawienie LCD
 LCDClearScreen(); // wyczyszczenie ekranu
 LCDPutStr("**********",126,0,SMALL,WHITE,BLUE);
 LCDPutStr("**********",0,0,SMALL,WHITE,BLUE);

 LCDPutStr("**********",126,70,SMALL,WHITE,RED);
 LCDPutStr("**********",0,70,SMALL,WHITE,RED);

LCDPutStr("==A==",y2,x2,SMALL,WHITE,BLACK);

int pozycja = 20;

int pocisk = 18;


 while(1) {
kanal = GetAdcChanel(ADC_CHN_7) / 10;


LCDPutStr("==V==",y,pozycja,SMALL,WHITE,BLACK);
 if (kanal > pozycja && pozycja < 100){
	 LCDPutStr("     ",y,pozycja,SMALL,WHITE,BLACK);
	 pozycja+= 10;
	 LCDPutStr("==V==",y,pozycja,SMALL,WHITE,BLACK);
  }
 else if ( kanal < pozycja && pozycja > 0){
 	 LCDPutStr("     ",y,pozycja,SMALL,WHITE,BLACK);
	 pozycja+= 10;
	 LCDPutStr("==V==",y,pozycja,SMALL,WHITE,BLACK);
 }

 
 /*switch(kanal) {
 case 0:
 LCDPutStr("     ",y,x,SMALL,WHITE,BLACK);
 x = 0;
 LCDPutStr("==V==",y,x,SMALL,WHITE,BLACK);
 break;

 case 102:
 LCDPutStr("     ",y,x,SMALL,WHITE,BLACK);
 x = 10;
 LCDPutStr("==V==",y,x,SMALL,WHITE,BLACK);
 break;

 case 204:
 LCDPutStr("     ",y,x,SMALL,WHITE,BLACK);
 x = 20;
 LCDPutStr("==V==",y,x,SMALL,WHITE,BLACK);
 break;
 case 306:
  LCDPutStr("     ",y,x,SMALL,WHITE,BLACK);
 x = 30;
 LCDPutStr("==V==",y,x,SMALL,WHITE,BLACK);
 break;
 case 409:
  LCDPutStr("     ",y,x,SMALL,WHITE,BLACK);
 x = 40;
 LCDPutStr("==V==",y,x,SMALL,WHITE,BLACK);
 break;
 case 512:
  LCDPutStr("     ",y,x,SMALL,WHITE,BLACK);
 x = 50;
 LCDPutStr("==V==",y,x,SMALL,WHITE,BLACK);
 break;

 case 614:
  LCDPutStr("     ",y,x,SMALL,WHITE,BLACK);
 x = 60;
 LCDPutStr("==V==",y,x,SMALL,WHITE,BLACK);
 break;

 case 716:
  LCDPutStr("     ",y,x,SMALL,WHITE,BLACK);
 x = 70;
 LCDPutStr("==V==",y,x,SMALL,WHITE,BLACK);
 break;

 case 818:
  LCDPutStr("     ",y,x,SMALL,WHITE,BLACK);
 x = 80;
 LCDPutStr("==V==",y,x,SMALL,WHITE,BLACK);
 break;

 case 921: 
  LCDPutStr("     ",y,x,SMALL,WHITE,BLACK);
 x = 90;
 LCDPutStr("==V==",y,x,SMALL,WHITE,BLACK);
 break;

 case 1023:
  LCDPutStr("     ",y,x,SMALL,WHITE,BLACK);
 x = 100;
 LCDPutStr("==V==",y,x,SMALL,WHITE,BLACK);
 break;
 }*/


 if((PIOB_PDSR & SW_1) == 0){

 }

 if((PIOB_PDSR & SW_2) == 0){
  LCDPutStr("*",pocisk,x+12,SMALL,WHITE,BLACK);
  delay(1000);
  LCDPutStr(" ",pocisk,x+12,SMALL,WHITE,BLACK);
  LCDPutStr("*",pocisk+7,x+12,SMALL,WHITE,BLACK);
  delay(1000);
  LCDPutStr(" ",pocisk,x+12,SMALL,WHITE,BLACK);
  LCDPutStr("*",pocisk+14,x+12,SMALL,WHITE,BLACK);
}
}

 return 0;
}