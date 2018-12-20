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
bool LED_Snake(byte colorID, byte brightness)
{
  xkor=2;
  ykor=5; 
  int startdelay=500;
  if (timenow == 0)
  {
    timenow = 0;
    timenow = millis();
  }

  if(millis() < timenow + startdelay)
  {
    LED_set( xkor, ykor,colorID,brightness);
  }
  if(deltaDrehgeber==1)
  {
    right();
    LED_set( xkor, ykor,colorID,brightness);
  }      
  if(deltaDrehgeber==-1)
  {
    up();
    LED_set( xkor, ykor,colorID,brightness);
  }
  if(deltaDrehgeber>=2)
  {
    down();
    LED_set( xkor, ykor,colorID,brightness);
  }

  if(deltaDrehgeber<=-2)
  {
    left();
    LED_set( xkor, ykor,colorID,brightness);
  }
}
