int velocity = 200;
int snakeDirection = 4; // 1: right, 2: left, 3: up, 4: down

int snakeLength = 4;
int snakeArr[4][2] = {
      {2, 5},         // Kopf: x=2, y=5
      {-1, -1},
      {-1, -1},
      {-1, -1}
  };
  
/*----------Snake----------*/
bool LED_Snake(byte colorID, byte brightness)
{
/*
  Serial.print(timenow);
  Serial.print(", ");
  */

if (deltaDrehgeber == 1) 
{
   switch (snakeDirection)
   {
      case 1:
        snakeDirection = 4;
        break;
      case 2:
        snakeDirection = 3;
        break;
      case 3:
        snakeDirection = 1;
        break;
      case 4:
        snakeDirection = 2;
        break;
   }
}
else if (deltaDrehgeber == -1) 
{
   switch (snakeDirection)
   {
      case 1:
        snakeDirection = 3;
        break;
      case 2:
        snakeDirection = 4;
        break;
      case 3:
        snakeDirection = 2;
        break;
      case 4:
        snakeDirection = 1;
        break;
   }
}
  
  if(timenow==0)
  {
    snakeArr[0][0] = 2;
    snakeArr[0][1] = 5; // 2
    /*
    xkor=2;
    ykor=5;
    */ 
  }
  else if (snakeDirection == 1) //nach rechts
  {
     snakeArr[0][0] +=1; 
     if (snakeArr[0][0] == 11) 
     {
       snakeArr[0][0] = 0;
     }

     if (snakeLength > 1)
     {
        snakeArr[1][0] = snakeArr[0][0] - 1; // x
        snakeArr[1][1] = snakeArr[0][1]    ; // y
     }
     if (snakeLength > 2)  
     {
        snakeArr[2][0] = snakeArr[0][0] - 2;
        snakeArr[2][1] = snakeArr[0][1]    ;
     }
     if (snakeLength > 3)  
     {
        snakeArr[3][0] = snakeArr[0][0] - 3;
        snakeArr[3][1] = snakeArr[0][1]    ;
     }
  }
  else if (snakeDirection == 2) // nach links
  {
     snakeArr[0][0] -=1; 
     if (snakeArr[0][0] == -1) 
     {
       snakeArr[0][0] = 10;
     }
  
     if (snakeLength > 1)
     {
        snakeArr[1][0] = snakeArr[0][0] + 1; // x
        snakeArr[1][1] = snakeArr[0][1]    ; // y
     }
     if (snakeLength > 2)  
     {
        snakeArr[2][0] = snakeArr[0][0] + 2;
        snakeArr[2][1] = snakeArr[0][1]    ;
     }
     if (snakeLength > 3)  
     {
        snakeArr[3][0] = snakeArr[0][0] + 3;
        snakeArr[3][1] = snakeArr[0][1]    ;
     }
   }
   else if (snakeDirection == 3) // nach oben
   {
     snakeArr[0][1] +=1; 
     if (snakeArr[0][1] == 11) 
     {
       snakeArr[0][1] = 0;
     }
  
     if (snakeLength > 1)
     {
        snakeArr[1][0] = snakeArr[0][0]; // x
        snakeArr[1][1] = snakeArr[0][1] - 1   ; // y
     }
     if (snakeLength > 2)  
     {
        snakeArr[2][0] = snakeArr[0][0];
        snakeArr[2][1] = snakeArr[0][1] - 2    ;
     }
     if (snakeLength > 3)  
     {
        snakeArr[3][0] = snakeArr[0][0];
        snakeArr[3][1] = snakeArr[0][1] - 3   ;
     }
   }
  else if (snakeDirection == 4) // nach unten
   {
     snakeArr[0][1] -=1; 
     if (snakeArr[0][1] == -1) 
     {
       snakeArr[0][1] = 10;
     }
  
     if (snakeLength > 1)
     {
        snakeArr[1][0] = snakeArr[0][0]; // x
        snakeArr[1][1] = snakeArr[0][1] + 1   ; // y
     }
     if (snakeLength > 2)  
     {
        snakeArr[2][0] = snakeArr[0][0];
        snakeArr[2][1] = snakeArr[0][1] + 2    ;
     }
     if (snakeLength > 3)  
     {
        snakeArr[3][0] = snakeArr[0][0];
        snakeArr[3][1] = snakeArr[0][1] + 3   ;
     }
   }

    delay(velocity);
    LED_clear;

  // Körperglieder zeichnen 
 if (snakeArr[1][0] > -1) {
    LED_set(snakeArr[1][0], snakeArr[1][1],colorID,brightness);
  } 
  if (snakeArr[2][0] > -1) {
    LED_set(snakeArr[2][0], snakeArr[2][1],colorID,brightness);
  } 
  if (snakeArr[3][0] > -1) {
    LED_set(snakeArr[3][0], snakeArr[3][1],colorID,brightness);
  } 
  
  // Kopf zeichnen
  LED_set(snakeArr[0][0], snakeArr[0][1], 40, brightness);
  timenow += 1;
}

bool istGliedHinterKopfLinks()
{
  if(snakeArr[0][0] == snakeArr[1][0] && snakeArr[0][1] == snakeArr[1][1] - 1)
  {
    return true;
  }
  else 
  {
    return false;
  }
}

bool istGliedHinterKopfRechts()
{
  if(snakeArr[0][0] == snakeArr[1][0] && snakeArr[0][1] == snakeArr[1][1] + 1)
  {
    return true;
  }
  else 
  {
    return false;
  }
}

  /*
  int startdelay=500;
  if (timenow == 0||timenow>=500)
  {
    delay(200);
    timenow = millis();
  }
  if(timenow>=200)
  {
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
  */
