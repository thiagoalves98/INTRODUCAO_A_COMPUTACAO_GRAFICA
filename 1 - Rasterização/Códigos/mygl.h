#ifndef MYGL_H
#define MYGL_H

#include "core.h"
#include "frame_buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void MyGlDraw(void);

typedef struct{

	int x, y;
	unsigned char R, G, B, A;
	
}Ponto;

typedef struct{

	Ponto x,y;
	
}Aresta;

typedef struct{

	Aresta A,B;

}Vertice;

#endif  // MYGL_H
