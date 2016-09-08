/*
* Graphics helper for ZX Spectrum
* so things will make sense for me
*/
//http://z88dk.cvs.sourceforge.net/viewvc/z88dk/z88dk/libsrc/spectrum/display/

//#define abs(x) ((x)<0 ? -(x) : (x))
//#define min(a,b) (((a)<(b))?(a):(b))
//#define max(a,b) (((a)>(b))?(a):(b))

#include <arch/zx.h>
#include <math.h>
#include <input.h>//used for pause
#include <stdlib.h>//temp
#include <stdio.h>//temp
//#include <assert.h>

#define MaxX 255
#define MaxY 191
#define MinX 0
#define MinY 0



void ZXplot(int x, int y, unsigned char colour)
{
    // works opposite to spectrum basic 
    // 0,0 ZXPlot = top left vs Basic = bottom left
    // 255,0 ZXplot = top right vs Basic = bottom right
    // 0,175 ZXplot = bottom left vs BASIC = top left
    // 255,175 ZXplot = bottom right vs BASIC = top right
	//
	// and larger than Basic Plot
	// ZXplot X range is 0-255 vs Basic 0-255
    // ZXplot Y range is 0-191 vs Basic 0-175
    
    char *address;
   
    //if you exceed the edges
    if (x > MaxX) return;
    if (y > MaxY) return;
    if (x < MinX) return;
    if (y < MinY) return;
    
    address = zx_pxy2saddr(x,y);
    *address |= zx_px2bitmask(x);
   
    *zx_saddr2aaddr(address) = colour;
}

void ZXunplot(int x, int y, unsigned char colour)
{
    // works opposite to spectrum basic 
    // 0,0 ZXPlot = top left vs Basic = bottom left
    // 255,0 ZXplot = top right vs Basic = bottom right
    // 0,175 ZXplot = bottom left vs BASIC = top left
    // 255,175 ZXplot = bottom right vs BASIC = top right
	//
	// and larger than Basic Plot
	// ZXplot X range is 0-255 vs Basic 0-255
    // ZXplot Y range is 0-191 vs Basic 0-175
	
	char *address;
   
	//if you exceed the edges
	if (x > MaxX) return;
	if (y > MaxY) return;
	if (x < MinX) return;
	if (y < MinY) return;
	
	address = zx_pxy2saddr(x,y);
	
	*address &= ~zx_px2bitmask(x);
	
	*zx_saddr2aaddr(address) = colour;
}

void ZXLine(int x1, int y1, int x2, int y2, unsigned char colour, unsigned char plotUnplot)
{
    int dy = y2 - y1;
    int dx = x2 - x1;
	
    int stepx;
	int stepy;
	int fraction = 0;

    if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; }
    if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }
    dy <<= 1;        // dy is now 2*dy
    dx <<= 1;        // dx is now 2*dx

	if (plotUnplot == 1)
	{
		ZXplot(x1,y1, colour);
	}
	else
	{
		ZXunplot(x1,y1, colour);
	}
    if (dx > dy) 
    {
        fraction = dy - (dx >> 1);	// same as 2*dy - dx
        while (x1 != x2) 
        {
           if (fraction >= 0) 
           {
               y1 += stepy;
               fraction -= dx;	// same as fraction -= 2*dx
           }
           x1 += stepx;
           fraction += dy;	// same as fraction -= 2*dy
		   
		   if (plotUnplot == 1)
		   {
			ZXplot(x1, y1, colour);
		   }
		   else
		   {
			  ZXunplot (x1, y1, colour);
		   }
        }
     } 
	 else 
	 {
		fraction = dx - (dy >> 1);
		while (y1 != y2) 
		{
			if (fraction >= 0) 
			{
				x1 += stepx;
				fraction -= dy;
			}
			y1 += stepy;
           fraction += dx;
		   if (plotUnplot == 1)
		   {
				ZXplot(x1, y1, colour);
		   }
		   else
		   {
			   ZXunplot(x1, y1, colour);
		   }
		   
        }
     }
}


