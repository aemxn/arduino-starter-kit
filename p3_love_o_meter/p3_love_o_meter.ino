const int sensorPin = A0; // using analog input A0
const float baselineTemp = 29.0; // temperature baseline

void setup() {
  Serial.begin(9600); // open a serial port w/ 9.6k baud rate
  
  // led pin 2,3,4
  for(int pinNumber = 2; pinNumber < 5; pinNumber++) {
    pinMode(pinNumber, OUTPUT); // initialize pins as output (led)
    digitalWrite(pinNumber, LOW); // turn off led
  }

}

void loop() {
  int sensorVal = analogRead(sensorPin); // read voltage from analog input pin A0
  
  Serial.print("Sensor value: "); // like console.log. Open Serial Monitor
  Serial.print(sensorVal);
  
  /** convert the ADC reading to voltage
   * analog in pin A0-A5 reports value 0-1023
   * maps to a range from 0 volts - 5 volts
   */
  float voltage = (sensorVal/1024.0) * 5.0;
  
  Serial.print(", Volts: ");
  Serial.print(voltage);
  
  Serial.print(", degrees C: ");
  
  /** convert the voltage to temperature in degrees
   * lrn2component datasheet: arduino.cc/kitdatasheets
   * 
   * -0.5*100 is offset bcs sensor can read temperature below 0c
   */
  float temperature = (voltage - 0.5) * 100;
  Serial.println(temperature);
  
  if(temperature < baselineTemp){
    
    // temp less than baseline
    
    digitalWrite(2, HIGH); // led pin 2 = on
    digitalWrite(3, LOW); // led pin 3 = off
    digitalWrite(4, LOW); // led pin 4 = off
    
  } else if (temperature >= baselineTemp + 2 && temperature < baselineTemp + 4) {
    
    // every temp+2 and above, and below temp+4
    
    digitalWrite(2, HIGH); // on
    digitalWrite(3, HIGH); // on
    digitalWrite(4, LOW); // off
    
  } else if (temperature >= baselineTemp + 4) {
    
    // temp more than temp+4
    
    digitalWrite(2, HIGH); // on
    digitalWrite(3, HIGH); // on
    digitalWrite(4, HIGH); // on
  }
  
  delay(1);
  
}
