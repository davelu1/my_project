#include <Snake.h>
#include "FastLED.h"

#define NUM_LEDS 135
#define LEDS_PER_ROW 15
#define DATA_PIN 6

Snake snakeGame(15,9,10);//initialize the snake field with x=15, y=9, delay=10 ticks						 
CRGB leds[NUM_LEDS];

void setup() {
	snakeGame.setBodyColor(255,0,255);//optionally set the color of the snakeparts
	snakeGame.setFoodColor(0,60,125);//optionally set the color of the food
	snakeGame.setHeadColor(225,20,60);//optionally set the color of the snakeparts

	delay(2000);
	FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
	Serial.begin(9600);
}

byte setPixel(byte x, byte y, byte r, byte g, byte b)
{
	byte ledID = NUM_LEDS - (y * LEDS_PER_ROW) - x - 1 ;
	leds[ledID].setRGB(r,g,b);
	return ledID;
}

void changeRGBtoGBR()
{
		for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed++)
		{
			leds[whiteLed].setRGB(leds[whiteLed].g , leds[whiteLed].b, leds[whiteLed].r);
		}
}

void clearScreen()
{
		for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed++)
		{
			leds[whiteLed].setRGB( 3, 3, 3);
		}
}

void loop() 
{	
	Snake::pixel* snakeLimbs=snakeGame.getSnakeLimbs();//this needs to be updated every frame
	Snake::pixel* snakeFood = snakeGame.getFoodPositions();//this needs to be updated every frame
	clearScreen();
	setPixel(snakeFood[0].posX,8-snakeFood[0].posY,snakeFood[0].pixelColor.r,snakeFood[0].pixelColor.g,snakeFood[0].pixelColor.b); // display the food
	for(int i=0; i<snakeGame.getSnakeLenght(); i++)
	{
		//display the snake, my setpixel method has x=0, y=0 at the top left, but the library has it at bottom left, so I invert the Y-Axis:
		setPixel(snakeLimbs[i].posX,8-snakeLimbs[i].posY,snakeLimbs[i].pixelColor.r,snakeLimbs[i].pixelColor.g,snakeLimbs[i].pixelColor.b);
	}
	FastLED.show();
	snakeGame.tick();//main loop for the snake library
	if(snakeGame.wasGameReset())// if the snake bit itself or the wall, flash a little
	{
		for(int i=0; i<30; i++)
		{
			changeRGBtoGBR();
			FastLED.show();
			delay(40);
		}
	}
	else
		delay(30);

}

byte incomingByte=0;
void serialEvent() {
	while (Serial.available()) 
	{
		incomingByte = Serial.read();
		Serial.write(incomingByte);
	}
	switch(incomingByte)
	{
	case 'a':
		snakeGame.goLeft(); //snake will go left on the next move
		break;
	case 'd':
		snakeGame.goRight(); //snake will go right on the next move
		break;
	case 's':
		snakeGame.goDown(); //snake will go down on the next move
		break;
	case 'w':
		snakeGame.goUp(); //snake will go up on the next move
		break;
	case '1':		//cheat!
		snakeGame.increaseSize();
		break;
	case '2':		//whaaaaaa
		snakeGame.setDelay(4);//set speed (actually you set the delay time)
		break;
	}
}