void ZXCircle(int xc, int yc, int r, unsigned char colour, unsigned char plotUnplot)
{
	// if plotUnplot = 1, then plot
	// else unplot
	
    unsigned int x = r;
    unsigned int y = 0;//local coords     
    int cd2 = 0;    //current distance squared - radius squared

    if (!r) return;
	
	
	
	if (plotUnplot == 1)
	{
		ZXplot(xc-r, yc, colour);
		ZXplot(xc+r, yc, colour);
		ZXplot(xc, yc-r, colour);
		ZXplot(xc, yc+r, colour);
	}
	else
	{
		ZXunplot(xc-r, yc, colour);
		ZXunplot(xc+r, yc, colour);
		ZXunplot(xc, yc-r, colour);
		ZXunplot(xc, yc+r, colour);
	}
    while (x > y)    //only formulate 1/8 of circle
    {
        cd2-= (--x) - (++y);
        if (cd2 < 0) cd2+=x++;
		
		if (plotUnplot == 1)
		{
			ZXplot(xc-x, yc-y, colour);//upper left left
			ZXplot(xc-y, yc-x, colour);//upper upper left
			ZXplot(xc+y, yc-x, colour);//upper upper right
			ZXplot(xc+x, yc-y, colour);//upper right right
			ZXplot(xc-x, yc+y, colour);//lower left left
			ZXplot(xc-y, yc+x, colour);//lower lower left
			ZXplot(xc+y, yc+x, colour);//lower lower right
			ZXplot(xc+x, yc+y, colour);//lower right right
		}
		else
		{
			ZXunplot(xc-x, yc-y, colour);//upper left left
			ZXunplot(xc-y, yc-x, colour);//upper upper left
			ZXunplot(xc+y, yc-x, colour);//upper upper right
			ZXunplot(xc+x, yc-y, colour);//upper right right
			ZXunplot(xc-x, yc+y, colour);//lower left left
			ZXunplot(xc-y, yc+x, colour);//lower lower left
			ZXunplot(xc+y, yc+x, colour);//lower lower right
			ZXunplot(xc+x, yc+y, colour);//lower right right
		}
     } 
}


void ZXTriangle (int topx, int topy, int rightx, int righty, unsigned char colour, unsigned char plotUnplot)
{
    int base =0;
    base = 2* rightx-topx;
    ZXLine(topx,topy, rightx,righty,colour, plotUnplot);                //draw hypotenuse
    ZXLine(topx-base/2, righty, rightx,righty,colour, plotUnplot);         // draw base
    ZXLine(topx-base/2, righty, topx,topy,colour, plotUnplot);            // draw hypotenuse
    
}

void ZXSquare(int x, int y, int size, unsigned char colour, unsigned char plotUnplot)
{
	int i;
	int j;	
	
	if (size > 0 )
	{
		i = 0;
		j = 0;
		for( i = x; i <= ( x + size ); i++ )
		{
			if (plotUnplot == 1)
			{
				ZXplot(i, y, colour);
				ZXplot(i, ( y + size ), colour);
			}
			else
			{
				ZXunplot(i, y, colour);
				ZXunplot(i, ( y + size ), colour);
			}			
		}

        for(j = y; j <= ( y + size ); j++ )
        {
            if (plotUnplot == 1)
			{
				ZXplot(x, j, colour);
				ZXplot(( x + size ), j, colour);
			}
			else
			{
				ZXunplot(x, j, colour);
				ZXunplot(( x + size ), j, colour);
			}
        }
    }
}

//https://github.com/Industry-Explorers-Graphics/graphicsLib/blob/master/render.c
void ZXRectangle(int x, int y, int width, int height, unsigned char colour, unsigned char plotUnplot)
{
	int i;
	int j;
	
	if ( height > 0 && width > 0 )
	{
		i = 0;
		j = 0;
		for( i = x; i <= ( x + height ); i++ )
		{
			if (plotUnplot == 1)
			{
				ZXplot(i, y, colour);
				ZXplot(i, ( y + width ), colour);
			}
			else
			{
				ZXunplot(i, y, colour);
				ZXunplot(i, ( y + width ), colour);
			}			
		}

        for(j = y; j <= ( y + width ); j++ )
        {			
            if (plotUnplot == 1)
			{
				ZXplot(x, j, colour);
				ZXplot(( x + height ), j, colour);
			}
			else
			{
				ZXunplot(x, j, colour);
				ZXunplot(( x + height ), j, colour);
			}
        }
    }
}


