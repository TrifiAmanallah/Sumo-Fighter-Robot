/*
 *
 * Use This code to test push buttons
 *
 */

// set push buttons pin numbers:
const int buttonPin0 = 7; 
const int buttonPin1 = 2;
const int buttonPin2 = 3;
const int buttonPin3 = 4;

// variables for reading the pushbutton status
int buttonState0 = 0;
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;

void setup() {
	// initialize serial communication at 9600 bits per second:	
	Serial.begin(9600);     
	// initialize the pushbuttons pin as an inputs:
	pinMode(buttonPin0, INPUT);  
	pinMode(buttonPin1, INPUT);  
	pinMode(buttonPin2, INPUT);  
	pinMode(buttonPin3, INPUT);  
}

void loop(){
	// read the state of the push buttons value:
	buttonState0 = digitalRead(buttonPin);
	buttonState1 = digitalRead(buttonPin1);
	buttonState2 = digitalRead(buttonPin2);
	buttonState3 = digitalRead(buttonPin3);
	// check if the pushbutton is pressed.
	// States are displayed on seial console
	Serial.println(buttonState0);
	Serial.println(buttonState1);
	Serial.println(buttonState2);
	Serial.println(buttonState3);
}

