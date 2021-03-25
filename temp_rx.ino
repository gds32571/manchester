#include <Wire.h>

//#include <LiquidCrystal.h>
#include <Manchester.h>

#define RX_PIN 8 //= physical pin 6
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

LiquidCrystal_I2C lcd(0x27,16,2); //set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(9600);
  Serial.println("receive test");
  
  lcd.begin(16,2);
  lcd.home();
  man.setupReceive(RX_PIN, MAN_300);
  man.beginReceive();
}

void loop() {
  if (man.receiveComplete()) {
    uint16_t m = man.getMessage();
    man.beginReceive(); 
    
   Serial.print("Humid: ");
   Serial.print(m/100);
   Serial.print("   Temp ");
   Serial.println(m%100);
   
    lcd.setCursor(0,0);
    lcd.print("Humid: ");
    lcd.print(m/100);
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(m%100);
    
    }
}