//fastest
void ZXEllipse(int xc, int yc, int rx, int ry, unsigned char colour, unsigned char plotUnplot)
{
	int x, y;
	long a2, b2;
	long p;
	long foura2, fourb2;
	long twoa2, twob2;
	long u, v;
	
	x = 0; 
	y = ry; 
	a2 = (long)(rx * rx);
	b2 = (long)(ry * ry);
	p = (b2 + b2) - (a2 + a2) * ry + a2;//p = 2 * b2 - 2 * a2 * ry + a2;
	foura2 = (a2 + a2 + a2 + a2); // foura2 = 4 * a2;
	fourb2 = (b2 + b2 + b2 + b2); //fourb2 = 4 * b2;
	twoa2 = (a2 + a2);
	
	u = 0; 
	v = foura2 * ry; 
	twob2 = (b2 + b2);
	
	while(u < v) //first while
	{
		if (plotUnplot == 1)
        {
            ZXplot(xc-x, yc-y, colour);
            ZXplot(xc+x, yc+y, colour);
            ZXplot(xc-x, yc+y, colour);
            ZXplot(xc+x, yc-y, colour);
        }
        else
        {
            ZXunplot(xc-x, yc-y, colour);
            ZXunplot(xc+x, yc+y, colour);
            ZXunplot(xc-x, yc+y, colour);
            ZXunplot(xc+x, yc-y, colour);
        }
		
		x++;
		u += fourb2;
		if(p > 0) 
		{
			y--;
			v -= foura2;
			p += u - v + twob2;
		}
		else
		{
			p += u + twob2;
		}
	}
	
	while(y >= 0) //second while
	{
		if (plotUnplot == 1)
        {
            ZXplot(xc-x, yc-y, colour);
            ZXplot(xc+x, yc+y, colour);
            ZXplot(xc-x, yc+y, colour);
            ZXplot(xc+x, yc-y, colour);
        }
        else
        {
            ZXunplot(xc-x, yc-y, colour);
            ZXunplot(xc+x, yc+y, colour);
            ZXunplot(xc-x, yc+y, colour);
            ZXunplot(xc+x, yc-y, colour);
        }
		y--;
		v -= foura2;
		if(p < 0) 
		{
			x++;
			u += fourb2;
			p += u - v + twoa2;
		}
		else
		{
			p += -v + twoa2;
		}
	}
}



void ZXArc(int cx, int cy, int xRadius, int yRadius, unsigned char colour, unsigned char plotUnplot)
{    
    int x;
	int	y;
    long xChange;
	long yChange;
	long ellipseError;
	long ellipseError2;
	long twoAsquare;
	long twoBsquare;
	long stoppingX;
	long stoppingY;
	
	twoAsquare = 2 * (long)(xRadius * xRadius);	
	twoBsquare = 2 * (long)(yRadius * yRadius);
	
	x = xRadius;
	y = 0;
  
	xChange = (long)(yRadius * yRadius * (1 - 2 * (long)xRadius));
	//xChange = (long)yRadius * (long)yRadius * (1 - 2 * (long)xRadius);
	
	yChange = (long)(xRadius * xRadius);
	//yChange = ((long)xRadius * (long)xRadius);

	ellipseError = 0;
	stoppingX = twoBsquare * (long)xRadius;
	stoppingY = 0;
  
    while (stoppingX >= stoppingY)	// 1st set of points
    {
        if (plotUnplot == 1)
        {
			//ZXplot(cx+x, cy+y, colour);
            //ZXplot(cx-x, cy+y, colour);
			
            ZXplot(cx-x, cy-y, colour);
            ZXplot(cx+x, cy-y, colour);
        }
        else
        {
			//ZXunplot(cx+x, cy+y, colour);
            //ZXunplot(cx-x, cy+y, colour);
			
            ZXunplot(cx-x, cy-y, colour);            
            ZXunplot(cx+x, cy-y, colour);
        }
		
		
        y++;
        stoppingY += twoAsquare;
		ellipseError += yChange;
		yChange += twoAsquare;
        
		ellipseError2 = (ellipseError + xChange) + (ellipseError + xChange);
		
        if (ellipseError2 > 0 )
        {
			x--;
			stoppingX -= twoBsquare;
			ellipseError += xChange;
			xChange += twoBsquare;
        }
    }
    
	x = 0;
	y = yRadius;
	
	xChange = (long)(yRadius * yRadius);
	yChange = (long)(xRadius * xRadius * (1 - 2 * (long)yRadius));

	ellipseError = 0;
	stoppingX = 0;
	stoppingY = twoAsquare * (long)yRadius;
    
    while (stoppingX <= stoppingY)	//2nd set of points
    {
        if (plotUnplot == 1)
        {
			//ZXplot(cx+x, cy+y, colour);
            //ZXplot(cx-x, cy+y, colour);
			
            ZXplot(cx-x, cy-y, colour);            
            ZXplot(cx+x, cy-y, colour);
        }
        else
        {
			//ZXunplot(cx+x, cy+y, colour);
            //ZXunplot(cx-x, cy+y, colour);
			
            ZXunplot(cx-x, cy-y, colour);            
            ZXunplot(cx+x, cy-y, colour);
        }
		

        x++;
		stoppingX += twoBsquare;
		ellipseError += xChange;
		xChange += twoBsquare;

        if ((2 * ellipseError + yChange) > 0 )
        {
            y--;
			stoppingY -= twoAsquare ;
			ellipseError += yChange ;
			yChange += twoAsquare ;
        }        
    }
}



