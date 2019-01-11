int velocity = 250;
int snakeDirection = 1; // 1: right, 2: left, 3: up, 4: down
int xapfel;
int yapfel;
int snakeLength = 1;
int snakeArr[4][2] = {
    {3, 5},         // Kopf: x=2, y=5
    {-1, -1},
    {-1, -1},
    {-1, -1}
};

/*----------Snake----------*/
bool LED_Snake(byte colorID, byte brightness)
{
  if (deltaDrehgeber <= -1) 
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
  else if (deltaDrehgeber >= 1) 
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
  
  //Kopf Startposition
  if(timenow <= 1)
  {
    snakeArr[0][0] = 3;
    snakeArr[0][1] = 5;
  }
  
  //Körper Startposition
  if(timenow <= 1)
  {
    snakeArr[1][0] = 3 - 1;
    snakeArr[1][1] = 5;
    snakeArr[2][0] = 3 - 2;
    snakeArr[2][1] = 5;
    snakeArr[3][0] = 3 - 3;
    snakeArr[3][1] = 5;
  }
  
// Kopf zeichnen
  LED_set(snakeArr[0][0], snakeArr[0][1], 40, brightness);
  timenow += 1;
  
// Körperglieder zeichnen
  if (snakeArr[1][0] > -1)
  {
    LED_set(snakeArr[1][0], snakeArr[1][1],colorID,brightness);
  } 
  if (snakeArr[2][0] > -1)
  {
    LED_set(snakeArr[2][0], snakeArr[2][1],colorID,brightness);
  }
  if (snakeArr[3][0] > -1)
  {
    LED_set(snakeArr[3][0], snakeArr[3][1],colorID,brightness);
  }
  delay(velocity);
  LED_clear;
//Körperelemente neu Positionieren
  snakeArr[3][0] = snakeArr[2][0];
  snakeArr[3][1] = snakeArr[2][1];
  
  snakeArr[2][0] = snakeArr[1][0];
  snakeArr[2][1] = snakeArr[1][1];

  snakeArr[1][0] = snakeArr[0][0];
  snakeArr[1][1] = snakeArr[0][1];
  
//Kopf neu positionieren
if (snakeDirection == 1) // nach rechts
{
  snakeArr[0][0] += 1; 
  if (snakeArr[0][0] == 11) 
  {
    sm_Button=16;
    snakeDirection = 1;
  }
}

else if (snakeDirection == 2) // nach links
{
  snakeArr[0][0] -=1; 
  if (snakeArr[0][0] == -1) 
  {
    sm_Button=16;
    snakeDirection = 1;
  }
}

else if (snakeDirection == 3) // nach oben
{
  snakeArr[0][1] +=1; 
  if (snakeArr[0][1] == 11) 
  {
    sm_Button=16;
    snakeDirection = 1;
  }
}

else if (snakeDirection == 4) // nach unten
{
  snakeArr[0][1] -=1; 
  if (snakeArr[0][1] == -1)
  {
  sm_Button=16;
  snakeDirection = 1;
  }
}

// Körperglieder zeichnen
    LED_set(snakeArr[1][0], snakeArr[1][1],colorID,brightness);
    LED_set(snakeArr[2][0], snakeArr[2][1],colorID,brightness);
    LED_set(snakeArr[3][0], snakeArr[3][1],colorID,brightness);

// Kopf zeichnen
  LED_set(snakeArr[0][0], snakeArr[0][1], 40, brightness);
  timenow += 1;

// Apfel erstellen + verschwinden lassen
  if(timenow <= 1 || snakeArr[0][1] == yapfel && snakeArr[0][0] == xapfel)
  {
    xapfel=random(0,10);
    yapfel=random(0,10);
  }
  LED_set(xapfel, yapfel,24,brightness);
}
