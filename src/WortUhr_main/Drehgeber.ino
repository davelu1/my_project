/*
  Rotary Encoder

  Reads a rotary encoder with interrupts.

  DFRobot 360 degree rotary encoder module is designed based on EC11 rotary encoder button.
  This module has three signal terminals: terminal A & B is encoder output; terminal C is 
  button signal output. It is very suitable for applications such as volume knob, lighting 
  adjustment. The rotary encoder module comes with XH2.54 bonding pad, easy to be used in 
  prototyping projects, like automotive electronics, multimedia speakers, instrumentation, 
  smart home and other fields.
  
  Specification
    Operating Voltage: 3.3V ~ 5V
    Full Rotation Angle: 360 degrees (no stop point)
    Number of pulse: 15
    Rotation Life: 30000 ± 200 Cycles
    Contact Resistance: ≤ 100mΩ
    Insulation Resistance: 100MΩ or more
    Oscillation: <10ms Press
    Working Temperature: -30 ℃ ~ +80 ℃
    Module Size: 33.8 * 22.4 (mm) /1.3 * 1.1 (inches)
    Weight: 14g
    
  https://www.dfrobot.com/wiki/index.php/EC11_Rotary_Encoder_Module_SKU:_SEN0235
*/

int encoderPinA = 2;
int encoderPinB = 3;
int buttonPin = 4;

volatile unsigned long lastEncoded = 0;
volatile unsigned long encoderValue = 0;

volatile boolean lastButtonPressed = false;
volatile boolean buttonPressed = true;

byte oldDrehgeber = 0;

int lastMSB = 0;
int lastLSB = 0;

// Gibt den absoluten Wert des Drehgebers zurueck
// Ueberlaueft bei Werten groesser 255 und startet wieder bei 0 (und umgekehrt)
byte Drehgeber_lesen(void)
{
    return (byte)(encoderValue/4 & 0xFF);
}

// Gibt bei jedem Aufruf die Aenderung des Drehknopfs zum letzten Zustand zurueck (positiv und negativ)
int Drehgeber_delta_lesen(void)
{
  byte        actDrehgeber = 0;
  byte        deltaDrehgeber = 0;
  int         retval = 0;
  static byte oldDrehgeber = 0;

  actDrehgeber = Drehgeber_lesen();
  deltaDrehgeber = actDrehgeber - oldDrehgeber;
  
  if(deltaDrehgeber<128)
  {
    retval = (int)deltaDrehgeber;
  }
  else
  {
    retval = ((int)deltaDrehgeber)-((int)256);
  }
  oldDrehgeber = actDrehgeber;
  return retval;
}

// Funktion, gibt true zurueck, wenn der Knopf gedrueckt wurde
boolean Drehgeber_knopf_gedrueckt(void)
{
  boolean retVal = false;
  
  if(!digitalRead(buttonPin))
  {
    buttonPressed = true;
  }
  else
  {
    buttonPressed = false;
  }
  
  if((buttonPressed == true) && (lastButtonPressed == false))
  {
    retVal = true;
  }
  lastButtonPressed = buttonPressed;
  
  return retVal;
}

// Setup des Drehgebers. Muss beim Starten einmal aufgerufen werden
void Drehgeber_setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(encoderPinA, INPUT); 
  pinMode(encoderPinB, INPUT);
  pinMode(buttonPin, INPUT);

  digitalWrite(encoderPinA, HIGH); //turn pullup resistor on
  digitalWrite(encoderPinB, HIGH); //turn pullup resistor on
  digitalWrite(buttonPin, HIGH);   //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);
}

// Interruptroutine. Startet bei jeder Aenderung des Drehknopfs automatisch
void updateEncoder()
{
  int MSB = digitalRead(encoderPinA); //MSB = most significant bit
  int LSB = digitalRead(encoderPinB); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}
