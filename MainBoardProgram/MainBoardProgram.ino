
#include <LCDI2C_Multilingual.h>
#include <WS2812FX.h>
#include <FastLED.h>

#define BUTTON1 16
#define BUTTON2 17
#define BUTTON3 18
#define BUTTON4 19

#define NUM_LEDS 8
#define DATA_PIN 14
CRGB leds[NUM_LEDS];

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
bool maxCurrentSlide = 0;

int menuRows = 0;

String menuMain[] = {"1. Mode menu","2. #Temp setup#","3. #Alarm Clock#","Have a good day :D"};
int menuMainRows = 4;
String menuModes[] = {"Rtrn to HomePage","1. WhiteMode", "2. TempMode","3. #cumming soon","Have a good day :D"};
int menuModesRows = 5;

LCDI2C_Generic lcd(0x27, 20, 4);  // I2C address: 0x27; Display size: 20x4

void setup() {

  Serial.begin(9600);

  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
  pinMode(BUTTON4, INPUT);

  lcd.init();
  lcd.backlight();

  change = HIGH;
  menuRows = menuMainRows;

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

}

void loop() {

//Tlačítko Nahoru
  if(digitalRead(BUTTON1) == HIGH && buttPressed == LOW) { 

    if(currentRow > 0) {
      currentRow--;
    }

    if(currentRowDisplay > 0) {
      currentRowDisplay--;
    }else{
      if(currentMenuSlide > 0){
        currentMenuSlide--;
      }
    }

    change = HIGH;
    buttPressed = HIGH;
  }
//Tlačítko Dolu
  if(digitalRead(BUTTON3) == HIGH && buttPressed == LOW) {
    if(currentRow < menuRows - 1) {
      currentRow++;
    }

    if(currentRowDisplay < 3) {
      currentRowDisplay++;
    }else{
      if(currentMenuSlide < maxCurrentSlide) {
        currentMenuSlide++;
      }
    }
    
    change = HIGH;
    buttPressed = HIGH;
  }

  if(digitalRead(BUTTON2) == HIGH && buttPressed == LOW) {
    sellectFunc();
    change = HIGH;
    buttPressed = HIGH;
  }

  if(digitalRead(BUTTON1) == LOW && digitalRead(BUTTON3) == LOW && digitalRead(BUTTON2) == LOW) {
    buttPressed = LOW;
    }

  displayFunc();

  Serial.print("state: " + String(state) + "\t");
  Serial.print("currentRow: " + String(currentRow) + "\t");
  Serial.print("currentRowDisplay: " + String(currentRowDisplay) + "\t");
  Serial.print("menuRows: " + String(menuRows) + "\t");
  Serial.print("currentMenuSlide: " + String(currentMenuSlide) + "\n");

}

void sellectFunc() {

  switch(state) {
    case 0: //Hlavni Menu
      switch(currentRow) {
        case 0: // Mode Menu
            cleanDisplay();
            state = 1;
            currentMenuSlide = 0;
            menuRows = menuModesRows;
            maxCurrentSlide = menuRows - 4;
          break;
        case 1: // Temp Menu

          break;
        case 2: // Alarm Clock

          break;
        case 3: 

          break;
      }
      break;
    case 1: //Menu Modů
      switch(currentRow) {
        case 0: //Return Main Menu
            returnMainMenu();
          break;
        case 1: // ON/OFF White Mode

          break;
        case 2: // ON/OFF Temp Mode

          break;
        case 3: // There is nothing we can do "Now"

          break;
      }
      break;
    case 2: 

      break;
  }

}

void displayFunc() {

  switch(state) {
    case 0:
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
      break;
    case 1:
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
      break;
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

void returnMainMenu() {
  cleanDisplay();
  Serial.print("I am idiot"); 
  currentMenuSlide = 0;
  menuRows = menuMainRows;
  state = 0;
  maxCurrentSlide = menuRows - 4;
}