//http://www.iasj.net/iasj?func=fulltext&aId=38879
void ZXParabola(int xc, int yc, int p, int bound, unsigned char colour, unsigned char plotUnplot)
// p = length
{
	int x,y,d,p2,p4;
	
	p2 = 2 * p;
	p4 = p2 * 2;
	x = 0; 
	y = 0;
	d = 1 - p;
	
	while ( ( y < p ) && ( x <= bound ) )
	{
		//draw(xc, yc, x, y);
		if (plotUnplot == 1)
		{
			ZXplot(xc - x, yc - y, colour);
			ZXplot(xc - x, yc + y, colour);
			
			//ZXplot(xc + x, yc + y, colour);
			//ZXplot(xc + x, yc - y, colour);
			
			/*
			ZXplot(xc - x, yc - y, colour);
			ZXplot(xc + x, yc - y, colour);
			*/
		}
		else
		{
			ZXunplot(xc - x, yc - y, colour);
			ZXunplot(xc - x, yc + y, colour);
		}
	
		if( d >= 0 )
		{
			x++;
			d -= p2;
		}
		
		y++;
		d += 2 * y + 1;
	}
	
	if( d == 1 ) 
	{
		d = 1 - p4;
	}
	else 
	{
		d = 1 - p2;
	}
	while( x <= bound )
	{
		//draw(xc, yc, x, y);
		if (plotUnplot == 1)
		{
			ZXplot(xc - x, yc - y, colour);
			ZXplot(xc - x, yc + y, colour);
		}
		else
		{
			ZXunplot(xc - x, yc - y, colour);
			ZXunplot(xc - x, yc + y, colour);			
		}
		
		if( d <= 0 )
		{
			y++;
			d += 4 * y;
		}
		
		x++;
		d -= p4;
	}
}




//https://answers.yahoo.com/question/index?qid=20071212061504AAVmCCp
//https://answers.yahoo.com/question/index?qid=20070210050742AAynIDM



void FilledCircle(int x, int y, int r, unsigned char colour, unsigned char plotUnplot)
{
	//brute force method
	int r2;
	int area;
	int rr;
	int i;
	int tx;
	int ty;

	i = 0;	
	rr = r << 1;
	r2 = r * r;
	area = r2 << 2;
	
	while (i < area)
	{
		tx = (i % rr) - r;
		ty = (i / rr) - r;

		if (tx * tx + ty * ty <= r2)
		{
			if (plotUnplot == 1)
			{
				ZXplot(x + tx, y + ty, colour);
			}
			else
			{
				ZXunplot(x + tx, y + ty, colour);
			}
		}
		i++;
	}
}



void bezier(int x1, int y1, int x2, int y2, int x3, int y3, unsigned char colour, unsigned char plotUnplot) 
{
	//int t;	
	int x;
	int y;
	float i;
	int percent;
	float ii;
	
	float k0;
	float k1;
	float k2;
	float inv;
	
	x = 0;
	y = 0;
	i = 0;
	percent = 100;
	ii = 0;
	
	
	//t = percentage
    //for(t = 0 ; t < percent ; t++)
	for(i = 0 ; i < 1 ; i += .01)
    {
		//i = (float)t / percent;

		inv = 1 - i; 	
		k0 = (inv) * (inv);
		k1 = (2 * i) * (inv);
		k2 = i * i;

		x = (k0 * x1) + (k1 * x2) + (k2 * x3);		
		y = (k0 * y1) + (k1 * y2) + (k2 * y3);
		
		if (plotUnplot == 1)
		{
			ZXplot(x, y, colour);
		}
		else
		{
			ZXunplot(x, y, colour);
		}
    }
}

void bezier2(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, unsigned char colour, unsigned char plotUnplot)
{
	int last_x;
	int last_y;
	int kN;
	int x;
	int y;
	
	int i;
	float t;
	
	float k0;
	float k1;
	float k2;
	float k3;
	
	last_x = x0;
	last_y = y0;
	
	i = 1;
	kN = 20; //steps
	
	for(i = 1; i <= kN; i++)
	{
		t = ((float) i) / kN;
		
		k0 = (pow(1 - t, 3));
		k1 = (3 * t * pow(1 - t, 2));
		k2 = (3 * pow(t, 2) * (1 - t));
		k3 = (pow(t, 3));
		
		x = (x0 * k0) + (x1 * k1) + (x2 * k2) + (x3 * k3);
		y = (y0 * k0) + (y1 * k1) + (y2 * k2) + (y3 * k3);
		
		if (plotUnplot == 1)
		{
			ZXLine(last_x, last_y, x, y, colour, 1);
		}
		else
		{
			ZXLine(last_x, last_y, x, y, colour, 0);
		}
		
		last_x = x;
		last_y = y;
	}
}


