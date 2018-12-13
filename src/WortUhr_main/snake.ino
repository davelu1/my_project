// Schreibt das Wort "Snake"
void LED_Snake(byte colorID, byte brightness)
{
int xkor=2;
int ykor=5;
int dx=1;
int dy=0;
unsigned long currentMillis = millis();
const long interval = 5000;
unsigned long previousMillis = 0;
  if ( (sm_Button) >12)
  {
    unsigned long previousMillis= 0;
  }
LED_set( xkor, ykor,colorID,brightness);
xkor=dx+xkor;
ykor=dy+ykor;
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;     
    LED_set( xkor, ykor,colorID,brightness);
  }
}
