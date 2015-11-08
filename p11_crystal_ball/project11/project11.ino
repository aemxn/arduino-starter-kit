#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int switchPin = 6;
int switchState = 0;
int prevSwitchState = 0;
int reply;

void setup() {
  lcd.begin(16, 2);
  pinMode(switchPin, INPUT);
  lcd.print("Donate fund:");
  lcd.setCursor(0, 1);
  lcd.print("RM 10");  
}

void loop() {
  switchState = digitalRead(switchPin);
  
  if(switchState != prevSwitchState){
    if (switchState == LOW) {
      reply = random(8);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("The ball says: ");
      lcd.setCursor(0, 1);
      
      switch(reply) {
        case 0:
          lcd.print("yes");
          break;
        case 1:
          lcd.print("most likely");
          break;
        case 2:
          lcd.print("certainly");
          break;
        case 3:
          lcd.print("outlook good");
          break;
        case 4:
          lcd.print("unsure");
          break;
        case 5:
          lcd.print("ask again!");
          break;
        case 6:
          lcd.print("doubtful");
          break;
        case 7:
          lcd.print("No");
          break;    
      }
    }
  }
  
  prevSwitchState = switchState;
}
