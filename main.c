#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
 /*
	Test cases taken from Matteo Wong's main.c:
	https://github.com/matteowong/graphics_matrix/blob/master/main.c
*/
int main() {

  screen s;
  clear_screen(s);
  color c;
  c.green=255;


  struct matrix * m=new_matrix(4,4);
  struct matrix * n=new_matrix(4,3);
  m->lastcol=4;
  n->lastcol=3;
  

  printf("\ntesting ident(m)\n");
  ident(m);
  print_matrix(m);

  n->m[0][0]=4;
  n->m[0][1]=37;
  n->m[3][2]=9;
  n->m[2][2]=10;
  printf("\nmatrix with values\n");
  print_matrix(n);

  printf("\ntesting matrix_mult with identity matrix\nbefore:\n");
  print_matrix(n);
  matrix_mult(m,n);
  printf("\nafter:\n");
  print_matrix(n);

  printf("\ntesting matrix_mult with not identity matrix\n");
  m->m[0][2]=14;
  m->m[1][0]=8;
  m->m[2][2]=17;
  print_matrix(m);
  printf("\nmultipled by\n");
  print_matrix(n);
  matrix_mult(m,n);
  printf("\nresult\n");
  print_matrix(n);

  free_matrix(m);
  free_matrix(n);
  
  struct matrix *edges;

  edges = new_matrix(4, 4);

  printf("testing add_edge, and implicitly add_point\n");
  add_edge(edges,0,350,0,50,400,0);
  add_edge(edges,50,400,0,100,350,0);
  add_edge(edges,0,350,0,100,350,0);

  add_edge(edges,100,400,0,150,350,0);
  add_edge(edges,150,350,0,200,400,0);
  add_edge(edges,100,400,0,200,400,0);
  print_matrix(edges);

  add_edge(edges,200,350,0,250,400,0);
  add_edge(edges,250,400,0,300,350,0);
  add_edge(edges,200,350,0,300,350,0);

  add_edge(edges,300,400,0,350,350,0);
  add_edge(edges,350,350,0,400,400,0);
  add_edge(edges,300,400,0,400,400,0);
  
  add_edge(edges,400,350,0,450,400,0);
  add_edge(edges,450,400,0,500,350,0);
  add_edge(edges,400,350,0,500,350,0);

  
  add_edge(edges,0,300,0,140,300,0);
  add_edge(edges,140,300,0,190,40,0);
  add_edge(edges,0,300,0,190,40,0);

  add_edge(edges,170,300,0,330,300,0);
  add_edge(edges,330,300,0,250,20,0);
  add_edge(edges,170,300,0,250,20,0);

  add_edge(edges,500,300,0,360,300,0);
  add_edge(edges,360,300,0,310,40,0);
  add_edge(edges,500,300,0,310,40,0);

  
  printf("\ndrawing lines\n");
  draw_lines(edges, s, c);
  save_ppm(s,"image.ppm");
  display(s);
  
  free_matrix( edges );
}