// https://github.com/plesner/avg/blob/master/display.ino
//http://denemo.org/~jjbenham/gub/downloads/cairo/cairo-1.12.2/src/cairo-mesh-pattern-rasterizer.c


void ZXQuad1(int x1, int y1, int ctrlX, int ctrlY, int x2, int y2, unsigned char steps, unsigned char colour, unsigned char plotUnplot)
{
	int last_x;
	int last_y;
	int x;
	int y;
	
	int i;
	
	float d ;
	
	//ok as long
	long kx1;
	long kx2;
	long kx3;	
	long ky1;
	long ky2;
	long ky3;
	//ok as long
	
	//problems as long  - no curve
	float dx0;
	float dx1;
	float dx2;
	float dx3;
	float dy0;
	float dy1;
	float dy2;
	float dy3;
	//problems as long
	
	long dx, dy;
	
	last_x = x1;
	last_y = y1;
	
	i = 1;
	
	d = 1.0 / steps;

	kx1 = (ctrlX - x1) * 3;
	ky1 = (ctrlY - y1) * 3; 
	
	kx2 = (ctrlX - ctrlX * 2 + x1) * 3;
	ky2 = (ctrlY - ctrlY * 2 + y1) * 3;
	
	kx3 = x2 - ctrlX * 3 + ctrlX * 3 - x1;	
	ky3 = y2 - ctrlY * 3 + ctrlY * 3 - y1;
	
	dx0 = x1;
	dy0 = y1;
	
	dx1 = (((kx3 * d) + kx2) * d + kx1) * d;
	dy1 = (((ky3 * d) + ky2) * d + ky1) * d;
	
	dx2 = ((kx3 * (3 * d)) + kx2) * (2 * d * d);
	dy2 = ((ky3 * (3 * d)) + ky2) * (2 * d * d);
	
	dx3 = kx3 * (6 * d * d * d);
	dy3 = ky3 * (6 * d * d * d);
	
	for (i = 1; i <= steps; i++) 
	{
		dx0 += dx1;
		dx1 += dx2;
		dx2 += dx3;
		dy0 += dy1;
		dy1 += dy2;
		dy2 += dy3;
		
		
		
		/*
		dx0 = (dx0 + dx1);
		dx1 = (dx1 + dx2);
		dx2 = (dx2 + dx3);		
		dy0 = (dy0 + dy1);
		dy1 = (dy1 + dy2);
		dy2 = (dy2 + dy3);
		*/
		
		dx = dx0;
		dy = dy0;
		x =  dx;
		y =  dy;
		
		if (plotUnplot == 1)
		{
			ZXLine(last_x, last_y, x, y, colour, 1);
		}
		else
		{
			ZXLine(last_x, last_y, x, y, colour, 0);
		}	
		last_x = x;
		last_y = y;
	}
}


	// cubic
	//var result = 
	//	Pow(1-t, 3)*x0 +
	//	3*t*Pow(1-t, 2)*x1 +
	//	3*(1-t)*Pow(t, 2)*x2 + 
	//	Pow(t, 3)*x3;
	
	// cubic
	// Point<double> n = 
	// (p[0] * pow(1 - t, 3)) + 
	// (p[1] * 3 * t * pow(1 - t, 2)) + 
	// (p[2] * 3 * pow(t, 2) * (1 - t)) + 
	// (p[3] * pow(t, 3));
	
	// quadratic
	//var result = 
	//	Pow(1-t, 2)*x0 + 
	//	2*t*(1-t)*x1 + 
	//	Pow(t, 2)*x2;
	

	
