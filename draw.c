#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
  if (points->lastcol==points->cols) {
	grow_matrix(points,points->cols+1);
  }
  	points->m[0][points->lastcol]=x;
  	points->m[1][points->lastcol]=y;
  	points->m[2][points->lastcol]=z;
  	points->m[3][points->lastcol]=1;
	points->lastcol++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
	add_point(points,x0,y0,z0);
	add_point(points,x1,y1,z1);
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void octant1(int x0, int y0, int x1, int y1, screen s, color c);
void octant2(int x0, int y0, int x1, int y1, screen s, color c);
void octant7(int x0, int y0, int x1, int y1, screen s, color c);
void octant8(int x0, int y0, int x1, int y1, screen s, color c);

void draw_lines( struct matrix * points, screen s, color c) {
	int x0,y0,x1,y1,k;
	for (k=0;k<points->lastcol;k+=2){
		x0=points->m[0][k];
    		y0=points->m[1][k];
    		x1=points->m[0][k+1];
    		y1=points->m[1][k+1];
    		draw_line(x0,y0,x1,y1,s,c);
	}
}





void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
	if (x1<x0) {
		draw_line(x1,y1,x0,x1,s,c);
		return;	
	}

	int dy = y1-y0;
	int dx = x1-x0;

	if (dy>=dx) {octant2(x0,y0,x1,y1,s,c);}
	else if (dx>dy && dy>=0) {octant1(x0,y0,x1,y1,s,c);}
	else if (dy*-1<dx && dy<0) {octant8(x0,y0,x1,y1,s,c);}
	else {octant7(x0,y0,x1,y1,s,c);}
}
void octant1(int x0, int y0, int x1, int y1, screen s, color c) {
	int A = y1-y0;
	int B = x0-x1;
	
	int x = x0;
	int y = y0;

	int d = 2*A + B;
	while (x<=x1){
		plot(s,c,x,y);
		if (d>0) {
			y++;
			d+=2*B;
		}
		x++;
		d+=2*A;
	}
}
void octant2(int x0, int y0, int x1, int y1, screen s, color c) {

	int A = y1-y0;
	int B = x0-x1;
	
	int x = x0;
	int y = y0;

	int d = A + 2*B;
	while (y <= y1){
		plot(s,c,x,y);
		if (d<0) {
			x++;
			d+=2*A;
		}
		y++;
		d+=2*B;
	}

}
void octant8(int x0, int y0, int x1, int y1, screen s, color c) {

	int A = y1-y0;
	int B = x0-x1;
	
	int x = x0;
	int y = y0;

	int d = 2*A - B;
	while (x<=x1){
		plot(s,c,x,y);
		if (d<0) {
			y--;
			d-=2*B;
		}
		x++;
		d+=2*A;
	}
}
void octant7(int x0, int y0, int x1, int y1, screen s, color c) {
	
	int A = y1-y0;
	int B = x0-x1;
	
	int x = x0;
	int y = y0;

	int d = A - 2*B;
	while (y>=y1){
		plot(s,c,x,y);
		if (d>0) {
			x++;
			d+=2*A;
		}
		y--;
		d-=2*B;
	}
}

