
// C:\z88dk\include
// C:\z88dk\include\_DEVELOPMENT\sdcc
// C:\z88dk\include\_DEVELOPMENT\sccz80

// sdcc  ::  
// zcc +zx -vn -SO3 -startup=31 -clib=sdcc_ix --reserve-regs-iy --max-allocs-per-node200000 main.c -o circ

//-lm allows for floats

// zcc +zx -vn -lm -O3 -startup=31 -clib=new main.c -o circ -zorg=32768


//zcc +zx -vn -lm -lndos -SO3 -startup=31 -clib=new main.c -o circ -zorg=32768


//floating point
//zcc +zx -vn -lm -clib=sdcc_iy -startup=1 main.c zxgraphics.c -o main -create-app


//new tester
// zcc +zx -vn -clib=new main.c zxgraphics.c -o main -create-app
// zcc +zx -vn -clib=sdcc_ix main.c zxgraphics.c -o main -create-app

// 




//optimizer but slow to compile
//zcc +zx -vn -SO3 -clib=sdcc_iy --max-allocs-per-node200000 main.c zxgraphics.c -o main -create-app -pragma-define:CRT_ENABLE_EIDI=0x21

#include <stdlib.h>
#include <stdio.h>
#include <arch/zx.h>
#include <input.h>
#include <math.h>
#include <string.h>

#include <arch/spectrum.h>

#include "zxgraphics.h"
#include <ctype.h>

#define printAt(row, col)

void pressakey()
{
	putc(0x0b, stdout);// control code home
	printf("Press a key\n");
	in_wait_nokey();
	in_pause(0);
	//putc(0x0c, stdout);//control code clear screen
}

	
	



