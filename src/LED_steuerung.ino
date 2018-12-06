// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// 64 voreingestellte Farbwerte der LED
const byte RGBvalues[SIZE_COLOR][3]=
{
  {255,  0,255}, // 0 mangenta
  {224,  0,255},
  {192,  0,255},
  {160,  0,255},
  {128,  0,255},
  { 96,  0,255},
  { 64,  0,255},
  { 32,  0,255},
  {  0,  0,255}, // 8 blau
  {  0, 32,255},
  {  0, 64,255},
  {  0, 96,255},
  {  0,128,255},
  {  0,160,255},
  {  0,192,255},
  {  0,224,255},
  {  0,255,255}, // 16 cyan
  {  0,255,224},
  {  0,255,192},
  {  0,255,160},
  {  0,255,128},
  {  0,255, 96},
  {  0,255, 64},
  {  0,255, 32},
  {  0,255,  0}, // 24 gruen
  { 32,255,  0},
  { 64,255,  0},
  { 96,255,  0},
  {128,255,  0},
  {160,255,  0},
  {192,255,  0},
  {224,255,  0},
  {255,255,  0}, // 32 gelb
  {255,224,  0},
  {255,192,  0},
  {255,160,  0},
  {255,128,  0},
  {255, 96,  0},
  {255, 64,  0},
  {255, 32,  0},
  {255,  0,  0}, // 40 rot
  {255,  0, 32},
  {255,  0, 64},
  {255,  0, 96},
  {255,  0,128},
  {255,  0,160},
  {255,  0,192},
  {255,  0,224},
  {255, 96,255}, // 48 mangenta hell
  {255,128,255},
  {255,160,255},
  {255,192,255},
  {255,224,255},
  {224,255,255}, // 53 cyan hell
  {192,255,255},
  {160,255,255},
  {128,255,255},
  { 96,255,255},
  {255,255, 96}, // 58 gelb hell
  {255,255,128},
  {255,255,160},
  {255,255,192},
  {255,255,224},
  {255,255,255}  // 63 weiss
};

// 64 voreingestellte Helligkeitswerte der LED
// diese sind auf Basis einer quadratischen Gleichung gerechnet,
// da das Helligkeitsverhalten der LED nicht linear ist
const int brightnessValues[64]=  // = logarithmische Werte
{
    0,   2,   3,   4,   5,   6,   7,   8,
    9,  10,  11,  12,  13,  14,  15,  16, 
   18,  20,  22,  24,  26,  28,  31,  34, 
   37,  40,  44,  47,  51,  54,  58,  62, 
   66,  70,  75,  79,  84,  88,  93,  98, 
  103, 108, 114, 119, 125, 131, 136, 142, 
  149, 155, 161, 168, 174, 181, 188, 195, 
  202, 210, 217, 225, 232, 240, 248, 256
};

// Zuweisung der seriell angeordneten LED zu X/Y-Koordinaten
const int LED_nr[SIZE_X][SIZE_Y]=
{
  { 14, 15, 36, 37, 58, 59, 80, 81,102,103,124},
  { 13, 16, 35, 38, 57, 60, 79, 82,101,104,123},
  { 12, 17, 34, 39, 56, 61, 78, 83,100,105,122},
  { 11, 18, 33, 40, 55, 62, 77, 84, 99,106,121},
  { 10, 19, 32, 41, 54, 63, 76, 85, 98,107,120},
  {  9, 20, 31, 42, 53, 64, 75, 86, 97,108,119},
  {  8, 21, 30, 43, 52, 65, 74, 87, 96,109,118},
  {  7, 22, 29, 44, 51, 66, 73, 88, 95,110,117},
  {  6, 23, 28, 45, 50, 67, 72, 89, 94,111,116},
  {  5, 24, 27, 46, 49, 68, 71, 90, 93,112,115},
  {  4, 25, 26, 47, 48, 69, 70, 91, 92,113,114}
};

