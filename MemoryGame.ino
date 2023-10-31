// Predefined number of rounds in  brackets.
//The size of arrays must be the same!
int rightAnswers[7];               //Container which includes correct answers
int playerAnswers[7];              //Container which includes players answers

int roundNumber = 0;  // iterator that counts the number of past rounds
bool flag_reset = false;

void setup() {
  if (!(sizeof(rightAnswers) == sizeof(playerAnswers))) {
    blink();
    while (true) {
      //ERROR
    }
  }

  //FIOLET - GND
  //zielony 7
  //zolty 8
  //pomaranczowy 9
  //bialy 10
  //zielony 3
  //zolty 4 
  //pomaranozowy 5
  //bialy 6
  //RESET bialy 11

  pinMode(3, OUTPUT); 
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);

  pinMode(12, INPUT_PULLUP);  //RESET
}
void reset() {
  roundNumber = 0;
}

// Blinks when all of rounds were won
void blink() {
  for (int i = 0; i <= 3; i++) {
    digitalWrite(3, 1);
    digitalWrite(4, 1);
    digitalWrite(5, 1);
    digitalWrite(6, 1);
    delay(2000);
    digitalWrite(3, 0);
    digitalWrite(4, 0);
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    delay(2000);
  }
}
// Displaying right sequeance every round
void displayRightSeq(int roundNumber) {
  if (roundNumber <= 5) {
    for (int i = 0; i <= roundNumber; i++) {
      digitalWrite(rightAnswers[i] + 2, 1);
      delay(500);
      digitalWrite(3, 0);
      digitalWrite(4, 0);
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      delay(500);
    }
  } else {
    blink();
    while (true) {
            if(digitalRead(12) == 0){
        flag_reset=true;
        return;
      }
    }
  }
}

void playerChoice(int roundNumber) {
  if (digitalRead(7) == 0) {
    playerAnswers[roundNumber] = 1;
    digitalWrite(3, 1);
    delay(500);
    digitalWrite(3, 0);
  } else if (digitalRead(8) == 0) {
    playerAnswers[roundNumber] = 2;
    digitalWrite(4, 1);
    delay(500);
    digitalWrite(4, 0);
  } else if (digitalRead(9) == 0) {
    playerAnswers[roundNumber] = 3;
    digitalWrite(5, 1);
    delay(500);
    digitalWrite(5, 0);
  } else if (digitalRead(10) == 0) {
    playerAnswers[roundNumber] = 4;
    digitalWrite(6, 1);
    delay(500);
    digitalWrite(6, 0);
  }
}

void checkAnswers(int roundNumber) {
  for (int i = 0; i <= roundNumber; i++) {
    while ((digitalRead(7) == 1) && (digitalRead(8) == 1) && (digitalRead(9) == 1) && (digitalRead(10) == 1)) {
      if (digitalRead(12) == 0) {
        flag_reset = true;
        return;
      }
    }
    playerChoice(i);
    if (playerAnswers[i] == rightAnswers[i]) {

    } else {
      while (true) {
        digitalWrite(3, 1);
        digitalWrite(4, 1);
        digitalWrite(5, 1);
        digitalWrite(6, 1);
        if (digitalRead(12) == 0) {
          flag_reset = true;
          return;
        }
      }
    }
  }
}

void generateRandomNumber(int roundNumber) {
  rightAnswers[roundNumber] = random(4) + 1;
}


void loop() {
  if (flag_reset == false) {
    randomSeed(analogRead(2));
    generateRandomNumber(roundNumber);
    delay(500);
    displayRightSeq(roundNumber);
    delay(500);
    checkAnswers(roundNumber);
    roundNumber = roundNumber + 1;
  } else {
    reset();
    flag_reset = false;
  }
}
