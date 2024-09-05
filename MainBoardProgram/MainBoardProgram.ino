
#include <LCDI2C_Multilingual.h>
#include <FastLED.h>
#include <WS2812FX.h>

#define BUTTON1 16
#define BUTTON2 17
#define BUTTON3 18
#define BUTTON4 19

bool buttPressed = LOW;

/*
States
0 - Menu
1 - On/Off/Modes Menu
*/
int state = 0;
int currentRow = 0;
bool change = LOW;
bool whiteOn = LOW;
bool tempColorOn = LOW;
int menuRows = 0;

LCDI2C_Generic lcd(0x27, 20, 4);  // I2C address: 0x27; Display size: 20x4

void setup() {

  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
  pinMode(BUTTON4, INPUT);

  lcd.init();
  lcd.backlight();

  startMenu();

  change = HIGH;

}

void loop() {

  if(digitalRead(BUTTON1) == HIGH && buttPressed == LOW) {
    if(currentRow > 0) {
      currentRow--;
    }else{
      currentRow = menuRows - 1;
    }
    change = HIGH;
    buttPressed = HIGH;
  }

  if(digitalRead(BUTTON3) == HIGH && buttPressed == LOW) {
    if(currentRow < menuRows - 1) {
      currentRow++;
    }else{
      currentRow = 0;
    }
    change = HIGH;
    buttPressed = HIGH;
  }

  if(digitalRead(BUTTON1) == LOW && digitalRead(BUTTON3) == LOW) {
    buttPressed = LOW;
    }

  if(change == HIGH) {
    lcd.setCursor(0, 0);
    lcd.println("  ");
    lcd.setCursor(0, 1);
    lcd.println("  ");
    lcd.setCursor(0, 2);
    lcd.println("  ");
    lcd.setCursor(0, 3);
    lcd.println("  ");
    lcd.setCursor(0, currentRow);
    lcd.println("> ");
    change = LOW;
    switch(state) {
      case 0:
        menuRows = 3;
        break;
      case 1:
        menuRows = 2;
        break;
    }
  }

}

void startMenu() {

  lcd.setCursor(2, 0);
  lcd.println("1. Mode menu");
  lcd.setCursor(2, 1);
  lcd.println("2. #Temp setup#");
  lcd.setCursor(2, 2);
  lcd.println("3. #Alarm Clock#");
  lcd.setCursor(1, 3);
  lcd.println("Have a good day :D");

}

void modesMenu() {

  lcd.setCursor(2, 0);
  if(whiteOn == LOW) {
    lcd.println("1. WhiteMode OFF");
  }else{
    lcd.println("1. WhiteMode ON");
  }
  lcd.setCursor(2, 1);
  if(tempColorOn == LOW) {
    lcd.println("2. TempMode OFF");
  }else{
    lcd.println("2. TempMode ON");
  }
  lcd.setCursor(2, 2);
  lcd.println("3. #cumming soon#");
  lcd.setCursor(1, 3);
  lcd.println("Have a good day :D");

}