// Initialisierung der LED Ansteuerung. Wird beim Start nur einmal aufgerufen
void LED_steuerung_setup() 
{
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
}

// Alle LED im Speicher loeschen
void LED_clear()
{
  // Clear all LEDs
  int cnt;

  for(cnt = 0; cnt < NUMPIXELS; cnt++)
  {
    pixels.setPixelColor(cnt, pixels.Color(0,0,0));
  }
}

// Schaltet die LED an der Koordinate x, y mit der gewuenschten Farbe und Helligkeit ein
void LED_set(int x, int y, byte colorID, byte brightness)
{
  if (colorID >= SIZE_COLOR)
  {
    colorID = SIZE_COLOR-1;
  }
  
  if (brightness >= SIZE_BRIGHTNESS)
  {
    brightness = SIZE_BRIGHTNESS-1;
  }

  if (x >= SIZE_X)
  {
    x = SIZE_X-1;
  }

  if (y >= SIZE_Y)
  {
    y = SIZE_Y-1;
  }
  pixels.setPixelColor(LED_nr[x][y], pixels.Color(RGBvalues[colorID][0]*brightnessValues[brightness]>>8,RGBvalues[colorID][1]*brightnessValues[brightness]>>8,RGBvalues[colorID][2]*brightnessValues[brightness]>>8));
}

// Schaltet die LED fuer die entsprechenden Minuten ein
void LED_minutes_set(int x, byte colorID, byte brightness)
{
  if (colorID >= SIZE_COLOR)
  {
    colorID = SIZE_COLOR-1;
  }
  
  if (brightness >= SIZE_BRIGHTNESS)
  {
    brightness = SIZE_BRIGHTNESS-1;
  }

  if (x >= SIZE_MINUTES)
  {
    x = SIZE_MINUTES-1;
  }
  pixels.setPixelColor(x, pixels.Color(RGBvalues[colorID][0]*brightnessValues[brightness]>>8,RGBvalues[colorID][1]*brightnessValues[brightness]>>8,RGBvalues[colorID][2]*brightnessValues[brightness]>>8));
}

// Schreibt das Wort "ES"
void LED_es(byte colorID, byte brightness)
{
  LED_set (0,10,colorID,brightness);
  LED_set (1,10,colorID,brightness);
}

// Schreibt das Wort "ESCH"
void LED_esch(byte colorID, byte brightness)
{
  LED_set (3,10,colorID,brightness);
  LED_set (4,10,colorID,brightness);
  LED_set (5,10,colorID,brightness);
  LED_set (6,10,colorID,brightness);
} 

// Schreibt das Wort "FUEF"
void LED_5(byte colorID, byte brightness)
{
  LED_set (8,10,colorID,brightness);
  LED_set (9,10,colorID,brightness);
  LED_set (10,10,colorID,brightness);
}

// Schreibt das Wort "ZAEH"
void LED_10(byte colorID, byte brightness)
{
  LED_set (8,9,colorID,brightness);
  LED_set (9,9,colorID,brightness);
  LED_set (10,9,colorID,brightness);
}

// Schreibt das Wort "VIERTU"
void LED_15(byte colorID, byte brightness)
{
  LED_set (0,9,colorID,brightness);
  LED_set (1,9,colorID,brightness);
  LED_set (2,9,colorID,brightness);
  LED_set (3,9,colorID,brightness);
  LED_set (4,9,colorID,brightness);
  LED_set (5,9,colorID,brightness);
}

// Schreibt das Wort "ZWAENZG"
void LED_20(byte colorID, byte brightness)
{
  LED_set (0,8,colorID,brightness);
  LED_set (1,8,colorID,brightness);
  LED_set (2,8,colorID,brightness);
  LED_set (3,8,colorID,brightness);
  LED_set (4,8,colorID,brightness);
  LED_set (5,8,colorID,brightness);
}

