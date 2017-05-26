////////////////////////////////////////////////////////////////////KOD1
#include <targets/AT91SAM7.h>
#include "adc.h"
#include "lcd.h"
#include "usart.h"

#define AUDIO_OUT PIOB_SODR_P19 
#define SW_1 PIOB_SODR_P24 
#define SW_2 PIOB_SODR_P25 
#define LCD_BACKLIGHT PIOB_SODR_P20

#define J_LEFT PIOA_SODR_P7
#define J_UP PIOA_SODR_P9
#define J_RIGHT PIOA_SODR_P14
#define J_PUSH PIOA_SODR_P15
#define J_DOWN PIOA_SODR_P8

void delay(int n) __attribute__ ((section(".fast"))); // konfiguracja delay
void delay(int n) {
	volatile int i;
	for(i=3000*n; i>0; i--) {
		__asm__("nop");
	}
}

int wynik = 0;
int wynik2 = 0;

void zycieprzeciwnika(int zycie2) {
	switch(zycie2) {
		case 0:
			LCDClearScreen();
			LCDPutStr("WYGRALES!",50,30,SMALL,WHITE,BLUE);
			delay(1000);
			wynik += 1;
			menu(); 
			break;
		case 1: LCDPutStr("*         ",126,0,SMALL,WHITE,BLUE); break;
		case 2: LCDPutStr("**        ",126,0,SMALL,WHITE,BLUE); break;
		case 3: LCDPutStr("***       ",126,0,SMALL,WHITE,BLUE); break;
	}
}

void mojezycie(int zycie) {
	switch(zycie) {
		case 0:
			LCDClearScreen();
			LCDPutStr("PRZEGRALES!",50,30,SMALL,WHITE,BLUE);
			delay(1000);
			wynik2 += 1;
			menu(); 
			break; 
		case 1: LCDPutStr("*         ",0,0,SMALL,WHITE,BLUE); break;
		case 2: LCDPutStr("**        ",0,0,SMALL,WHITE,BLUE); break;
		case 3: LCDPutStr("***       ",0,0,SMALL,WHITE,BLUE); break;
	}
}

void ammoprzeciwnika(int ammo2) {
	switch(ammo2) {
		case 0: LCDPutStr("          ",126,70,SMALL,WHITE,RED); break;  
		case 1: LCDPutStr("*         ",126,70,SMALL,WHITE,RED); break;
		case 2: LCDPutStr("**        ",126,70,SMALL,WHITE,RED); break;
		case 3: LCDPutStr("***       ",126,70,SMALL,WHITE,RED); break;
		case 4: LCDPutStr("****      ",126,70,SMALL,WHITE,RED); break;
		case 5: LCDPutStr("*****     ",126,70,SMALL,WHITE,RED); break;
		case 6: LCDPutStr("******    ",126,70,SMALL,WHITE,RED); break;
		case 7: LCDPutStr("*******   ",126,70,SMALL,WHITE,RED); break;
		case 8: LCDPutStr("********  ",126,70,SMALL,WHITE,RED); break;
		case 9: LCDPutStr("********* ",126,70,SMALL,WHITE,RED); break;
		case 10: LCDPutStr("**********",126,70,SMALL,WHITE,RED); break;
	}
}

void mojeammo(int ammo) {
	switch(ammo) {
		case 0: LCDPutStr("          ",0,70,SMALL,WHITE,RED); break;  
		case 1: LCDPutStr("*         ",0,70,SMALL,WHITE,RED); break;
		case 2: LCDPutStr("**        ",0,70,SMALL,WHITE,RED); break;
		case 3: LCDPutStr("***       ",0,70,SMALL,WHITE,RED); break;
		case 4: LCDPutStr("****      ",0,70,SMALL,WHITE,RED); break;
		case 5: LCDPutStr("*****     ",0,70,SMALL,WHITE,RED); break;
		case 6: LCDPutStr("******    ",0,70,SMALL,WHITE,RED); break;
		case 7: LCDPutStr("*******   ",0,70,SMALL,WHITE,RED); break;
		case 8: LCDPutStr("********  ",0,70,SMALL,WHITE,RED); break;
		case 9: LCDPutStr("********* ",0,70,SMALL,WHITE,RED); break;
		case 10: LCDPutStr("**********",0,70,SMALL,WHITE,RED); break;
	}
}

