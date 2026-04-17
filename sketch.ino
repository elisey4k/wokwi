#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDRESS 0x27   
#define LCD_COLUMNS 20   
#define LCD_ROWS    4 

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

const int buttonPin = 2;   
volatile bool flag = false;

long fibonacci(int n) {
  if (n <= 1) return n;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Press button...");
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    delay(50);
    if (digitalRead(buttonPin) == LOW) {
      int n = random(5, 31);
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Random: ");
      lcd.print(n);
      
      unsigned long start = micros();
      long fibResult = fibonacci(n);
      unsigned long elapsed = micros() - start;
      float seconds = elapsed / 1000000.0;
      
      char timeBuffer[20];
      dtostrf(seconds, 0, 5, timeBuffer);   // "0.12345"
      lcd.setCursor(0, 1);
      lcd.print("Time: ");
      lcd.print(timeBuffer);
      lcd.print(" sec");
      
      lcd.setCursor(0, 2);
      lcd.print("Number: ");
      lcd.print(fibResult);
      
      while (digitalRead(buttonPin) == LOW) delay(10);
      delay(100);
    }
  }
}