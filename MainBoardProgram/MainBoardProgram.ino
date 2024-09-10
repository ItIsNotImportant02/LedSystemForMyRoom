
#include <LCDI2C_Multilingual.h>
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
int currentRowDisplay = 0;
int currentMenuSlide = 0;
bool change = LOW;
bool whiteOn = LOW;
bool tempColorOn = LOW;


String menuMain[] = {"1. Mode menu","2. #Temp setup#","3. #Alarm Clock#","Have a good day :D"};
int menuRows = 0;

String menuModes[] = {"Rtrn to HomePage","1. WhiteMode", "2. TempMode","3. #cumming soon","Have a good day :D"};

LCDI2C_Generic lcd(0x27, 20, 4);  // I2C address: 0x27; Display size: 20x4

void setup() {

  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
  pinMode(BUTTON4, INPUT);

  lcd.init();
  lcd.backlight();

  /*startMenu();*/

  change = HIGH;

}

void loop() {

  if(digitalRead(BUTTON1) == HIGH && buttPressed == LOW) {
    if(currentRow > 0) {
      currentRow--;
    }else{
      currentRow = menuRows - 1;
    }

    if(currentRowDisplay < 3) {
      currentRowDisplay--;
    }else{
      currentMenuSlide--;
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

    if(currentRowDisplay > 0) {
      currentRowDisplay++;
    }else{
      currentMenuSlide++;
    }
    
    change = HIGH;
    buttPressed = HIGH;
  }

  if(digitalRead(BUTTON2) == HIGH && buttPressed == LOW) {
    /*sellectFunc();*/
    change = HIGH;
    buttPressed = HIGH;
  }

  if(digitalRead(BUTTON1) == LOW && digitalRead(BUTTON3) == LOW) {
    buttPressed = LOW;
    }

  if(change == HIGH) {
    /*
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
    */
    displayFunc();

    change = LOW;
    switch(state) {
      case 0:
        menuRows = 3;
        break;
      case 1:
        menuRows = 3;
        break;
    }
  }

}
/*
void sellectFunc() {

  if(state == 0 && currentRow == 0) {
    state = 1;
    change = HIGH;
    currentRow = 0;
    cleanDisplay();
    modesMenu();
  }

}
*/

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
  lcd.setCursor(2, 3);
  lcd.println("Have a good day :D");

}

void displayFunc() {

  if(state == 0) {
   
    lcd.setCursor(2, 0);
    lcd.println(menuMain[currentMenuSlide]);
    lcd.setCursor(2, 1);
    lcd.println(menuMain[currentMenuSlide + 1]);
    lcd.setCursor(2, 2);
    lcd.println(menuMain[currentMenuSlide + 2]);
    lcd.setCursor(2, 3);
    lcd.println(menuMain[currentMenuSlide + 3]);
    lcd.setCursor(0, 0);
    lcd.println("  ");
    lcd.setCursor(0, 1);
    lcd.println("  ");
    lcd.setCursor(0, 2);
    lcd.println("  ");
    lcd.setCursor(0, 3);
    lcd.println("  ");
    lcd.setCursor(0, currentRowDisplay);
    lcd.println("> ");

  }else if(state == 1) {

    lcd.setCursor(2, 0);
    lcd.println(menuModes[currentMenuSlide]);
    lcd.setCursor(2, 1);
    lcd.println(menuModes[currentMenuSlide + 1]);
    lcd.setCursor(2, 2);
    lcd.println(menuModes[currentMenuSlide + 2]);
    lcd.setCursor(2, 3);
    lcd.println(menuModes[currentMenuSlide + 3]);
    lcd.setCursor(0, 0);
    lcd.println("  ");
    lcd.setCursor(0, 1);
    lcd.println("  ");
    lcd.setCursor(0, 2);
    lcd.println("  ");
    lcd.setCursor(0, 3);
    lcd.println("  ");
    lcd.setCursor(0, currentRowDisplay);
    lcd.println("> ");

  }
}

void cleanDisplay() {
  lcd.setCursor(2, 0);
  lcd.println("                  ");
  lcd.setCursor(2, 1);
  lcd.println("                  ");
  lcd.setCursor(2, 2);
  lcd.println("                  ");
  lcd.setCursor(2, 3);
  lcd.println("                  ");
}


