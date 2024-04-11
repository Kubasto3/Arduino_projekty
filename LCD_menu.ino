#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
int duty = 150;
int state = 0;
bool flaga_menu = true;
bool flaga_autor = false;
bool flaga_pwm = false;
bool flaga_sinus = false;


byte customN[8] = {
  B00100,
  B00000,
  B10110,
  B11001,
  B10001,
  B10001,
  B10001,
  B00000
};

byte customSmile[8] = {
  B00000,
  B01010,
  B01010,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000
};

void setup() {
  pinMode(9, OUTPUT);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);

  lcd.createChar(0, customN);
  lcd.createChar(1, customSmile);
  lcd.begin(16, 2);
  analogWrite(9, duty);
}

void loop() {
  delay(100);

  if (flaga_menu == true) {

    switch (state) {
      case 0:
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.write("Autor");  // "\10"
        lcd.setCursor(1, 1);
        lcd.write("PWM");
        lcd.setCursor(0, 0);
        lcd.write("*");
        break;

      case 1:
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.write("Autor");  // "\10"
        lcd.setCursor(1, 1);
        lcd.write("PWM");
        lcd.setCursor(0, 1);
        lcd.write("*");
        break;

      case 2:
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.write("PWM");  // "\10"
        lcd.setCursor(1, 1);
        lcd.write("Sinus");
        lcd.setCursor(0, 1);
        lcd.write("*");
        break;

      case 3:
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.write("Sinus");  // "\10"
        lcd.setCursor(1, 1);
        lcd.write("Autor");
        lcd.setCursor(0, 1);
        lcd.write("*");
        break;
    }

    delay(500);

    if (digitalRead(11) == LOW) {
      if (state == 0 || state == 3) {
        flaga_menu = false;
        flaga_autor = true;
      }

        if (state == 1) {
          flaga_menu = false;
          flaga_pwm = true;
      }

      if (state == 2) {
          flaga_menu = false;
          flaga_sinus = true;
      }
    }

      if (digitalRead(12) == LOW) {
        state += 1;
        if (state >= 4) {
          state = 1;
        }
        delay(100);
      }
  }

  if (flaga_autor == true) {
    delay(500);
    lcd.setCursor(0, 0);
    lcd.write("Jakub  ");
    lcd.setCursor(0, 1);
    lcd.write("Stoli");
    lcd.write("\10");
    lcd.write("ski");

    if (digitalRead(12) == LOW) {
      flaga_menu = true;
      flaga_autor = false;
    }
  }

  if (flaga_pwm == true) {
    if (digitalRead(11) == LOW) {
      duty += 25;
      if (duty >= 250) {
        duty = 0;
      }
      analogWrite(9, duty);
      delay(100);
    }
    if (digitalRead(12) == LOW) {
      flaga_menu = true;
      flaga_pwm = false;
    }
  }

    if (flaga_sinus == true) {
    delay(500);

    if (digitalRead(12) == LOW) {
      flaga_menu = true;
      flaga_sinus = false;
    }
  }
}
