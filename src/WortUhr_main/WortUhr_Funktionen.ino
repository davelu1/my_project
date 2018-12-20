// Intro "MADE BY DAVID"
void intro()
{
  static int farbID=0;
  
  LED_clear();
  LED_hello(farbID, 30);
  LED_made(CYAN, 30);
  LED_by(CYAN, 30);
  LED_david(CYAN, 30);

  farbID++;
  if (farbID >= 47) // durch alle Farben bis 46 durchlaufen, dann wieder von vorne
  {
    farbID = 0;
  }

  if( (act_time - intro_time) > 5000)
  {
    sm_Button++; // intro nach 5s verlassen
  }
}

// Uhrzeit anhand der Variablen minuten und stunden anzeigen
void uhrzeit_anzeigen(void)
{
  LED_clear(); // Zuerst alles loeschen

  minuten5 = (minuten / 5) * 5; // Minuten auf 5 Minuten genau (0, 5, 10, ...)
  minuten_einzel = minuten % 5; // Restliche Minuten (0, 1, 2, 3, 4)
  
  // LED fuer einzelne Minuten anzeigen
  switch (minuten_einzel)
  {
    case 1: // 1 LED ein
      LED_minutes_set(0, colorID, brightness);
      break;
    
    case 2: // 2 LED ein
      LED_minutes_set(0, colorID, brightness);
      LED_minutes_set(1, colorID, brightness);
      break;
    
    case 3: // 3 LED ein
      LED_minutes_set(0, colorID, brightness);
      LED_minutes_set(1, colorID, brightness);
      LED_minutes_set(2, colorID, brightness);
      break;  
    
    case 4: // 4 LED ein
      LED_minutes_set(0, colorID, brightness);
      LED_minutes_set(1, colorID, brightness);
      LED_minutes_set(2, colorID, brightness);
      LED_minutes_set(3, colorID, brightness);
      break;  
    
    default:  // in allen anderen Faellen kein LED einschalten
      break;
  }
  
  // Worte fuer aktuelle Minuten anzeigen
  switch (minuten5)
  {
    case 0:
      LED_es(colorID, brightness);
      LED_esch(colorID, brightness);
      break;
      
    case 5:
      LED_es(colorID, brightness);
      LED_esch(colorID, brightness);
      LED_5(colorID, brightness);
      LED_ab(colorID, brightness);
      break;
      
    case 10:
      LED_es(colorID, brightness);
      LED_esch(colorID, brightness);
      LED_10(colorID, brightness);
      LED_ab(colorID, brightness);
      break;
    
    case 15:
      LED_es(colorID, brightness);
      LED_esch(colorID, brightness);
      LED_15(colorID, brightness);
      LED_ab(colorID, brightness);
      break;
    
    case 20:
      LED_es(colorID, brightness);
      LED_esch(colorID, brightness);
      LED_20(colorID, brightness);
      LED_ab(colorID, brightness);
      break;
    
    case 25:
      LED_es(colorID, brightness);
      LED_esch(colorID, brightness);
      LED_5(colorID, brightness);
      LED_vor(colorID, brightness);
      LED_haubi(colorID, brightness);
      break;
    
    case 30:
      LED_es(colorID, brightness);
      LED_esch(colorID, brightness);
      LED_haubi(colorID, brightness);
      break;
    
    case 35:
      LED_es(colorID, brightness);
      LED_esch(colorID, brightness);
      LED_5(colorID, brightness);
      LED_ab(colorID, brightness);
      LED_haubi(colorID, brightness);
      break;
    
    case 40:
      LED_es(colorID, brightness);
      LED_esch(colorID, brightness);
      LED_20(colorID, brightness);
      LED_vor(colorID, brightness);
      break;
    
    case 45:
      LED_es(colorID, brightness);
      LED_esch(colorID, brightness);
      LED_15(colorID, brightness);
      LED_vor(colorID, brightness);
      break;
    
    case 50:
      LED_es(colorID, brightness);
      LED_esch(colorID, brightness);
      LED_10(colorID, brightness);
      LED_vor(colorID, brightness);
      break;
    
    case 55:
      LED_es(colorID, brightness);
      LED_esch(colorID, brightness);
      LED_5(colorID, brightness);
      LED_vor(colorID, brightness);
      break;
    
    default:
      break;
  }

  // Angezeigte Stunden rechnen
  if(minuten>=25) // wenn die Minuten groesser oder gleich 25 sind, wird auf die naechste Stunde gerechnet
    
     {
      stunden_angezeigt=stunden+1;
      if (stunden_angezeigt>23) // wenn Stunden groesser 23, wird sie wieder null
      {
        stunden_angezeigt=0;
      } 
     }
  else
     {
      stunden_angezeigt=stunden;
     }
  
  // Halbtage anzeigen (AM/PM)
  if(halbtage_anzeigen || (sm_Button == 2) ) // Halbtage anzeigen, wenn gewuenscht oder immer beim Verstellen der Uhr
  {
    if(stunden >=12)
    {
      halbtag = 1;  // PM: Nachmittag
      LED_PM(colorID, brightness);
    }
    else
    {
      halbtag = 0;  // AM: Morgen
      LED_AM(colorID, brightness);
    }
  }
  
  // Zweiten Halbtag auf den ersten umrechnen (sieht gleich aus)
  if(stunden_angezeigt >=12)
  {
    stunden_angezeigt = stunden_angezeigt - 12;
  }
  
  switch (stunden_angezeigt)
  {
    case 0:
      stunde_0(colorID, brightness);
    break;  
  
    case 1:
      stunde_1(colorID, brightness);
    break;  
  
    case 2:
      stunde_2(colorID, brightness);
    break;  
    
    case 3:
      stunde_3(colorID, brightness);
    break;  
    
    case 4:
      stunde_4(colorID, brightness);
    break; 
       
    case 5:
      stunde_5(colorID, brightness);
    break;  
  
    case 6:
      stunde_6(colorID, brightness);
    break;  
  
    case 7:
      stunde_7(colorID, brightness);
    break;  
  
    case 8:
      stunde_8(colorID, brightness);
    break;  
  
    case 9:
      stunde_9(colorID, brightness);
    break;  
  
    case 10:
      stunde_10(colorID, brightness);
    break;  
  
    case 11:
      stunde_11(colorID, brightness);
    break;

    default:
    break;
  }
}