void startGame() {
	
	LCDClearScreen(); // wyczyszczenie ekranu

	int zycie =3;
	int zycie2 = 3;
	int ammo = 10;
	int ammo2 = 10;

	mojezycie(zycie);
	zycieprzeciwnika(zycie2);
	mojeammo(ammo);
	ammoprzeciwnika(ammo2);

	int kanal;
	int w;
	int x=0, y=9; // pozycja graczaq na górze
	int x2= 0, y2 = 117; // pozycja graczaq na górze
	char* bufor;

	int pozycjaG = 0;
	int pozycjaD = 0;

	unsigned char znak;

	LCDPutStr("==A==",y2,pozycjaD,SMALL,WHITE,BLACK);
		LCDPutStr("==V==",y,pozycjaG,SMALL,WHITE,BLACK);
	while(1) {
		
		znak = read_char_USART0_nonstop();
		
		if(znak) {

			if(znak == 'L') {
				LCDPutStr("     ",y2,pozycjaD,SMALL,WHITE,BLACK);
				pozycjaD-=10;
				LCDPutStr("==A==",y2,pozycjaD,SMALL,WHITE,BLACK);
			}
				
			else if(znak == 'P') {
				LCDPutStr("     ",y2,pozycjaD,SMALL,WHITE,BLACK);
				pozycjaD+=10;
				LCDPutStr("==A==",y2,pozycjaD,SMALL,WHITE,BLACK);
			}

			else if(znak == 'O') {
				LCDPutStr("*",108,pozycjaD+12,SMALL,WHITE,BLACK);
				PIOB_SODR |= AUDIO_OUT;
				delay(3);
				LCDPutStr(" ",108,pozycjaD+12,SMALL,WHITE,BLACK);
				PIOB_CODR |= AUDIO_OUT;
				ammo2 -= 1;
				ammoprzeciwnika(ammo2);
				
				if(ammo == 0 && ammo2 == 0) {
					LCDClearScreen();
					LCDPutStr("BRAK AMUNICJI! REMIS!",50,30,SMALL,WHITE,BLUE);
					delay(1000);
					menu(); 
				}
			}

			else if(znak == 'T') {
				zycie-=1;
				mojezycie(zycie);
			}

			else if(znak == 'K') {
				LCDClearScreen();
				LCDPutStr("KONIEC GRY!",50,30,SMALL,WHITE,BLUE);
				delay(1000);
				menu(); 
			}
		
		}

		kanal = GetAdcChanel(ADC_CHN_7) / 10;
	
		if (kanal >= pozycjaG && pozycjaG < 100) {
			if(kanal/10 != pozycjaG/10) {
				LCDPutStr("     ",y,pozycjaG,SMALL,WHITE,BLACK);
				pozycjaG+= 10;
				write_char_USART0('P');
				LCDPutStr("==V==",y,pozycjaG,SMALL,WHITE,BLACK);
			}
			else pozycjaG = pozycjaG;
		}
		
		else if ( kanal <= pozycjaG && pozycjaG > 0) {
			if(kanal/10 != pozycjaG/10) {
				LCDPutStr("     ",y,pozycjaG,SMALL,WHITE,BLACK);
				pozycjaG-= 10;
				write_char_USART0('L');
				LCDPutStr("==V==",y,pozycjaG,SMALL,WHITE,BLACK);
			}
			else pozycjaG = pozycjaG;
		}
		
		else if (pozycjaG >= 100 || pozycjaG <= 10) {
			pozycjaG = pozycjaG;
		}

		if((PIOB_PDSR & SW_1) == 0) {
			write_char_USART0('O');
			
			LCDPutStr("*",18,pozycjaG+12,SMALL,WHITE,BLACK);
			PIOB_SODR |= AUDIO_OUT;
			delay(3);
			LCDPutStr(" ",18,pozycjaG+12,SMALL,WHITE,BLACK);
			PIOB_CODR |= AUDIO_OUT;

			ammo -=1;
			mojeammo(ammo);
			
			if(pozycjaD - pozycjaG <= 12 && pozycjaD - pozycjaG >= -12) {
				write_char_USART0('T');
				zycie2 -=1;
				zycieprzeciwnika(zycie2);
			}
			
			if(ammo == 0 && ammo2 == 0) {
					LCDClearScreen();
					LCDPutStr("BRAK AMUNICJI! REMIS!",50,30,SMALL,WHITE,BLUE);
					delay(1000);
					menu(); 
				}
		}

		if((PIOB_PDSR & SW_2) == 0) {
			write_char_USART0('K');
			LCDClearScreen();
			LCDPutStr("KONIEC GRY!",50,30,SMALL,WHITE,BLUE);
			delay(1000);
			menu(); 
		}
		
	}
}

