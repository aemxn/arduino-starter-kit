#include <Servo.h>
#include <Time.h>
#include <TimeAlarms.h>

Servo myServo;

// int const potPin = A0;
int potVal;
int angle;
int initPos = 0; // 0 to 850
int finalPos = 500;

void setup() {
  myServo.attach(9);
  Serial.begin(9600);
  
  setTime(13,55,50,10,17,15); // set current time to Saturday 8:29:00am Jan 1 2011
  Alarm.alarmRepeat(13,56,0, MorningAlarm);  // 8:30am every day

  // init servo position to 0
  angle = map(initPos, 0, 1023, 0, 179);
  myServo.write(angle);  
}

void loop() {
  digitalClockDisplay();
  Alarm.delay(1000); // wait one second between clock display
  
}

// functions to be called when an alarm triggers:
void MorningAlarm() {
  angle = map(finalPos, 0, 1023, 0, 179);
  myServo.write(angle);
  
  Serial.println("Alarm: - turn lights on");    
}

void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}

void printDigits(int digits) {
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

