    // *** Externe Bibliotheken einlesen ***
#include <Adafruit_NeoPixel.h>  // Library für serielle LED Ansteuerung
#include <EEPROM.h>             // Library für permanenten Speicher (Farbe, Helligkeit, AM/PM)
#include <Wire.h>               // Library für serielle Schnittstelle zu Echtzeituhr (RTC)
#include <RTClib.h>            // Library zum Speichern/Auslesen der Uhrdaten

#ifdef __AVR__
  #include <avr/power.h>        // Library Arduino AVR
#endif


// *** Einstellungen NeoPixel Library (Ansteuerung LED) ***
#define NUMPIXELS           125 // Anzahl angeschlossener LED (11 x 11) + 4
#define PIN                 6   // Verwendeter Arduino Pin für LED (NeoPixels)
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


// Benoetigte Konstanten definieren
#define SIZE_X              11  // Anzeigegroesse X-Richtung
#define SIZE_Y              11  // Anzeigegroesse Y-Richtung
#define SIZE_MINUTES        4   // Groesse Minutenanzeige (0 - 4)
#define SIZE_COLOR          64  // Anzahl moeglicher Farben
#define SIZE_BRIGHTNESS     64  // Anzahl moeglicher Helligkeitswerte

// Benoetigte Variablen deklarieren
int                         colorID   = 16;
int                         brightness = 10;
int                         deltaDrehgeber = 0;

static int                  x=0;
static int                  y=0;
static byte                 part=0;

static byte                 sm_Button = 0;      // Zustand der Statemachine. Wechselt mit jedem Knopfdruck

static int                  minuten = 0;        // Minuten 0 bis 59
int                         minuten5;           // Minuten, auf 5 Minuten abgerundet
int                         minuten_einzel;     // Minuten 0 bis 4

static int                  stunden = 0;        // Stunden 0 bis 23
int                         stunden_angezeigt;  // Aufgerundete Stunden, je nach Minuten (z.B. 13:45 = VIERTU VOR ZWOEI)

static bool                 halbtage_anzeigen = false;  // Halbtage anzeigen? (AM/PM)
byte                        halbtag = 0;        // Morgen = 0 (AM), Nachmittag = 1 (PM)

unsigned long               act_time = 0;
static unsigned long        intro_time = 0;
static unsigned long        inaktiv_time = 0;
static bool                 uhrzeit_verstellt = false;

typedef enum EEProm_store_t
{
    COLOR,
    HELLIGKEIT,
    AMPM,
    OffWhite,
    Supreme
} EEProm_store;

typedef enum FARBEN_t
{
   MANGENTA = 0,
   BLAU     = 8,
   CYAN     = 16,
   GRUEN    = 24,
   GELB     = 32,
   ROT      = 40,
   WEISS    = 63,
} FARBEN;

RTC_DS1307 rtc;

void setup() // Initialisierung, wird am Anfang nur einmal durchlaufen:
{
  Serial.begin (9600);
  Drehgeber_setup();
  LED_steuerung_setup();
  LED_clear();
  colorID = EEPROM.read(COLOR);
  brightness = EEPROM.read(HELLIGKEIT);
  halbtage_anzeigen = (byte)(EEPROM.read(AMPM));
  initRTC();
}