// https://github.com/plesner/avg/blob/master/display.ino
void ZXQuadraticBezier(int x1, int y1, int ctrlX, int ctrlY, int x2, int y2, unsigned char steps, unsigned char colour, unsigned char plotUnplot)
{
	int last_x = 0;
	int last_y = 0;
	int x = 0;
	int y = 0;
	
	int i = 0;
	
	float d = 0;
	
	float kx1;
	float kx2;
	float kx3;
	
	float ky1;
	float ky2;
	float ky3;
	
	float dx0;
	float dx1;
	float dx2;
	float dx3;
	float dy0;
	float dy1;
	float dy2;
	float dy3;
	
	last_x = x1;
	last_y = y1;
	
	i = 1;
	
	d = 1.0 / steps;
	
	
	kx1 = (ctrlX - x1) * 3; 
	kx2 = (ctrlX - ctrlX * 2 + x1) * 3;
	kx3 = x2 - ctrlX * 3 + ctrlX * 3 - x1;
	
	ky1 = (ctrlY - y1) * 3; 
	ky2 = (ctrlY - ctrlY * 2 + y1) * 3;
	ky3 = y2 - ctrlY * 3 + ctrlY * 3 - y1;
	
	dx0 = x1;
	dx1 = (((kx3 * d) + kx2) * d + kx1) * d; 
	dx2 = ((kx3 * (3 * d)) + kx2) * (2 * d * d);
	dx3 = kx3 * (6 * d * d * d);
	
	dy0 = y1;
	dy1 = (((ky3 * d) + ky2) * d + ky1) * d; 
	dy2 = ((ky3 * (3 * d)) + ky2) * (2 * d * d);
	dy3 = ky3 * (6 * d * d * d);
	
	for (i = 1; i <= steps; i++) 
	{
		/*dx0 = dx0 + dx1;
		dx1 = dx1 + dx2;
		dx2 = dx2 + dx3;
		dy0 = dy0 + dy1;
		dy1 = dy1 + dy2;
		dy2 = dy2 + dy3;*/
		
		dx0 += dx1;
		dx1 += dx2;
		dx2 += dx3;
		dy0 += dy1;
		dy1 += dy2;
		dy2 += dy3;
		
		x = dx0;
		y = dy0;
		
		if (plotUnplot == 1)
		{
			ZXLine(last_x, last_y, x, y, colour, 1);
		}
		else
		{
			ZXLine(last_x, last_y, x, y, colour, 0);
		}	
		last_x = x;
		last_y = y;
	}
}


void ZXQuadraticBezier1(int x1, int y1, int ctrlX, int ctrlY, int x2, int y2, unsigned char steps, unsigned char colour, unsigned char plotUnplot)
{
	int last_x = 0;
	int last_y = 0;
	int x = 0;
	int y = 0;
	
	int i = 0;
	
	long d = 0;
	
	long kx1;
	long kx2;
	long kx3;
	
	long ky1;
	long ky2;
	long ky3;
	
	long dx0;
	long dx1;
	long dx2;
	long dx3;
	long dy0;
	long dy1;
	long dy2;
	long dy3;
	
	last_x = x1;
	last_y = y1;
	
	i = 1;
	
	d = 1000 / steps;
	
	
	kx1 = (ctrlX - x1) * 3; 
	kx2 = (ctrlX - ctrlX * 2 + x1) * 3;
	kx3 = x2 - ctrlX * 3 + ctrlX * 3 - x1;
	
	ky1 = (ctrlY - y1) * 3; 
	ky2 = (ctrlY - ctrlY * 2 + y1) * 3;
	ky3 = y2 - ctrlY * 3 + ctrlY * 3 - y1;
	
	dx0 = x1;
	dx1 = (((kx3 * d) + kx2) * d + kx1) * d; 
	dx2 = ((kx3 * (3 * d)) + kx2) * (2 * d * d);
	dx3 = kx3 * (6 * d * d * d);
	
	dy0 = y1;
	dy1 = (((ky3 * d) + ky2) * d + ky1) * d; 
	dy2 = ((ky3 * (3 * d)) + ky2) * (2 * d * d);
	dy3 = ky3 * (6 * d * d * d);
	
	for (i = 1; i <= steps; i++) 
	{
		dx0 = dx0 + dx1;
		dx1 = dx1 + dx2;
		dx2 = dx2 + dx3;
		dy0 = dy0 + dy1;
		dy1 = dy1 + dy2;
		dy2 = dy2 + dy3;
		
		dx0 = dx0>>14;
		dy0 = dy0>>14;
		
		x = (int)dx0;
		y = (int)dy0;
		
		if (plotUnplot == 1)
		{
			ZXLine(last_x, last_y, x, y, colour, 1);
		}
		else
		{
			ZXLine(last_x, last_y, x, y, colour, 0);
		}	
		last_x = x;
		last_y = y;
	}
}