// Schreibt das Wort "AB"
void LED_ab(byte colorID, byte brightness)
{
  LED_set (0,7,colorID,brightness);
  LED_set (1,7,colorID,brightness);
}

// Schreibt das Wort "VOR"
void LED_vor(byte colorID, byte brightness)
{
  LED_set (8,8,colorID,brightness);
  LED_set (9,8,colorID,brightness);
  LED_set (10,8,colorID,brightness);
}

// Schreibt das Wort "HAUBI"
void LED_haubi(byte colorID, byte brightness)
{
  LED_set (3,7,colorID,brightness);
  LED_set (4,7,colorID,brightness);
  LED_set (5,7,colorID,brightness);
  LED_set (6,7,colorID,brightness);
  LED_set (7,7,colorID,brightness);
}

// Schreibt das Wort "AM" (morgen)
void LED_AM(byte colorID, byte brightness)
{
  LED_set (2,0,colorID,brightness);
  LED_set (3,0,colorID,brightness);
}

// Schreibt das Wort "PM" (abend)
void LED_PM(byte colorID, byte brightness)
{
  LED_set (4,0,colorID,brightness);
  LED_set (5,0,colorID,brightness);
} 

// Schreibt das Wort "ZWOEUFI"
void stunde_0(byte colorID, byte brightness) // 12 ,24 stunden
{
  LED_set (0,1,colorID,brightness);
  LED_set (1,1,colorID,brightness);
  LED_set (2,1,colorID,brightness);
  LED_set (3,1,colorID,brightness);
  LED_set (4,1,colorID,brightness);
  LED_set (5,1,colorID,brightness);
}

// Schreibt das Wort "EIS"
void stunde_1(byte colorID, byte brightness)
{
  LED_set (0,6,colorID,brightness);
  LED_set (1,6,colorID,brightness);
  LED_set (2,6,colorID,brightness);
}

// Schreibt das Wort "ZWOEI"
void stunde_2(byte colorID, byte brightness)
{
  LED_set (3,6,colorID,brightness);
  LED_set (4,6,colorID,brightness);
  LED_set (5,6,colorID,brightness);
  LED_set (6,6,colorID,brightness);
}  

// Schreibt das Wort "DRUE"
void stunde_3(byte colorID, byte brightness)
{
  LED_set (8,6,colorID,brightness);
  LED_set (9,6,colorID,brightness);
  LED_set (10,6,colorID,brightness);
}

// Schreibt das Wort "VIERI"
void stunde_4(byte colorID, byte brightness)
{
  LED_set (0,5,colorID,brightness);
  LED_set (1,5,colorID,brightness);
  LED_set (2,5,colorID,brightness);
  LED_set (3,5,colorID,brightness);
  LED_set (4,5,colorID,brightness);
}

// Schreibt das Wort "FUEFI"
void stunde_5(byte colorID, byte brightness)
{
  LED_set (6,5,colorID,brightness);
  LED_set (7,5,colorID,brightness);
  LED_set (8,5,colorID,brightness);
  LED_set (9,5,colorID,brightness);
}

// Schreibt das Wort "SAECHSI"
void stunde_6(byte colorID, byte brightness)
{
  LED_set (0,4,colorID,brightness);
  LED_set (1,4,colorID,brightness);
  LED_set (2,4,colorID,brightness);
  LED_set (3,4,colorID,brightness);
  LED_set (4,4,colorID,brightness);
  LED_set (5,4,colorID,brightness);
}

// Schreibt das Wort "SEBNI"
void stunde_7(byte colorID, byte brightness)
{
  LED_set (6,4,colorID,brightness);
  LED_set (7,4,colorID,brightness);
  LED_set (8,4,colorID,brightness);
  LED_set (9,4,colorID,brightness);
  LED_set (10,4,colorID,brightness);
}

