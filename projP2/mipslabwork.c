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

#define TMR2PERIOD ((80000000 / 256) / 300) /* FPS */
#if TMR2PERIOD > 0xffff
#error "TimerPeriodIsTooBig"
#endif


//#define TMR2PERIOD ((80000000 / 256) / 10) //initialize tmr2period

int blobX = 8;
int blobY = 6;

int wallx0 = 128;
int wally0 = 31;

int wallx1 = 180;
int wally1 = 0;

int wallx2 =240;
int wally2 = 0;

int wallx3 = 300;
int wally3 = 31;

int wallx = 0;
int wally = 0;

int start = 1;

int prime = 1234567;
int mytime = 0x5957;
int timecount = 0;
char starttxt[] = "Snekky Brid ";
char starttxt1[] = "BTN4 2 start";
char starttxt2[] = "BTN3 2 jump ";



char gameover1[] = "GAME OVER ";
char gameover2[] = "BTN4 to restart";

volatile int *porte = (volatile int *) 0xbf886110;


/* Interrupt Service Routine */
void user_isr( void )
{
//när interupt kör den user
//if(IFS(0) & 0x100){
	IFSCLR(0) = 0x100;
	interupt = 1;
}

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

enable_interrupt();
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{

mark_blob(blobX, blobY);
//}
mark_wall0(wallx0, wally0);
mark_wall1(wallx1, wally1);
mark_wall2(wallx2, wally2);
mark_wall3(wallx3, wally3);
mark_wallz(wallx, wally);

display_image(0, icon);

resetscreen();


blobY = blobY + 1; //Gravity 

delay(30);

// -1 gives direction of the walls
wallx0 = wallx0 - 1;
wallx1 = wallx1 - 1;
wallx2 = wallx2 - 1;
wallx3 = wallx3 - 1;


//Resets walls
if(wallx0 <= -128) 
{
	wallx0 = 128; 
}

if(wallx1 <= -128)
{
	wallx1 = 128;
}

if(wallx2 <= -128) 
{ 
	wallx2 = 128; 
}

if(wallx3 <= -128)
{
	wallx3 = 128; 
}
// jump
if(getbtns() == 2){
blobY = blobY - 3;
}

//collisions
int whileloop = 1;
if(blobY >= 30 || blobY <= 4 || ( (blobY - 1) >= wally-14 && (blobX+ 8) == wallx) || 
(((blobY - 1) <= (wally1 + 10)) && ((blobX + 8) == wallx1)) || (((blobY -1)<=wally2 + 19) && ((blobX +8)== wallx2)) 
  || (((blobY-1) >= (wally3 -18)) &&  ((blobX + 8) == wallx3))){
while(whileloop){
		display_string(1, gameover1);
		display_string(2, gameover2);

		display_update();
		if(getbtns() == 4){
			//Reset to start

			whileloop = 0;
			blobY = 8;
			blobX = 6;
			wallx0 = 128;
			wallx1 = 180;
			wallx2 = 240;
			wallx3 = 300;

		}
	}
}

while(start){
display_string(0, starttxt);
display_string(1, starttxt1);
display_string(2, starttxt2);

display_update();

if(getbtns() == 4){
start = 0;
}
}
display_string(0, "");
display_string(3, "");

}