/*
 *
 * Use This code to test the Ultrasound sensor
 *
 */

// set Ultrasound sensor pin numbers:
const int trig1 = 7; 
const int echo1 = 6; 

// Variables used to calculate distance:
long lecture_echo1=0; 
long cm1=0;
long dist=0;
int  i=0;

void setup() {
	// initialize serial communication at 9600 bits per second:	
	Serial.begin(9600);
	// initialize the sensor trigger and echo pins:
	pinMode(trig1, OUTPUT); 
	pinMode(echo1, INPUT); 
	digitalWrite(trig1, LOW);
}

//Calculate the distance to the closest obstacle from raw read data
long calculateDistance(){
	cm1=0;
	for(i=0;i<5;i++){
		digitalWrite(trig1, HIGH); 
  		delayMicroseconds(25); 
  		digitalWrite(trig1, LOW);
  		lecture_echo1 = pulseIn(echo1, HIGH);              
		cm1 = cm1+ lecture_echo1/ 58,2;  
	}           
	return cm1/5;
}

void loop() {
	// read distance from the sensor:
	dist=calculateDistance();
	// Distances are displayed on seial console
	Serial.println(dist);
}
