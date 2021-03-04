/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>	 /* Declarations of uint_32 and the like */
#include <pic32mx.h>	/* Declarations of system-specific addresses etc */
#include "mipslab.h"	/* Declatations for these labs */

#define TMR2PERIOD ((80000000 / 256) / 300) /* 100ms */
#if TMR2PERIOD > 0xffff
#error "TimerPeriodIsTooBig"
#endif


//#define TMR2PERIOD ((80000000 / 256) / 10) //initialize tmr2period
int squareX = 15;
int squareY = 10;
int squareXpixel = 23;
int squareYpixel = 4;

int obsx = 128;
int obsy = 31;

int obsx1 = 180;
int obsy1 = 0;

int obsx2 =240;
int obsy2 = 0;

int obsx3 = 300;
int obsy3 = 31;

int wallx = 0;
int wally = 0;

int start = 1;

int prime = 1234567;
int mytime = 0x5957;
int timecount = 0;
char starttext[] = "flappycat ";
char starttext1[] = "BTN4 to start";
char starttext2[] = "BTN3 to jump ";
char starttext3[] = "BTN2--> BTN4<-- ";




char gameover1[] = "Game over, klick ";
char gameover2[] = "BTN4 to restart";

volatile int *porte = (volatile int *) 0xbf886110;


/* Interrupt Service Routine */
void user_isr( void )
{
//när interupt kör den user
//if(IFS(0) & 0x100){
	IFSCLR(0) = 0x100;
	interupt = 1;

	//timecount++;

	//if(timecount == 10){

	//ime2string(textstring,mytime);
	//display_string(3, textstring);
	//display_update();
	//tick(&mytime);
	//timecount = 0;
	//}	
//}
}
//for sw3
//if(IFS(0) & 0x8000){
//IFSCLR(0) = 0x8000;
//(*porte) += 1;
//}

//for sw2
//if(IFS(0) & 0x800){
////IFSCLR(0) = 0x800;
//tick(&mytime);
//tick(&mytime);
//tick(&mytime);
//time2string(textstring,mytime);
//display_string(3, textstring);
//display_update();

//IFSCLR(0) = 0x800;
//}
//}

/* Lab-specific initialization goes here */
void labinit( void )
{
volatile int *trise = (volatile int*) 0xbf886100;

*trise =*trise &  0xFF00;

TRISD = TRISD & 0x0fe0;
//(*porte) = 0;

//T2CONSET = 0x70; //ta borty sen
PR2 = TMR2PERIOD;
TMR2 = 0; //kan lägga till vad som, börjar på 0
T2CONSET = 0X8070; //8 är bit för att starta, 70 är för att prescalingen
//T2CONSET = 0x8000;
//
//

IEC(0) = 0x100; //set enable

IPC(2) = 0x1f; //set prioritty

//enable sw3
//IPC(3) = 0x1c000000;
//IEC(0) = IEC(0) | 0x8000;


//enable sw2
//IEC(0) = 0x800 | IEC(0) ; 
//IPC(2) = 0x1f000000 | IPC(2);



enable_interrupt();
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{


//prime = nextprime(prime);
//display_string( 0, itoaconv(prime));
if(getbtns() != 2){
mark_square1(squareX, squareY);
}

if(getbtns() == 2){
mark_square2(squareX, squareY);
}
mark_obs(obsx, obsy);

mark_obs1(obsx1, obsy1);

mark_obs2(obsx2, obsy2);
mark_obs3(obsx3, obsy3);

mark_wall(wallx, wally);

//mark_obs1(obsx1, obsy1);

//mark_obs2(obsx2, obsy2);
//mark_obs3(obsx3, obsy3);

display_image(0, icon);
//display_update();
resetscreen();


squareY = squareY + 1;
squareXpixel = squareYpixel + 1;
delay(30);
//squareY = squareY + 1;
obsx = obsx - 1;
obsx1 = obsx1 - 1;
obsx2 = obsx2 - 1;
obsx3 = obsx3 - 1;




//Resets
if(obsx <= -128) //120
{
	//obsy = 31;
	obsx = 128; //128

}

if(obsx1 <= -128) //72
{
	obsx1 = 128; //180

}

if(obsx2 <= -128){ //-20
	obsx2 = 128; //240

}

if(obsx3 <= -128){
	obsx3 = 128; //300

}



//if (((squareX+ 8) == obsx) || ((squareX + 8) == obsx1-52) ||  ((squareX +8)== obsx2)  ||   ((squareX + 8) == obsx3))
  //{
	//  *porte= *porte +1;
  //}



if(getbtns() == 2){
squareY = squareY - 3;
}

if(getbtns()==1){
	squareX = squareX + 1;
}
if(getbtns()==4){
	squareX = squareX - 1;
}
//collisions
int whileloop = 1;
if(squareY >= 30 || squareY <= 4 || ( (squareY - 1) >= obsy-14 && (squareX+ 8) == obsx) || 
(((squareY - 1) <= (obsy1 + 10)) && ((squareX + 8) == obsx1)) || (((squareY -1)<=obsy2 + 19) && ((squareX +8)== obsx2)) 
  || (((squareY-1) >= (obsy3 -18)) &&  ((squareX + 8) == obsx3))){
while(whileloop){
		display_string(1, gameover1);
		display_string(2, gameover2);

		display_update();
		if(getbtns() == 4){
			//(*porte) = 0;

			whileloop = 0;
			squareY = 15;
			squareX = 10;
			obsx = 128;
			obsx1 = 180;
			obsx2 = 240;
			obsx3 = 300;

		}
	}
}

while(start){
display_string(0, starttext);
display_string(1, starttext1);
display_string(2, starttext2);
display_string(3, starttext3);



display_update();

if(getbtns() == 4){
start = 0;
}
}
display_string(0, "");
display_string(3, "");



}


