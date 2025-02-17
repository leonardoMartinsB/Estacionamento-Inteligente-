#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo1;

int IR1 = 2;
int IR2 = 4;
int Slot = 4;

int flag1 = 0;
int flag2 = 0;

void setup() {
  lcd.begin();
  lcd.backlight();

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  myservo1.attach(3);
  myservo1.write(100);

  lcd.setCursor(0, 0);
  lcd.print("     ARDUINO    ");
  lcd.setCursor(0, 1);
  lcd.print(" ESTACIONAMENTO INTELIGENTE ");
  delay(2000);
  lcd.clear();
}

void loop() { 
  if (digitalRead(IR1) == LOW && flag1 == 0) {
    if (Slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo1.write(0); 
        Slot = Slot - 1;
      }
    } else {
      lcd.setCursor(0, 0);
      lcd.print("    DESCULPE!  ");  
      lcd.setCursor(0, 1);
      lcd.print("  Estacionamento Cheio  "); 
      delay(3000);
      lcd.clear();
    }
  }

  if (digitalRead(IR2) == LOW && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo1.write(0); 
      Slot = Slot + 1;
    }
  }

  if (flag1 == 1 && flag2 == 1) {
    delay(1000);
    myservo1.write(100);
    flag1 = 0;
    flag2 = 0;
  }

  lcd.setCursor(0, 0);
  lcd.print("    BEM VINDO!    ");
  lcd.setCursor(0, 1);
  lcd.print("Vagas Restantes: ");
  lcd.print(Slot);
}