#include <MaxMatrix.h>

int8_t matrix[8][8] = {{ 0, 0, 0, 1, 1, 0, 0, 0 },
		       { 0, 0, 0, 0, 0, 0, 0, 0 },
		       { 0, 0, 0, 0, 0, 0, 0, 0 },
		       { 0, 0, 0, 0, 0, 0, 1, 0 },
		       { 0, 0, 0, 0, 0, 0, 0, 0 },
		       { 0, 0, 0, 0, 0, 0, 0, 0 },
		       { 0, 0, 0, 0, 0, 0, 0, 0 },
		       { 0, 0, 0, 1, 1, 0, 0, 0 }};

int8_t posP1 = 3;
int8_t posP2 = 3;

int8_t posXBall = 1;
int8_t posYBall = 3;
int8_t ballUD = 1;
int8_t ballRL = 1;

int8_t data = 30;
int8_t clock = 32;
int8_t load = 31;
int8_t maxInUse = 1;

MaxMatrix m(data, clock, load, maxInUse);

int8_t ultraDistP1 = 8;
int8_t ultraDistP2 = 8;

int8_t timeRefresh = 10;	//in second so 100ms delay

int begMillis = 0;
int curMillis = 0;

int8_t trigs[2] = {36, 42};
int8_t echos[2] = {37, 43};

int8_t led = 13; 

int8_t zekoS = 0;
int8_t grgaS = 0;

int readUltra(int8_t player)
{
	digitalWrite(trigs[player], HIGH);
	delayMicroseconds(10);
	digitalWrite(trigs[player], LOW);
	delayMicroseconds(5);

	int us = pulseIn(echos[player], HIGH, 10000);
	int dist = us/2/29;

	if(dist == 0)
	{
		dist = 1023;
	}
	
	return dist;
}

void matrixAll(bool in)
{
	for (int i = 0; i < 8; i++) 
	{
		for (int j = 0; j < 8; j++) 
		{
			matrix[i][j] = in;
		}	
	}
}

void maxDraw()
{
	for (int i = 0; i < 8; i++) 
	{
		for (int j = 0; j < 8; j++) 
		{
			m.setDot(i, j, matrix[i][j]);
		}
	}
}

void blinkBlink()
{
	matrixAll(0);
	matrix[0][posP1] = 1;
	matrix[0][posP1+1] = 1;
	matrix[7][posP2] = 1;
	matrix[7][posP2-1] = 1;
	maxDraw();
	delay(100);
	matrixAll(0);
	maxDraw();
	delay(100);
	matrixAll(0);
	matrix[0][posP1] = 1;
	matrix[0][posP1+1] = 1;
	matrix[7][posP2] = 1;
	matrix[7][posP2-1] = 1;
	maxDraw();
	delay(100);
	matrixAll(0);
	maxDraw();
	delay(100);
}

void setup()
{
	Serial.begin(115200);

	pinMode(led,OUTPUT);
	
	m.init();
	m.setIntensity(8);

	begMillis = millis();

	/* maxDraw(); */

	/* delay(100000); */

	Serial.println("Zeko pong");
}

void loop()
{
	/* while(curMillis - begMillis <= 1000/timeRefresh) */
	/* { */
		ultraDistP1 = readUltra(0);
		ultraDistP2 = readUltra(1);

		if(ultraDistP1 >= 21) posP1 = 6;	
		else posP1 = map(ultraDistP1, 3, 20, 0, 6);		

		if (ultraDistP2 >= 21) posP2 = 0;
		else posP2 = map(ultraDistP2, 3, 20, 7, 1);		

		matrixAll(0);
		matrix[posYBall][posXBall] = 1;
		matrix[0][posP1] = 1;
		matrix[0][posP1+1] = 1;
		matrix[7][posP2] = 1;
		matrix[7][posP2-1] = 1;

		maxDraw();

	/*         curMillis = millis(); */
	/* } */
        /*  */
	/* begMillis = curMillis; */
        /*  */
	/* blink(); */

	if(posYBall == 0 || posYBall == 7) 
	{		
		if((posP1 == posXBall || posP1 + 1 == posXBall) || (posP2 == posXBall || posP2 + 1 == posXBall))
		{
			ballUD *= -1;
			if(posXBall == 0 || posXBall == 7)
				ballRL *= -1;

			posYBall += ballUD;			
			posXBall += ballRL;
		}
		else
		{
			blinkBlink();

			if(posYBall == 0) zekoS++;	
			else grgaS++;


			posYBall = 3;
			posXBall = 1;
			ballUD *= -1;
			ballRL *= -1;

			matrixAll(0);
			matrix[posYBall][posXBall] = 1;
			matrix[0][posP1] = 1;
			matrix[0][posP1+1] = 1;
			matrix[7][posP2] = 1;
			matrix[7][posP2-1] = 1;

			maxDraw();

			delay(250);
		}
	}
	/* else if(posYBall == 1 || posYBall == 6) */
	/* { */
	/*         if((posP1 - 1 <= posXBall && posP1 + 3 >= posXBall) || 	(posP2 - 1 <= posXBall && posP2 + 3 >= posXBall)) */
	/*         { */
	/*          */
	/*                 ballUD *= -1; */
	/*                 if(posXBall == 0 || posXBall == 7) */
	/*                         ballRL *= -1; */
        /*  */
	/*                 posYBall += ballUD;			 */
	/*                 posXBall += ballRL; */
	/*         } */
	/*         else */
	/*         { */
	/*                 blinkBlink(); */
        /*  */
	/*                 if(posYBall == 1) zekoS++;	 */
	/*                 else grgaS++; */
        /*  */
        /*  */
	/*                 posYBall = 4; */
	/*                 posXBall = 3; */
	/*                 ballUD *= -1; */
        /*  */
	/*                 matrixAll(0); */
	/*                 matrix[posYBall][posXBall] = 1; */
	/*                 matrix[0][posP1] = 1; */
	/*                 matrix[0][posP1+1] = 1; */
	/*                 matrix[7][posP2] = 1; */
	/*                 matrix[7][posP2+1] = 1; */
        /*  */
	/*                 maxDraw(); */
        /*  */
	/*                 delay(250); */
	/*                 } */
	/* } */
	else
	{
		posYBall += ballUD;			
		if(posXBall == 0 || posXBall == 7)
			ballRL *= -1;
		posXBall += ballRL;
	}

	matrixAll(0);
	matrix[posYBall][posXBall] = 1;
	matrix[0][posP1] = 1;
	matrix[0][posP1+1] = 1;
	matrix[7][posP2] = 1;
	matrix[7][posP2-1] = 1;

	maxDraw();

	Serial.print(zekoS);
	Serial.print(" : ");
	Serial.println(grgaS);

	delay(100);
}

void blink()
{
	/* digitalWrite(led, HIGH); */
	/* delay(100); */
	/* digitalWrite(led, LOW); */
	/* delay(100); */
}