// Funktion, um die Uhrzeit zu verstellen 
void  uhrzeit_einstellen(void)
{
  if (deltaDrehgeber != 0) // wurde Drehknopf betaetigt?
  {
    minuten = minuten - deltaDrehgeber; // Minuten in entsprechende Richtung aendern
    if (minuten < 0) // sind Minuten kleiner 0?
    {       
      minuten = minuten+60; // dann wieder bei 59 anfangen
      stunden = stunden-1;  // und Stunden um 1 erniedrigen
      if (stunden < 0)      // sind Stunden kleiner 0?
      {
        stunden = 23;       // dann auf 23 vom Vortag setzen
      }
    }
    if(minuten>=60) // sind Minuten groesser oder gleich 60
    {
      minuten = minuten-60; // dann wieder bei 0 anfangen
      stunden = stunden+1;  // und Stunden um 1 erhoehen
      if (stunden >23)      // sind Stunden groesser 23
      {
        stunden = 0;        // dann auf 0 vom Folgetag setzen
      }
    }
    uhrzeit_verstellt = true; // ja, Uhrzeit wurde verstellt
  }
  uhrzeit_anzeigen();       // Uhrzeit auch beim Verstellen immer anzeigen

  // Serial.println(stunden);  // nur zum testen
}

// Speichert die Uhrzeit im batteriegepufferten Speicher (RTC)
void uhrzeit_speichern()
{
  setRTC(stunden, minuten);  // in RTC speichern
  uhrzeit_verstellt = false; // Uhrzeit verstellt wieder zuruecksetzen
}

