const int greenLEDPin = 9;
const int blueLEDPin = 10;
const int redLEDPin = 11;

const int redSensorPin = A2;
const int blueSensorPin = A1;
const int greenSensorPin = A0;

int redValue = 0;
int blueValue = 0;
int greenValue = 0;

int redSensorValue = 0;
int blueSensorValue = 0;
int greenSensorValue = 0;

void setup() {
	Serial.begin(9600);

	pinMode(greenLEDPin, OUTPUT);
	pinMode(redLEDPin, OUTPUT);
	pinMode(blueLEDPin, OUTPUT);
}

void loop() {
	redSensorValue = analogRead(redSensorPin); // read from red sensor
	delay(5);
	blueSensorValue = analogRead(blueSensorPin); // read from blue sensor
	delay(5);
	greenSensorValue = analogRead(greenSensorPin); // read from green sensor

	Serial.print("\nRaw sensor values \n\t Red: ");
	Serial.print(redSensorValue);
        Serial.print("\n");
	Serial.print("\t Green: ");
	Serial.print(greenSensorValue);
        Serial.print("\n");
	Serial.print("\t Blue: ");
	Serial.print(blueSensorValue);
        Serial.print("\n");
        
        // convert raw reading from 1024 to 255
	redValue = redSensorValue/4;
	blueValue = blueSensorValue/4;
	greenValue = greenSensorValue/4;

	Serial.print("\nMapped sensor values \n\t Red: ");
	Serial.print(redValue);
        Serial.print("\n");
	Serial.print("\t Green: ");
	Serial.print(greenValue);
        Serial.print("\n");
	Serial.print("\t Blue: ");
	Serial.print(blueValue);
        Serial.print("\n");

        // sets LED light levels
	analogWrite(redLEDPin, redValue);
	analogWrite(blueLEDPin, blueValue);
	analogWrite(greenLEDPin, greenValue);
}
