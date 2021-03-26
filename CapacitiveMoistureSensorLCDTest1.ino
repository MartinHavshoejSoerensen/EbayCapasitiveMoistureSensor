#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3E, 20, 4);

#define inputPin A0
#define delayTime 1000

int inputVal = 0;
int inputValMin = 589 ; // Mest fugtig.
int inputValMax = 667; // Mindst fugtig.
int corrInputVal;
int fugtPct;

void readData(){
    inputVal = analogRead(inputPin);
}

void processData(){
    corrInputVal = map(inputVal, inputValMin, inputValMax, 0, 1023);
    corrInputVal = constrain(corrInputVal, 0, 1023);
    fugtPct = map(corrInputVal, 0, 1023, 100, 0);  
}

void serialPrint(){
    Serial.println("********************");
    Serial.println("  ");
    Serial.print("inputVal      : ");
    Serial.println(inputVal);
    Serial.print("corrInputVal  : ");
    Serial.println(corrInputVal);
    Serial.print("fugtPct       : ");
    Serial.print(fugtPct);
    Serial.println(" %");
    Serial.println("  ");
}

void LCDPrint(){
    lcd.setCursor(1, 0);   
    lcd.print("inputVal     :");
    if(inputVal < 10){
      lcd.print("   ");
      }
    else if(inputVal < 100){
      lcd.print("  ");
      }
    else if(inputVal < 1000){
      lcd.print(" ");     
      }
    lcd.print(inputVal);
      
    lcd.setCursor(1, 1);
    lcd.print("corrInputVal :");
    if(corrInputVal < 10){
      lcd.print("   ");
      }
    else if(corrInputVal < 100){
      lcd.print("  ");    
      }
    else if(corrInputVal < 1000){
      lcd.print(" ");     
      }
    lcd.print(corrInputVal);
    
    lcd.setCursor(1, 2);
    lcd.print("fugtPct      :");
    if(fugtPct < 10){
      lcd.print("   ");
      }
    else if(fugtPct < 100){
      lcd.print("  ");     
      }
    else if(fugtPct < 1000){
      lcd.print(" ");
      }
    lcd.print(fugtPct);
}

void setup() {
    Serial.begin(9600);

    lcd.init();
    lcd.backlight();
    lcd.clear();

    pinMode(inputPin, INPUT);
}

void loop() {
    readData();

    processData();

    serialPrint();

    LCDPrint();

    delay(delayTime);
}