void main(void)
{
	signed int r;
	signed int s;
	signed int t;
	unsigned char colour;// = (0 & 0x0) + PAPER_WHITE;
   
    
	zx_cls(0x38);
   
	
	
	r = 0;
	t = 0;
	s = 0;

	
	//plot routine
	{
		t = 127;
		s = 86;
		colour = (1 & 0x3) + PAPER_WHITE;//blue ink
		printf("\nPlot pause and Unplot\n");
		ZXplot(t, s, colour);
		
		pressakey();
		putc(0x0c, stdout);//control code clear screen
		
		colour = (2 & 0x3) + PAPER_WHITE;//red ink
		printf("\nFill screen with Plot and clear with Unplot\n");
		for (s = 0; s < 256; s++)
		{
			for (t = 0; t < 192; t++)
			{
				ZXplot(s, t, colour);
			}
		}
		
		for (s = 0; s < 256; s++)
		{
			for (t = 0; t < 192; t++)				
			{
				ZXunplot(s, t, colour);
			}
		}
		pressakey();
		putc(0x0c, stdout);//control code clear screen
	}
	
	
	
	
	//line demo
	{		
		colour = (3 & 0x3) + PAPER_WHITE;//magenta ink
	
		printf("\nLine Routine\n");
		ZXLine(0, 0, 256, 192, colour, 1);
		ZXLine(0, 192, 256, 0, colour, 1);
		pressakey();
		putc(0x0c, stdout);//control code clear screen
		
		printf("\nFill screen with line Routine and then clear with line routine\n");
		
		for (s = 0; s < 256; s++)
		{
			ZXLine(0, 0, s, 192, colour, 1);
		}
		
		for (s = 256; s > 0; s--)
		{
			ZXLine(s, 0, 256, 192, colour, 1);
		}
		in_pause(2000);
		
		for (s = 0; s < 256; s++)
		{
			ZXLine(s, 0, 256, 192, colour, 0);
			ZXLine(0, 0, s, 192, colour, 0);
		}
		pressakey();
		putc(0x0c, stdout);//control code clear screen
		
	}
	
	//square demo

	{
		colour = (4 & 0x4) + PAPER_WHITE;//green
		printf("\nSquare Routine\n");
		ZXSquare(120,90,30, colour,1);
		pressakey();
		putc(0x0c, stdout);//control code clear screen
		for (s = 0; s < 50; s++)
		{
			ZXSquare(120,90,s, colour,1);
		}
		for (s = 0; s < 50; s++)
		{
			ZXSquare(120,90,s, colour,0);
		}
	}
	
	//rectangle demo
	{
		colour = (5 & 0x5) + PAPER_WHITE;//cyan
		printf("\nRectangle Routine\n");
		ZXRectangle(120,90,15,30, colour,1);
		pressakey();
		putc(0x0c, stdout);//control code clear screen
		for (s = 0; s < 50; s++)
		{
			ZXRectangle(120,90,15,s, colour,1);
		}
		for (s = 0; s < 50; s++)
		{
			ZXRectangle(120,90,15,s, colour,0);
		}
		for (s = 0; s < 50; s++)
		{
			ZXRectangle(120,90,s,15, colour,1);
		}
		for (s = 0; s < 50; s++)
		{
			ZXRectangle(120,90,s,15, colour,0);
		}
	}
	
	//triangle demo
	
	{
		colour = (6 & 0x6) + PAPER_WHITE;//yellow
		printf("\nTriangle Routine\n");
		ZXTriangle (40, 40, 60, 150,colour, 1);
		in_pause(2000);
		pressakey();
		putc(0x0c, stdout);//control code clear screen
		for (s = 0; s < 50; s++)
		{
			ZXTriangle (40, 40, s,150 ,colour, 1);
		}
		for (s = 0; s < 50; s++)
		{
			ZXTriangle (40, 40, s,150 ,colour, 0);
		}
		pressakey();
		putc(0x0c, stdout);//control code clear screen
	}
	
	
	
	
	
	
	//circle demo
	
	{		
		colour = (1 & 0x3) + PAPER_WHITE;//blue ink
		printf("\nCircle Routine\n");
		ZXCircle(127, 86, 40, colour, 1);
		pressakey();
		putc(0x0c, stdout);//control code clear screen
		
		for (s = 0; s < 75; s++)
		{
			ZXCircle(127, 86, s, colour, 1);
		}
		for (s = 0; s < 75; s++)
		{
			ZXCircle(127, 86, s, colour, 0);
		}
		pressakey();
		putc(0x0c, stdout);//control code clear screen
	}
	
	
	//ellipse routine
	{
		colour = (0 & 0x0) + PAPER_WHITE;//green
		printf("\nEllipse Routine\n");
		ZXEllipse(127, 86, 20, 40, colour, 1);
		pressakey();
		putc(0x0c, stdout);//control code clear screen

		
		for (r = 0; r < 70; r++)
		{
			ZXEllipse(120,90,r ,40, colour,1);
		}
		for (r = 0; r < 70; r++)
		{
			ZXEllipse(120,90,r ,40, colour,0);
		}
		pressakey();
		putc(0x0c, stdout);//control code clear screen
	}
	
	//arc routine
	{
		colour = (2 & 0x3) + PAPER_WHITE;//red ink
		printf("\nArc Routine\n");
		ZXArc(127, 86, 20, 40, colour, 1);
		pressakey();
		putc(0x0c, stdout);//control code clear screen

		
		for (r = 0; r < 70; r++)
		{
			ZXArc(127,96,r ,40, colour,1);
		}
		for (r = 0; r < 70; r++)
		{
			ZXArc(127,96,r ,40, colour,0);
		}
		pressakey();
		putc(0x0c, stdout);//control code clear screen
	}
	
	{
		colour = (3 & 0x3) + PAPER_WHITE;//magenta ink

		printf("\nParabola Routine\n");
		ZXParabola(127, 86, 20, 40, colour, 1);
		
		pressakey();
		putc(0x0c, stdout);//control code clear screen

		
		for (r = 0; r < 70; r++)
		{
			ZXParabola(127,96,r ,40, colour,1);
		}
		for (r = 0; r < 70; r++)
		{
			ZXParabola(127,96,r ,40, colour,0);
		}
		pressakey();
		putc(0x0c, stdout);//control code clear screen
	}
	

	
	
	/*
	//Quadratic Bezier Curve section
	{
		r = 0;
		t = 96;
		s = 96;
		colour = (5 & 0x3) + PAPER_WHITE;//green
		
		printf("\nQuadratic Bezier Curve\n");
		ZXQuad1(65,96, 108,66, 144,96, 16, colour, 1);	
		in_pause(2000);
		pressakey();
		putc(0x0c, stdout);//control code clear screen
	
		printf("\nQuadratic Bezier Curve, on top of one another\n");
		ZXQuadraticBezier(65,96, 108,66, 144,96, 16, colour, 1);
		ZXQuadraticBezier(65,96, 108,126, 144,96, 16, colour, 1);
		in_pause(2000);
		pressakey();
		//putc(0x0c, stdout);//control code clear screen
		
		printf("\nQuadratic Bezier Curve, on top of one another Erase\n");
		ZXQuadraticBezier(65,96, 108,66, 144,96, 16, colour, 0);
		ZXQuadraticBezier(65,96, 108,126, 144,96, 16, colour, 0);
		in_pause(500);
		pressakey();
		putc(0x0c, stdout);//control code clear screen
		
		
		printf("\nQuadratic Bezier Curve, on top of one another loop and Erase\n");
		for (r = 0; r < 40; r ++)
		{
			//16 is plenty detailed
			ZXQuadraticBezier(65,96, 108,t, 144,96, 16, colour, 1);
			ZXQuadraticBezier(65,96, 108,s, 144,96, 16, colour, 1);
			
			ZXQuadraticBezier(65,96, 108,t, 144,96, 16, colour, 0);
			ZXQuadraticBezier(65,96, 108,s, 144,96, 16, colour, 0);
			t -= 3;
			s += 3;
		}
		pressakey();
		putc(0x0c, stdout);//control code clear screen
	}
	*/

	
	
	
	//plotBasicBezier(65,150,108,60,144,150, colour, 0);
	//bezier(65,150,108,60,144,150, colour, 0);
	
	

	//ZXEllipse(120,90,r ,40, colour,1);
	//ZXEllipse(120,90,r ,40, colour,0);
	
	
	
	
	//in_pause(0);//pause until keypress   
	//zx_cls(0x38);
	
	
	
	
	
	
	
	//time = 22.5

	

	
	
	
	
	

   in_wait_nokey();
}


//eof