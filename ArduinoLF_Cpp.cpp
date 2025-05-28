const int IA1 = 9;  // Motor 1 forward
const int IB1 = 10; // Motor 1 backward
const int IA2 = 5;  // Motor 2 forward
const int IB2 = 6;  // Motor 2 backward


const int LS = 2;   // aristeros aisthtiras
const int MS = 4;   // mesaios
const int RS = 12;  // deksios


int lastInput = -2; //aristera = -1,mesh = 0, deksia = 1
bool stop = false;  // stop flag

void setup() {
  Serial.begin(9600);

  // aisthitires
  pinMode(LS, INPUT);
  pinMode(MS, INPUT);
  pinMode(RS, INPUT);

  //kinitires
  pinMode(IA1, OUTPUT);
  pinMode(IB1, OUTPUT);
  pinMode(IA2, OUTPUT);
  pinMode(IB2, OUTPUT);
}



void moveForward() {
  digitalWrite(IA1, HIGH);
  digitalWrite(IB1, LOW);
  digitalWrite(IA2, HIGH);
  digitalWrite(IB2, LOW);
  lastInput = 0;
}

void turnLeft() {
  digitalWrite(IA1, HIGH);
  digitalWrite(IB1, LOW);
  digitalWrite(IA2, LOW);
  digitalWrite(IB2, LOW);
  lastInput = -1;
}

void turnRight() {
  digitalWrite(IA1, LOW);
  digitalWrite(IB1, LOW);
  digitalWrite(IA2, HIGH);
  digitalWrite(IB2, LOW);
  lastInput = 1;
}

void stopMotors() {
  digitalWrite(IA1, LOW);
  digitalWrite(IB1, LOW);
  digitalWrite(IA2, LOW);
  digitalWrite(IB2, LOW);
} 

void lineSearch(int attempts = 0){ // course correction an xathei h grammh
  const int searchDelay = 10; //delay psaksimatos
  const int maxAttempts = 50; //megistos ari8mos prospatheiwn

  bool ls = digitalRead(LS); //dhlwsh aisthitirwn
  bool ms = digitalRead(MS);
  bool rs = digitalRead(RS);

  
  if(ls && ms && rs){       //elegxos teleytaiou input
     stop = true;   
  } else if (lastInput == 0) {
     moveForward();
  } else if (lastInput == 1) {
     turnRight();
  } else if (lastInput == -1) {
     turnLeft();  
  }
  
  delay(searchDelay); 
  
  if (stop) { //elegxos gia stop 
    stopMotors();
    delay(100);
    return;
  }
  
  ls = digitalRead(LS); // elegxos aistitirwn meta to search
  ms = digitalRead(MS);
  rs = digitalRead(RS);

  if (attempts > maxAttempts) { //an pairnei pollh wra na vrei th grammh, stop
    stopMotors();
    Serial.println("Line not found. Stopping.");
    return;
  } else if (ms || ls || rs) { // an vrethhke h grammh
    lastInput = -2;
    return;
  } else { 
    lineSearch(attempts + 1); //anadromh 
  }
}


void loop() {
  bool ls = digitalRead(LS); //dhlwsh aisthitirwn
  bool ms = digitalRead(MS);
  bool rs = digitalRead(RS);

  Serial.print("LS: "); Serial.print(ls);
  Serial.print(" | MS: "); Serial.print(ms);
  Serial.print(" | RS: "); Serial.println(rs);
  if (ls || ms || rs) {     //direction check
        if (ls && ms && rs) { //stop 
        stopMotors();        
        Serial.println("STOP - All sensors on line");
      } else if (ms) { //mprosta
        moveForward();
        Serial.println("Forward");
      } else if (ls) { //aristera
        turnLeft();
        Serial.println("Turn left");
      } else if (rs) { //deksia
        turnRight();
        Serial.println("Turn right");
      } else {         //psaksimo grammhs
        lineSearch(0); 
      } 
  }
  
  delay(10); // delay gia megaliteri statherotita
}