// Stellt die Helligkeit der LED ein
void helligkeit_einstellen(void)
{
  brightness = brightness - deltaDrehgeber;
  if (brightness >= SIZE_BRIGHTNESS) // wenn maximale Helligkeit erreicht wurde, dort bleiben
  {
    brightness = SIZE_BRIGHTNESS-1; 
  }
  if (brightness < 1) // wenn minimale Helligkeit erreicht wurde, dort bleiben
  {
    brightness = 1; 
  }
  LED_clear();
  LED_helligkeit(colorID, brightness);
}


void Snake_einstellen(void)
{
  snakeID = snakeID + deltaDrehgeber;
  LED_clear;
  LED_Snake(colorID, brightness);
}

// Stellt die Farbe der LED ein
void farbe_einstellen(void)
{
  colorID = colorID + deltaDrehgeber;
  if (colorID >= SIZE_COLOR) // wenn hoechste Farbe erreicht wurde, wieder bei 0 anfangen
  {
    colorID = colorID - SIZE_COLOR; 
  }
  if (colorID < 0) // wenn kleinste Farbe erreicht wurde, wieder bei der hoechsten anfangen
  {
    colorID = colorID + SIZE_COLOR; 
  }
  LED_clear();
  LED_farb(colorID, brightness);
}

// Anzeigen von AM/PM bestimmen
void ampm_einstellen(void)
{
  LED_clear();
  LED_halbtage(colorID, brightness);
  if (deltaDrehgeber != 0) // Wenn Drehrad bewegt wurde
  {
    halbtage_anzeigen = !halbtage_anzeigen; // dann Anzeige jeweils invertieren
  }
  if (halbtage_anzeigen)
  {
    LED_AM(colorID, brightness);
    LED_PM(colorID, brightness);
  }
}

//Off-White Kreuz anzeigen
void OffWhite_einstellen(void)
{
  LED_clear();
  LED_OffWhite(colorID, brightness);
}



// Eine kleine Demo zum Anzeigen der Farbmoeglichkeiten der LED
void fancy_demo(void)
{
  static byte farbe = 0;
 
  switch(part)
  {
    case 0:
      for(y=0;y<=x;y++)
      {
        if (((x-y)<SIZE_X) && (y<SIZE_Y))
        {
          LED_set(x-y, y, farbe, brightness);
        }
      }
      x++;
      if(x>=SIZE_X+SIZE_X)
      {
        part=1;
        farbe = farbe + 8;
      }
      break;
 
    case 1:
      for(y=0;y<=x;y++)
      {
        if (((x-y)<SIZE_X) && (y<SIZE_Y))
        {
          LED_set(x-y, y,farbe, brightness);
        }
      }
      x--;
      if(x<0)
      {
        part=2;
        farbe = farbe + 8;
        x=0;
      }
      break;
          
    case 2:
      for(y=0;y<=x;y++)
      {
        if (((x-y)<SIZE_X) && (y<SIZE_Y))
        {
          LED_set(x-y, SIZE_Y-y-1, farbe, brightness);
        }
      }
      x++;
      if(x>=SIZE_X+SIZE_X)
      {
        part=3;
        farbe = farbe + 8;
      }
      break;

    case 3:
      for(y=0;y<=x;y++)
      {
        if (((x-y)<SIZE_X) && (y<SIZE_Y))
        {
          LED_set(x-y, SIZE_Y-y-1, farbe, brightness);
        }
      }
      x--;
      if(x<0)
      {
        part=0;
        farbe = farbe + 8;
        x=0;
      }
      break;
    }
    if (farbe > 63)
    {
      farbe = 0;
    }
    else if (farbe == 48)
    {
      farbe = 63;
    }
}
