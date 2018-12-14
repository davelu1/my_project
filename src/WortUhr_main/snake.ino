void right()
{
  int dx=1;
  int dy=0;
  xkor+=dx;
  ykor+=dy;
}
void left()
{
  int dx=-1;
  int dy=0;
  xkor+=dx;
  ykor+=dy;
}
void up()
{
  int dx=0;
  int dy=1;
  xkor+=dx;
  ykor+=dy;
}
void down()
{
  int dx=0;
  int dy=-1;
  xkor+=dx;
  ykor+=dy;
}
  
// Startet Snake
void LED_Snake(byte colorID, byte brightness)
{

  xkor=2;
  ykor=5;
  dx=1;
  dy=0;
  if (currentMillis == 0)
  {
    currentMillis = millis();
  }
  LED_set( xkor, ykor,colorID,brightness);

  xkor+=dx;
  ykor+=dy;
  if (millis() > currentMillis + 500)
  {
    LED_set( xkor, ykor,colorID,brightness);
  }
}
