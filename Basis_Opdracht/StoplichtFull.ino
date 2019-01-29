int LRedB = 13;
int LGreenB = 12;
int LRedR = 11;
int LGreenR = 10;
int LRedL = 9;
int LGreenL = 8;
int LRedO = 7;
int LGreenO = 6;

int LRedVoet = 5;
int LGreenVoet = 4;
int voetButton = 3;
int busButton = 2;

int walkRequest = 0;
int busRequest = 0;


void setup()
{
  pinMode(LRedB, OUTPUT);
  pinMode(LGreenB, OUTPUT);
  pinMode(LRedR, OUTPUT);
  pinMode(LGreenR, OUTPUT);
  pinMode(LRedL, OUTPUT);
  pinMode(LGreenL, OUTPUT);
  pinMode(LRedO, OUTPUT);
  pinMode(LGreenO, OUTPUT);
  pinMode(LRedVoet, OUTPUT);
  pinMode(LGreenVoet, OUTPUT);
  
  //Voeg interrupts toe, deze schakel ik direct aan de pins, zodat de interrupt pas activeert als de knop word ingedrukt, hierdoor hoeft dus geen digitalRead commando gebruikt te worden.
  attachInterrupt(digitalPinToInterrupt(voetButton), voetInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(busButton), busInterrupt, CHANGE);
  
  //Zet alle rode LEDS aan, en groene LEDS uit (gebruik hiervoor de function 'resetStoplichten')
  resetStoplichten();
}


//De loop bezit alle stoplicht cycles, elk cycle bestaat uit een if-else commando. Deze checkt of de buslijn knop ingedrukt is.
//Als de buslijn knop ingedrukt is, word er overgeschakeld naar de busCycle, als dit niet zo is dan gaat de loop door.
void loop()
{
  //Bovenste stoplicht cycle
    if (busRequest == 1) {
   busCycle();
  }
  resetStoplichten();
  delay(1000);
  digitalWrite(LRedB, LOW);
  digitalWrite(LGreenB, HIGH);
  delay(2000);


  //Rechter stoplicht cycle
    if (busRequest == 1) {
   busCycle();
  }
  resetStoplichten();
  delay(1000);
  digitalWrite(LRedR, LOW);
  digitalWrite(LGreenR, HIGH);
  delay(2000);


  //Onder stoplicht cycle
    if (busRequest == 1) {
   busCycle();
  }
  resetStoplichten();
  delay(1000);
  digitalWrite(LRedO, LOW);
  digitalWrite(LGreenO, HIGH);
  delay(2000);


  //Linker stoplicht cycle
    if (busRequest == 1) {
   busCycle();
  }
  resetStoplichten();
  delay(1000);
  digitalWrite(LRedL, LOW);
  digitalWrite(LGreenL, HIGH);
  delay(2000);

  
    //als het variabele walkRequest 1 is, schakel dan over naar de walkCycle, als het niet 1 is, ga dan door met de loop
   if (walkRequest == 1) {
   walkCycle();
  }
}

//Deze function zorgt ervoor dat alle stoplichten ge-reset worden, 
//hiervoor gebruiken wij een function zodat we deze code kunnen hergebruiken.
void resetStoplichten() {
  digitalWrite(LRedB, HIGH);
  digitalWrite(LRedR, HIGH);
  digitalWrite(LRedL, HIGH);
  digitalWrite(LRedO, HIGH);
  digitalWrite(LGreenB, LOW);
  digitalWrite(LGreenR, LOW);
  digitalWrite(LGreenL, LOW);
  digitalWrite(LGreenO, LOW);
  
  digitalWrite(LRedVoet, HIGH);
  digitalWrite(LGreenVoet, LOW);
}



//WalkCycle is het voetgangersstoplicht die aan en uit gaat met delays er tussen.
void walkCycle() {
    digitalWrite(LRedL, HIGH);
    digitalWrite(LGreenL, LOW);
    delay(1000);
    digitalWrite(LGreenVoet, HIGH);
    digitalWrite(LRedVoet, LOW);
    delay(5000);
    digitalWrite(LGreenVoet, LOW);
    digitalWrite(LRedVoet, HIGH);
    delay(1000);
    walkRequest = 0;
}

//busCycle is het stoplicht voor de bus, het onderste stoplicht wordt hiervoor gebruikt
void busCycle() {
    resetStoplichten();
    delay(1000);
    digitalWrite(LRedO, LOW);
    digitalWrite(LGreenO, HIGH);
    delay(5000);
    digitalWrite(LRedO, HIGH);
    digitalWrite(LGreenO, LOW);
    delay(1000);
    busRequest = 0;
}




//Interrupt voor voetgangers, kijkt of er op de knop "voetButton" geklikt word
void voetInterrupt() {
  walkRequest = 1;
}

//Interrupt voor de buslijn, kijkt of er op de knop "busButton" geklikt word
void busInterrupt() {
  busRequest = 1;
}
