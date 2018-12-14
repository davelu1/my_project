/*void right()
  {
    int dx=1;
    int dy=0;
  }
  void left()
  {
    int dx=-1;
    int dy=0;
  }
  void up()
  {
    int dx=0;
    int dy=1;
  }
  void down()
  {
    int dx=0;
    int dy=-1;
    xkor+=dx;
    ykor+=dy;
  }*/
  
// Startet Snake
void LED_Snake(byte colorID, byte brightness)
{
  if (currentMillis == 0)
  {
    currentMillis = millis();
  }
  LED_set( xkor, ykor,colorID,brightness);
  dx=1;
  dy=0;
  xkor=2;
  ykor=5;
  xkor+=dx;
  ykor+=dy;
  if (millis() > currentMillis + 500)
  {
    LED_set( xkor, ykor,colorID,brightness);
  }
}