// Schreibt das Wort "ACHTI"
void stunde_8(byte colorID, byte brightness)
{
  LED_set (0,3,colorID,brightness);
  LED_set (1,3,colorID,brightness);
  LED_set (2,3,colorID,brightness);
  LED_set (3,3,colorID,brightness);
  LED_set (4,3,colorID,brightness);
}

// Schreibt das Wort "NUENI"
void stunde_9(byte colorID, byte brightness)
{
  LED_set (5,3,colorID,brightness);
  LED_set (6,3,colorID,brightness);
  LED_set (7,3,colorID,brightness);
  LED_set (8,3,colorID,brightness);
}

// Schreibt das Wort "ZAENI"
void stunde_10(byte colorID, byte brightness)
{
  LED_set (0,2,colorID,brightness);
  LED_set (1,2,colorID,brightness);
  LED_set (2,2,colorID,brightness);
  LED_set (3,2,colorID,brightness);
}

// Schreibt das Wort "OEUFI"
void stunde_11(byte colorID, byte brightness)
{
  LED_set (7,2,colorID,brightness);
  LED_set (8,2,colorID,brightness);
  LED_set (9,2,colorID,brightness);
  LED_set (10,2,colorID,brightness);
}

// Schreibt das Wort "HELLIGKEIT"
void LED_helligkeit(byte colorID, byte brightness)
{
  LED_set ( 6,10,colorID,brightness);
  LED_set ( 2, 9,colorID,brightness);
  LED_set ( 6, 8,colorID,brightness);
  LED_set ( 7, 8,colorID,brightness);
  LED_set ( 7, 7,colorID,brightness);
  LED_set ( 5, 5,colorID,brightness);
  LED_set (10, 5,colorID,brightness);
  LED_set ( 7,4,colorID,brightness);
  LED_set ( 4,3,colorID,brightness);
  LED_set ( 5,2,colorID,brightness);
}

// Schreibt das Wort "FARB"
void LED_farb(byte colorID, byte brightness)
{
  LED_set ( 8,10,colorID,brightness);
  LED_set ( 4, 7,colorID,brightness);
  LED_set ( 9, 6,colorID,brightness);
  LED_set ( 8, 4,colorID,brightness);

}

// Schreibt das Wort "HAUBZIIT"
void LED_halbtage(byte colorID, byte brightness)
{
  LED_set ( 3, 7,colorID,brightness);
  LED_set ( 4, 7,colorID,brightness);
  LED_set ( 5, 7,colorID,brightness);
  LED_set ( 6, 7,colorID,brightness);
  LED_set ( 3, 6,colorID,brightness);
  LED_set ( 4, 5,colorID,brightness);
  LED_set ( 5, 4,colorID,brightness);
  LED_set ( 3, 3,colorID,brightness);
}

// Schreibt das Wort "HELLO"
void LED_hello(byte colorID, byte brightness)
{
  LED_set ( 6, 10,colorID,brightness);
  LED_set ( 2, 9,colorID,brightness);
  LED_set ( 6, 8,colorID,brightness);
  LED_set ( 7, 8,colorID,brightness);
  LED_set ( 10, 7,colorID,brightness);
}

// Schreibt das Wort "MADE"
void LED_made(byte colorID, byte brightness)
{
  LED_set ( 7, 1,colorID,brightness);
  LED_set ( 8, 1,colorID,brightness);
  LED_set ( 9, 1,colorID,brightness);
  LED_set ( 10, 1,colorID,brightness);
}

// Schreibt das Wort "BY"
void LED_by(byte colorID, byte brightness)
{
  LED_set ( 0, 0,colorID,brightness);
  LED_set ( 1, 0,colorID,brightness);
}

// Schreibt das Wort "DAVID"
void LED_david(byte colorID, byte brightness)
{
  LED_set ( 6, 0,colorID,brightness);
  LED_set ( 7, 0,colorID,brightness);
  LED_set ( 8, 0,colorID,brightness);
  LED_set ( 9, 0,colorID,brightness);
  LED_set ( 10, 0,colorID,brightness);
}

