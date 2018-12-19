void right()
{
  dx=1;
  dy=0;
  xkor+=dx;
  ykor+=dy;
}
void left()
{
  dx=-1;
  dy=0;
  xkor+=dx;
  ykor+=dy;
}
void up()
{
  dx=0;
  dy=1;
  xkor+=dx;
  ykor+=dy;
}
void down()
{
  dx=0;
  dy=-1;
  xkor+=dx;
  ykor+=dy;
}
  
/*----------Snake----------*/
void LED_Snake(byte colorID, byte brightness)
{
  if(deltaDrehgeber == 0)
  {
    xkor=2;
    ykor=5;    
    if (currentMillis == 0)
    {
      currentMillis = millis();

    }

    LED_set( xkor, ykor,colorID,brightness);
    if(deltaDrehgeber==0)
    {

      if (millis() > currentMillis + 500)
      {
        LED_set( xkor, ykor,colorID,brightness);
      }
      if(deltaDrehgeber==1)
      {
        right;
        LED_set( xkor, ykor,colorID,brightness);
      }      
      if(deltaDrehgeber==-1)
      {
        left;
        LED_set( xkor, ykor,colorID,brightness);
      }
    }
  }
}
