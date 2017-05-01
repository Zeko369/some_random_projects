int button = 7;
int potentiomenet = A0;

int lamp = 6;

bool on;
int brightness = 255;

void setup()
{
	pinMode(button, INPUT_PULLUP);
	pinMode(potentiomenet, INPUT);

	pinMode(lamp, OUTPUT);

	for(int i = 0; i<brightness; i++)
	{
		analogWrite(lamp, i);
		delay(4);	
	}
}

void loop()
{
	if(digitalRead(button) == 0)
	{
		on = !on;	

		if(on == 0)
			analogWrite(lamp, 0);
		else
			fade(brightness);

		while(digitalRead(button) == 0) {}
	}

	if(on == 1)
	{
		analogWrite(lamp, map(analogRead(potentiomenet), 0, 1023, 0, 255));	
	}

	delay(50);	
}

void fade(int a)
{
	for(int i = 0; i<a; i++)
	{
		analogWrite(lamp, i);
		delay(2);	
	}
	analogWrite(lamp, 255);
}
