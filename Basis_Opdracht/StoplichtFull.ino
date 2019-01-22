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

volatile int voetButtonState = 0;
volatile int busButtonState = 0;
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
  pinMode(voetButton, INPUT);
  
  //Voeg interrupts toe
  attachInterrupt(digitalPinToInterrupt(voetButton), voetInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(busButton), busInterrupt, CHANGE);
  
  //Zet alle stoplichten op rood, en groen uit
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

void loop()
{
  //Activeer de stoplichtcycles
    if (busRequest == 1) {
   busCycle();
  }
  
  stoplichtBoven();
  delay(1000);
  
    if (busRequest == 1) {
   busCycle();
  }
  
  stoplichtRechts();
  delay(1000);
  
    if (busRequest == 1) {
   busCycle();
  }
  
  stoplichtOnder();
  delay(1000);
  
    if (busRequest == 1) {
   busCycle();
  }
  
  stoplichtLinks();
  delay(1000);
  
    if (busRequest == 1) {
   busCycle();
  }
  
    //als het variabele walkRequest 1 is, schakel dan over naar de walkCycle
   if (walkRequest == 1) {
   walkCycle();
  }
}

void stoplichtBoven() {
    //Zet alle stoplichten op rood, en zet bovenste op groen
  digitalWrite(LRedB, LOW);
  digitalWrite(LGreenB, HIGH);
  digitalWrite(LRedL, HIGH);
  digitalWrite(LGreenL, LOW);
}

void stoplichtRechts() {
    //Zet Rechter stoplicht op groen
  digitalWrite(LRedB, HIGH);
  digitalWrite(LGreenB, LOW);
  digitalWrite(LRedR, LOW);
  digitalWrite(LGreenR, HIGH);
}

void stoplichtOnder() {
    //Zet Onderste stoplicht op groen
  digitalWrite(LRedR, HIGH);
  digitalWrite(LGreenR, LOW);
  digitalWrite(LRedO, LOW);
  digitalWrite(LGreenO, HIGH);
}

void stoplichtLinks() {
    //Zet Linker stoplicht op groen
  digitalWrite(LRedO, HIGH);
  digitalWrite(LGreenO, LOW);
  digitalWrite(LRedL, LOW);
  digitalWrite(LGreenL, HIGH);
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
  digitalWrite(LRedB, HIGH);
  digitalWrite(LRedR, HIGH);
  digitalWrite(LRedL, HIGH);
  digitalWrite(LRedO, HIGH);
  digitalWrite(LGreenB, LOW);
  digitalWrite(LGreenR, LOW);
  digitalWrite(LGreenL, LOW);
  digitalWrite(LGreenO, LOW);
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
  voetButtonState = digitalRead(voetButton);
  walkRequest = 1;
}

//Interrupt voor de buslijn, kijkt of er op de knop "busButton" geklikt word
void busInterrupt() {
  busButtonState = digitalRead(busButton);
  busRequest = 1;
}
