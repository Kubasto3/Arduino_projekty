  int Pin3 = 3;
  int Pin4 = 4;
  int Pin5 = 5;
  int Pin6 = 6;

  int Pin7 = 7;
  int Pin8 = 8;
  int Pin9 = 9;
  int Pin10 = 10;

  int rightAnswers[5];
  int playerAnswers[5];
  int roundNumber=0;

void setup() {
  Serial.begin(9600);

  pinMode(Pin3, OUTPUT);
  pinMode(Pin4, OUTPUT);
  pinMode(Pin5, OUTPUT);
  pinMode(Pin6, OUTPUT);
  digitalWrite(Pin7, LOW);
  digitalWrite(Pin8, LOW);
  digitalWrite(Pin9, LOW);
  digitalWrite(Pin10, LOW);
  pinMode(Pin7, INPUT_PULLUP);
  pinMode(Pin8, INPUT_PULLUP);
  pinMode(Pin9, INPUT_PULLUP);
  pinMode(Pin10, INPUT_PULLUP);
}

void blink() {
  for (int i = 0; i <= 2; i++) {
    digitalWrite(Pin3, 1);
    digitalWrite(Pin4, 1);
    digitalWrite(Pin5, 1);
    digitalWrite(Pin6, 1);
    delay(3000);
    digitalWrite(Pin3, 0);
    digitalWrite(Pin4, 0);
    digitalWrite(Pin5, 0);
    digitalWrite(Pin6, 0);
    delay(3000);
  }
}

void displayRightSeq(int roundNumber) {
  if (roundNumber <= 4) {
    for (int i = 0; i <= roundNumber; i++) {
      digitalWrite(rightAnswers[i]+2, 1);
      delay(2000);
      digitalWrite(Pin3, 0);
      digitalWrite(Pin4, 0);
      digitalWrite(Pin5, 0);
      digitalWrite(Pin6, 0);
    }
  } else {
    blink();
    while(true){
    }
  }
}

void playerChoice(int roundNumber) {
  if (digitalRead(7) == 0) {
    playerAnswers[roundNumber] = 1;
    digitalWrite(3, 1);
    delay(2000);
    digitalWrite(3, 0);
  } else if (digitalRead(8) == 0) {
    playerAnswers[roundNumber] = 2;
    digitalWrite(4, 1);
    delay(2000);
    digitalWrite(4, 0);
  } else if (digitalRead(9) == 0) {
    playerAnswers[roundNumber] = 3;
    digitalWrite(5, 1);
    delay(2000);
    digitalWrite(5, 0);
  } else if (digitalRead(10) == 0) {
    playerAnswers[roundNumber] = 4;
    digitalWrite(6, 1);
    delay(2000);
    digitalWrite(6, 0);
  }
}

void checkAnswers(int roundNumber) {
  for (int i = 0; i <= roundNumber; i++) {
    while ((digitalRead(7) == 1) && (digitalRead(8) == 1) && (digitalRead(9) == 1) && (digitalRead(10) == 1)) {
    }
    playerChoice(roundNumber);
    Serial.println("----------");
    Serial.println(roundNumber);
    Serial.println(playerAnswers[i]);
    Serial.println(rightAnswers[i]);
    if (playerAnswers[i] == rightAnswers[i]) {

    } else {
      while (true) {
        digitalWrite(Pin3, 1);
        digitalWrite(Pin4, 1);
        digitalWrite(Pin5, 1);
        digitalWrite(Pin6, 1);
      }
    }
  }
}

void generateRandomNumber(int roundNumber) {
  rightAnswers[roundNumber] = rand()%4+1;
}


void loop() {
  generateRandomNumber(roundNumber);
  delay(1000);
  displayRightSeq(roundNumber);
  delay(1000);
  checkAnswers(roundNumber);
  roundNumber = roundNumber + 1;
}

