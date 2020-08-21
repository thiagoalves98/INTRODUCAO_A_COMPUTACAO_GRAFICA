#include "mygl.h"

float GetDistancia(int x0, int y0, int x1, int y1){
    
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    return sqrt((dx*dx)+(dy*dy));
}

void InterpolarCor(Ponto *A, Ponto *B, unsigned char *RGBA, float d){

	RGBA[0] = (B->R * d) + ((1-d)*A->R);
	RGBA[1] = (B->G * d) + ((1-d)*A->G);
	RGBA[2] = (B->B * d) + ((1-d)*A->B);
	RGBA[3] = (B->A * d) + ((1-d)*A->A);
}

void PutPixel(int x, int y, unsigned char R, unsigned char G, unsigned char B, unsigned char A){
	
	int offset = (x*4) + (y*4*IMAGE_WIDTH);

	fb_ptr[offset + 0] = R;
	fb_ptr[offset + 1] = G;
	fb_ptr[offset + 2] = B;
	fb_ptr[offset + 3] = A;
}

void DrawLine(Ponto A, Ponto B){

	//Obtem as coordenadas
	int x0 = A.x;
	int y0 = A.y;
	int x1 = B.x;
	int y1 = B.y;

	int dx = x1 - x0;
	int dy = y1 - y0;

	int inclinacao;

	unsigned char RGBA[3];

	if(dx < 0){
		DrawLine(B, A);
		return;
	}

	if(dy < 0){
		inclinacao = -1;
	}else{
		inclinacao = 1;
	}

	int d;

	int x = x0;
	int y = y0;

	float Distancia_total = GetDistancia(x0,y0,x1,y1);

	float Distancia = GetDistancia(x,y,x1,y1)/Distancia_total;

	InterpolarCor(&A, &B, RGBA, Distancia);

	PutPixel(x, y, RGBA[0], RGBA[1], RGBA[2], RGBA[3]);

	if(dx >= inclinacao*dy){

		if(dy < 0){

			d = 2*dy+dx;

			while(x < x1){

				if(dy < 0){

					d += 2*(dy+dx);
					x++;
					y--;
				}

				else{

					d += 2*dy;
					x++;
				}

				Distancia = GetDistancia(x,y,x1,y1)/Distancia_total;
				
				InterpolarCor(&A, &B, RGBA, Distancia);
				
				PutPixel(x, y, RGBA[0], RGBA[1], RGBA[2], RGBA[3]);
			}
		}

		else{

			d = 2*dy-dx;

			while(x < x1){

				if(d < 0){

					d += 2*dy;
					x++;
				}

				else{

					d += 2*(dy-dx);
					x++;
					y++;
				}

				Distancia = GetDistancia(x,y,x1,y1)/Distancia_total;
				
				InterpolarCor(&A, &B, RGBA, Distancia);
				
				PutPixel(x, y, RGBA[0], RGBA[1], RGBA[2], RGBA[3]);
			}
		}
	}

	else{

		if(dy < 0){

			d = dy + 2*dx;

			while(y > y1){

				if(d < 0){

					d += 2*dx;
					y--;
				}

				else{

					d += 2*(dy+dx);
					x++;
					y--;
				}

				Distancia = GetDistancia(x,y,x1,y1)/Distancia_total;
				
				InterpolarCor(&A, &B, RGBA, Distancia);
				
				PutPixel(x, y, RGBA[0], RGBA[1], RGBA[2], RGBA[3]);
			}

		}

		else{

			d = dy - 2*dx;

			while(y < y1){

				if(d < 0){

					d += 2*(dy-dx);
					x++;
					y++;
				}

				else{
					d += -2*dx;
					y++;
				}

				Distancia = GetDistancia(x,y,x1,y1)/Distancia_total;
				
				InterpolarCor(&A, &B, RGBA, Distancia);
				
				PutPixel(x, y, RGBA[0], RGBA[1], RGBA[2], RGBA[3]);
			}
		}
	}

	Distancia = GetDistancia(x,y,x1,y1)/Distancia_total;
				
	InterpolarCor(&A, &B, RGBA, Distancia);
				
	PutPixel(x, y, RGBA[0], RGBA[1], RGBA[2], RGBA[3]);	
}

void DrawTriangle (Ponto A, Ponto B, Ponto C){

	DrawLine(A,B);
	DrawLine(B,C);
	DrawLine(C,A);
}

void MyGlDraw(void) {

	//Testes PutPixel
	/**
	PutPixel(0, 0, 0, 255, 0, 255);

	PutPixel(511, 511, 255, 0, 0, 255);
	**/

	//Testes DrawLine
	/**
	Ponto A3 = {0, 0, 0, 255, 0, 255};
	Ponto B3 = {511, 511, 255, 0, 0, 255};
	DrawLine(A3,B3);

	Ponto A7 = {512, 0, 0, 255, 0, 255};
	Ponto B7 = {0, 512, 255, 0, 0, 255};
	DrawLine(A7,B7);

	Ponto A4 = {0, 0, 255, 255, 255, 255};
	Ponto B4 = {256, 511, 0, 0, 255, 255};
	DrawLine(A4,B4);

	Ponto A6 = {511, 0, 255, 255, 255, 255};
	Ponto B6 = {256, 511, 0, 0, 255, 255};
	DrawLine(A6,B6);

	Ponto A12 = {512, 512, 255, 255, 255, 255};
	Ponto B12 = {256, 0, 255, 255, 0, 255};
	DrawLine(A12,B12);

	Ponto A14 = {0, 512, 255, 255, 255, 255};
	Ponto B14 = {256, 0, 255, 255, 0, 255};
	DrawLine(A14,B14);

	Ponto A1 = {0, 256, 255, 255, 255, 255};
	Ponto B1 = {511, 256, 255, 0, 255, 255};
	DrawLine(A1,B1);
	**/

	//Testes DrawTriangle
	/**
	Ponto A1 = {256, 10, 255, 255, 255, 255};
	Ponto A2 = {10, 256, 255, 0, 0, 255};
	Ponto A3 = {500, 256, 255, 0, 0, 255};
	DrawTriangle(A1,A2,A3);

	Ponto B1 = {500, 256, 255, 255, 255, 255};
	Ponto B2 = {500, 500, 0, 255, 0, 255};
	Ponto B3 = {256, 500, 0, 255, 0, 255};
	DrawTriangle(B1,B2,B3);

	Ponto C1 = {10, 256, 255, 255, 255, 255};
	Ponto C2 = {10, 500, 0, 0, 255, 255};
	Ponto C3 = {256, 500, 0, 0, 255, 255};
	DrawTriangle(C1,C2,C3);
	**/

	puts(".");
}