void checkTrim() {
	LCDClearScreen(); // wyczyszczenie ekranu
	LCDPutStr("Ustaw oba potencjometry na najni¿sz¹ wartoœæ!",50,30,SMALL,WHITE,BLUE);
	int kanal;
	char znak;
	while(1) {
		kanal = GetAdcChanel(ADC_CHN_7);
		if(kanal < 10) {
			write_char_USART0('S');
			znak = read_char_USART0_nonstop();
			if(znak == 'S') {
				startGame();
			}
		}
	}
}

void showPoints() {
	LCDClearScreen(); // wyczyszczenie ekranu
	char* bufor;
	bufor = (char*)malloc(40);
	sprintf(bufor,"%d\0",wynik);
	LCDPutStr("Moje punkty",10,5,LARGE,WHITE,BLACK);
	LCDPutStr(bufor,30,40,LARGE,WHITE,BLACK);
	free(bufor);

	bufor = (char*)malloc(40);
	sprintf(bufor,"%d\0",wynik2);
	LCDPutStr("Przeciwnika",70,5,LARGE,WHITE,BLACK);
	LCDPutStr(bufor,90,40,LARGE,WHITE,BLACK);
	free(bufor);

	delay(500);
	menu();
}

void showCredits() {
	LCDClearScreen(); // wyczyszczenie ekranu
	
	LCDPutStr("Wac Agnieszka",10,5,SMALL,WHITE,BLACK);
	LCDPutStr("Surtel Katarzyna",30,5,SMALL,WHITE,BLACK);
	delay(500);
	
	menu();
}

void sterowanie() {
	LCDClearScreen(); // wyczyszczenie ekranu
	
	LCDPutStr("Lewo-prawo: TRIM",10,5,SMALL,WHITE,BLACK);
	LCDPutStr("Strzal: Lewy przycisk",30,5,SMALL,WHITE,BLACK);
	LCDPutStr("Koniec: Prawy przycisk",50,5,SMALL,WHITE,BLACK);
	delay(1000);
	
	menu();
}

void menu() {
	LCDClearScreen(); // wyczyszczenie ekranu

  LCDPutStr("START",5,20,SMALL,WHITE,BLUE);
  LCDPutStr("PUNKTACJA",30,20,SMALL,WHITE,BLUE);
  LCDPutStr("TWORCY",55,20,SMALL,WHITE,BLUE);
	LCDPutStr("STEROWANIE",80,20,SMALL,WHITE,BLUE);
  LCDPutStr("WYJSCIE",105,20,SMALL,WHITE,BLUE);
  LCDPutStr(">",5,0,SMALL,WHITE,BLUE);

  int wyborMenu = 0;

	while(1) {
		if((PIOA_PDSR & J_UP)==0 && wyborMenu > 0) {
			LCDPutStr(" ",(wyborMenu*25)+5,0,SMALL,WHITE,BLUE);
			wyborMenu-=1;
			LCDPutStr(">",(wyborMenu*25)+5,0,SMALL,WHITE,BLUE);
			delay(500);
		}
		
		if((PIOA_PDSR & J_DOWN)==0 && wyborMenu < 4) {
			LCDPutStr(" ",(wyborMenu*25)+5,0,SMALL,WHITE,BLUE);
			wyborMenu+=1;
			LCDPutStr(">",(wyborMenu*25)+5,0,SMALL,WHITE,BLUE);
			delay(500);
		}
		
		if((PIOA_PDSR & J_PUSH)==0) {
			switch(wyborMenu) {
				case 0: checkTrim(); break;
				case 1: showPoints(); break;
				case 2: showCredits(); break;
				case 3: sterowanie(); break;
				case 4: PIOB_CODR|=LCD_BACKLIGHT; break;
			}
		}
	}
}


int main() {
	PMC_PCER = PMC_PCER_PIOB; // w³¹czenie obs³ugi przerwañ
	PMC_PCER=PMC_PCER_PIOA;
	PIOB_OER = AUDIO_OUT | LCD_BACKLIGHT;
	PIOB_PER = AUDIO_OUT | LCD_BACKLIGHT;

	InitLCD(); //inicjalizacja LCD
	InitADC(); // inicjalizacja ADC
	LCDSettings(); //ustawienie LCD
	LCDClearScreen(); // wyczyszczenie ekranu
	InitUSART0();

	menu();
	
	return 0;
}