// https://github.com/plesner/avg/blob/master/display.ino
void ZXCubicBezier(int x1, int y1, int ctrlx1, int ctrly1, int ctrlx2, int ctrly2, int x2, int y2, unsigned char steps, unsigned char colour, unsigned char plotUnplot)
{
	int last_x = 0;
	int last_y = 0;
	int x = 0;
	int y = 0;
	
	int i = 0;
	
	float d = 0;
	
	float kx1;
	float kx2;
	float kx3;
	
	float ky1;
	float ky2;
	float ky3;
	
	float dx0;
	float dx1;
	float dx2;
	float dx3;
	float dy0;
	float dy1;
	float dy2;
	float dy3;
	
	last_x = x1;
	last_y = y1;
	
	i = 1;
	
	d = 1.0 / steps;
	
	//kx0 = x1;
	kx1 = (ctrlx1 - x1) * 3; 
	kx2 = (ctrlx2 - ctrlx1 * 2 + x1) * 3;
	kx3 = x2 - ctrlx2 * 3 + ctrlx1 * 3 - x1;
	//ky0 = y1;
	ky1 = (ctrly1 - y1) * 3; 
	ky2 = (ctrly2 - ctrly1 * 2 + y1) * 3;
	ky3 = y2 - ctrly2 * 3 + ctrly1 * 3 - y1;
	
	dx0 = x1;
	dx1 = (((kx3 * d) + kx2) * d + kx1) * d; 
	dx2 = ((kx3 * (3 * d)) + kx2) * (2 * d * d);
	dx3 = kx3 * (6 * d * d * d);
	
	dy0 = y1;
	dy1 = (((ky3 * d) + ky2) * d + ky1) * d; 
	dy2 = ((ky3 * (3 * d)) + ky2) * (2 * d * d);
	dy3 = ky3 * (6 * d * d * d);
	
	for (i = 1; i <= steps; i++) 
	{
		dx0 = dx0 + dx1;
		dx1 = dx1 + dx2;
		dx2 = dx2 + dx3;
		dy0 = dy0 + dy1;
		dy1 = dy1 + dy2;
		dy2 = dy2 + dy3;
		
		x = dx0;
		y = dy0;
		
		if (plotUnplot == 1)
		{
			ZXLine(last_x, last_y, x, y, colour, 1);
		}
		else
		{
			ZXLine(last_x, last_y, x, y, colour, 0);
		}	
		last_x = x;
		last_y = y;
	}
}

 void DrawBezierFX( int ax, int ay, int bx, int by, int cx, int cy, int dx, int dy, unsigned char colour, unsigned char plotUnplot)
{
	long i;
	long t;
	long u;
	long a,b,c,d;
	long x;
	long y;
	long steps;
	
	steps = 1024;//1024

    for(i=0; i<=steps; i+=1)
    {
		t = i<<5;

		u = (steps-i)<<5;

		a = ((((u*u)>>15)*u)>>15);
		b = ((((t*u)>>15)*u)>>15)*3;
		c = ((((t*t)>>15)*u)>>15)*3;
		d = ((((t*t)>>15)*t)>>15);


		x = ax*a + bx*b + cx*c + dx*d;
		y = ay*a + by*b + cy*c + dy*d;

     //SetPixel(x>>15 ,y>>15, color);
	 if (plotUnplot == 1)
		{
			ZXplot(x>>15, y>>15, colour);
		}
		else
		{
			ZXunplot(x>>15, y>>15, colour);
		}
	 //ZXplot(x>>15, y>>15, colour);

     }

}


/*
void Display::draw_cubic_bezier_faster_diffs(Point<double> *p) {
  static const double d = 1.0 / kN;

  // Calculate the four ks.  
  Point<double> k0 = p[0];
  Point<double> k1 = (p[1] - p[0]) * 3;
  Point<double> k2 = (p[2] - p[1] * 2 + p[0]) * 3;
  Point<double> k3 = p[3] - p[2] * 3 + p[1] * 3 - p[0];
  
  // Caldulate the four ds.
  Point<double> d0 = k0;
  Point<double> d1 = (((k3 * d) + k2) * d + k1) * d;
  Point<double> d2 = ((k3 * (3 * d)) + k2) * (2 * d * d);
  Point<double> d3 = k3 * (6 * d * d * d);
  
  // quadratic
	//var result = 
	//	Pow(1-t, 2)*x0 + 
	//	2*t*(1-t)*x1 + 
	//	Pow(t, 2)*x2;
  
  // Plot
  int16_t last_x = static_cast<int16_t>(p[0].x);
  int16_t last_y = static_cast<int16_t>(p[0].y);
  for (uint8_t i = 1; i <= kN; i++) {
    d0 = d0 + d1;
    d1 = d1 + d2;
    d2 = d2 + d3;
    int16_t x = static_cast<int16_t>(d0.x);
    int16_t y = static_cast<int16_t>(d0.y);
    draw_line(last_x, last_y, x, y);
    last_x = x;
    last_y = y;
  }
}*/

//http://www.ericeastwood.com/blog/25/curves-and-arcs-quadratic-cubic-elliptical-svg-implementations

//  point On Quadratic BezierCurve
//var result = Math.pow(1-t, 2)*x0 + 2*t*(1-t)*x1 + Math.pow(t, 2)*x2;

// pointOn Cubic BezierCurve
//var result = Math.pow(1-t, 3)*x0 + 3*t*Math.pow(1-t, 2)*x1 + 3*(1-t)*Math.pow(t, 2)*x2 + Math.pow(t, 3)*x3;











