// Initialisieren des RTC. Wird beim Start einmal ausgefuehrt
void initRTC(void)
{
  if (! rtc.begin())
  {
    Serial.println("Couldn't find RTC");
  }

  if (! rtc.isrunning())
  {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

// Uhrzeit aus gepuffertem Speicher laden
void getRTC(int * const RTCstunden, int * const RTCminuten)
{
  DateTime Uhrzeit;
  
  Uhrzeit       = rtc.now();             // Von Echtzeituhr lesen
  (*RTCminuten) = (int)Uhrzeit.minute(); // Minuten auslesen
  (*RTCstunden) = (int)Uhrzeit.hour();   // Stunden auslesen
}

// Uhrzeit in gepufferten Speicher speichern
void setRTC(int const RTCstunden, int const RTCminuten)
{
  DateTime Uhrzeit;
  
  Uhrzeit = DateTime(2002, 9, 15, (uint8_t)RTCstunden, (uint8_t)RTCminuten, 0); // Jahr, Monate, Tage, Stuunden, Minuten, Sekunden
  rtc.adjust(Uhrzeit); // Auf Echtzeituhr speichern
}