void loop()  // Endlosschleife:
{
  // Aktuelle Uhrzeit bestimmen (stunden, minuten)
  act_time = millis();

  if (!uhrzeit_verstellt) // Uhrzeit wurde NICHT verstellt
  {
    getRTC(&stunden, &minuten);
  }

  if(Drehgeber_knopf_gedrueckt()) // Wurde Knopf gedrueckt?
  {
    sm_Button++;
    if(sm_Button>11)
    {
      sm_Button = 1;
    }
  }
  deltaDrehgeber = Drehgeber_delta_lesen(); // Differenz Drehgeber lesen

  // Beschleunigung bei schnellem Drehen
  if (deltaDrehgeber > 0)
  {
    deltaDrehgeber = (5 * deltaDrehgeber) - 4;  //  1, 6, 11, 16, ...
  }
  
   if (deltaDrehgeber < 0)
  {
    deltaDrehgeber = (5 * deltaDrehgeber) + 4;  //  -1, -6, -11, -16, ...
  }

  // Test Led auf print
  digitalWrite(LED_BUILTIN, HIGH);   // LED einschalten
  delay(20);                         // 20 millisekunden warten
  digitalWrite(LED_BUILTIN, LOW);    // LED ausschalten
  delay(20);                         // 20 millisekunden warten

 // Automatisches Verlassen des Bearbeitungsmodus nach 10 Sekunden
  if ( (act_time - inaktiv_time) > 10000) // Sind bereits 10 Sekunden seit letztem Zurücksetzen vergangen?
  {
    sm_Button = 1; // Dann gehe zu case 1: Uhrzeit anzeigen
  }
    
  switch(sm_Button)
  {
    case 0:
      intro();
      inaktiv_time = act_time; // Bearbeitungsmodus timeout zurücksetzen
      break;
      
    case 1:
      uhrzeit_anzeigen();
      inaktiv_time = act_time; // Bearbeitungsmodus timeout zurücksetzen
      break;
      
    case 2:
      uhrzeit_einstellen();
      if (deltaDrehgeber != 0)
      {
        inaktiv_time = act_time; // Bearbeitungsmodus timeout zurücksetzen wenn Knopf gedreht
      }
      break;
      
    case 3:
      if (uhrzeit_verstellt) 
      {
        uhrzeit_speichern();
      }
      setRTC(stunden, minuten);
      inaktiv_time = act_time; // Bearbeitungsmodus timeout zurücksetzen
      sm_Button++; // sofort zum naechsten Schritt weiter
      break;
      
    case 4: // Helligkeit
      helligkeit_einstellen();
      
      if (deltaDrehgeber != 0)
      {
        inaktiv_time = act_time; // Bearbeitungsmodus timeout zurücksetzen wenn Knopf gedreht
      }
      break;
      
    case 5: // Helligkeit speichern
      EEPROM.update(HELLIGKEIT, brightness);
      inaktiv_time = act_time;
      sm_Button++; // sofort zum naechsten Schritt weiter
      break;
      
    case 6: // Farbe
      farbe_einstellen();
      if (deltaDrehgeber != 0)
      {
        inaktiv_time = act_time; // Bearbeitungsmodus timeout zurücksetzen wenn Knopf gedreht
      }
      break;

    case 7: // Farbe speichern
      EEPROM.update(COLOR, colorID);
      inaktiv_time = act_time; // Bearbeitungsmodus timeout zurücksetzen
      sm_Button++; // sofort zum naechsten Schritt weiter
      break;
      
    case 8: // AM/PM
      ampm_einstellen();
      if (deltaDrehgeber != 0)
      {
        inaktiv_time = act_time; // Bearbeitungsmodus timeout zurücksetzen wenn Knopf gedreht
      }
      break;

    case 9: // AM/PM speichern
      inaktiv_time = act_time; // Bearbeitungsmodus timeout zurücksetzen
      sm_Button++; // sofort zum naechsten Schritt weiter
      break;
      





     case 10: //Off White Kreuz
      OffWhite_einstellen();
      if (deltaDrehgeber != 0)
      {
        inaktiv_time = act_time; // Bearbeitungsmodus timeout zurücksetzen wenn Knopf gedreht
      }
      break;
      
     case 11: // Off White speichern
      inaktiv_time = act_time; // Bearbeitungsmodus timeout zurücksetzen
      sm_Button++; // sofort zum naechsten Schritt weiter
      break;


     case 12: //Supreme
      Supreme_einstellen();
      if (deltaDrehgeber != 0)
      {
        inaktiv_time = act_time; // Bearbeitungsmodus timeout zurücksetzen wenn Knopf gedreht
      }
      break;
      
     case 13: // Supreme speichern
      inaktiv_time = act_time; // Bearbeitungsmodus timeout zurücksetzen
      sm_Button++; // sofort zum naechsten Schritt weiter
      break;




      
    case 14: // Reset Fancy Demo
      LED_clear();
      x=0;
      y=0;
      part=0;
      sm_Button++; // sofort zum naechsten Schritt weiter
      break;

    case 15: // Fancy Demo
      fancy_demo();
      inaktiv_time = act_time; // Bearbeitungsmodus timeout zurücksetzen
      break;

    default:
      sm_Button = 0;
      break;
  }
  pixels.show(); // Started das Update saemtlicher LED.
}