void bezier4(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, unsigned char colour, unsigned char plotUnplot)
{
	int last_x = 0;
	int last_y = 0;
	int kN = 0;
	int x = 0;
	int y = 0;
	
	int i = 0;
	
	float d = 0;
	
	float kx0;
	float kx1;
	float kx2;
	float kx3;
	float ky0;
	float ky1;
	float ky2;
	float ky3;
	
	float dx0;
	float dx1;
	float dx2;
	float dx3;
	float dy0;
	float dy1;
	float dy2;
	float dy3;
	
	float diffx1;
	float diffx2;
	
	float diffx3;
	float diffy1;
	float diffy2;
	
	float diffy3;
	
	last_x = x0;
	last_y = y0;
	
	i = 1;
	kN = 25; //steps	
	
	d = 1.0 / kN;
	
	diffx1 = x1 - x0;
	diffx2 = x2 - (x1 + x1) + x0;
	diffx3 = (x3 - (x2 + x2 + x2)) + (x1 + x1 + x1) - x0;

	diffy1 = y1 - y0;
	diffy2 = y2 - (y1 + y1) + y0;
	diffy3 = (y3 - (y2 + y2 + y2)) + (y1 + y1 + y1) - y0;
	
	kx0 = x0;
	kx1 = diffx1 + diffx1 + diffx1; 
	kx2 = diffx2 + diffx2 + diffx2;
	kx3 = diffx3;	
	
	ky0 = y0;
	ky1 = diffy1 + diffy1 + diffy1; 
	ky2 = diffy2 + diffy2 + diffy2;
	ky3 = diffy3;
	
	
	
	diffx1 = d + d + d;
	diffx2 = d + d;
	diffx3 = d + d + d + d + d + d;
	//floats
	dx0 = x0;
	dx1 = (((kx3 * d) + kx2) * d + kx1) * d; 
	dx2 = ((kx3 * (diffx1)) + kx2) * ((diffx2) * d);
	dx3 = kx3 * ((diffx3) * d * d);
	
	dy0 = y0;
	dy1 = (((ky3 * d) + ky2) * d + ky1) * d; 
	dy2 = ((ky3 * (diffx1)) + ky2) * ((diffx2) * d);
	dy3 = ky3 * ((diffx3) * d * d);
	//floats
	
	for (i = 1; i <= kN; i++) 
	{
		//floats
		dx0 = dx0 + dx1;
		dx1 = dx1 + dx2;
		dx2 = dx2 + dx3;
		dy0 = dy0 + dy1;
		dy1 = dy1 + dy2;
		dy2 = dy2 + dy3;
		//floats
		
		x = dx0;
		y = dy0;
		
		if (plotUnplot == 1)
		{
			ZXLine(last_x, last_y, x, y, colour, 1);
		}
		else
		{
			ZXLine(last_x, last_y, x, y, colour, 0);
		}	
		last_x = x;
		last_y = y;
	}
}


//https://www.niksula.hut.fi/~hkankaan/Homepages/bezierfast.html


/*
static inline Point<fixed> mult_3(const Point<fixed> &p) 
{
  return (p << 1) + p;
}
void bezier4(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, unsigned char colour, unsigned char plotUnplot)
{
	int kLogN = 4;
	
	// Calculate the four ks.  
	Point<fixed> k0 = p[0];
	Point<fixed> k1 = mult_3(p[1] - p[0]);
	Point<fixed> k2 = mult_3(p[2] - (p[1] << 1) + p[0]);
	Point<fixed> k3 = p[3] + mult_3(p[1] - p[2]) - p[0];
  
	// Caldulate the four ds.
	Point<fixed> d0 = k0;
	Point<fixed> d1 = ((((k3 >> kLogN) + k2) >> kLogN) + k1) >> kLogN;
	Point<fixed> d2 = ((mult_3(k3) >> kLogN) + k2) >> (kLogN * 2 - 1);
	Point<fixed> d3 = mult_3(k3) >> (3 * kLogN - 1);
  
	// Plot
  int16_t last_x = p[0].x.to_int16();
  int16_t last_y = p[0].y.to_int16();
  for (uint8_t i = 1; i <= kN; i++) {
    d0 = d0 + d1;
    d1 = d1 + d2;
    d2 = d2 + d3;
    int16_t x = d0.x.to_int16();
    int16_t y = d0.y.to_int16();
    draw_line(last_x, last_y, x, y);
    last_x = x;
    last_y = y;
  }
}
*/



//http://h14s.p5r.org/2013/01/bezier.html
//https://github.com/plesner/avg/blob/master/display.ino

//https://github.com/MadLittleMods/svg-curve-lib/blob/master/src/c%2B%2B/SVGCurveLib.cpp




//eof