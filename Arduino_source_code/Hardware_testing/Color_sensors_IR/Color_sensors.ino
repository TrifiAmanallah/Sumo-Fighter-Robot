/*
 *
 * Use This code to test the Infra red sensors (color sensors)
 *
 */

// set sensors pin numbers:
const int sensorPin0 = A13; 
const int sensorPin1 = A10; 


void setup() {
	// initialize serial communication at 9600 bits per second:
	Serial.begin(9600);
}

void loop() {
	int sensorValue0 = analogRead(sensorPin0);
	// Display value for sensor0 on seial console
	Serial.println(sensorValue0);
  
	int sensorValue1 = analogRead(sensorPin1);
	// Display value for sensor1 on seial console
	Serial.println(sensorValue1);
  
	// delay in between reads for stability
	delay(1);  
}
