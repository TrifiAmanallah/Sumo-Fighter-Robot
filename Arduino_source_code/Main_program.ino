/* Written by Amanallah Trifi:
 * Git: https://github.com/TrifiAmanallah/ 
 *
 * This a simple algorithm for a sumo fighter Robot
 * There is no need for fancy sofisticated algorithm, this one works just fine ;)
 * In the case of this algorithm, the ring is black and the perimeters are white ! 
 * The Robot is composed of:
 *   - Two infra Red sensors, one on the front and one the back.
 *     Both are pointed down to detect when the robot reaches the perimeters of the ring.
 *   - One Ultrasound sensor to detect the oppenent robot.
 *     Sensor is put on the front of the robot pointed at 90 degrees from ground.
 *   - Two DC motors controlled throught a H-Bridge (L293D) refer to datasheet:
 *     https://github.com/TrifiAmanallah/Sumo-Fighter-Robot\Datasheets 
 *   - Four push buttons, to detect if the robot is being pushed from either sides.
 *     Two buttons on each sides of the robot.  
 * 
 */
 
//***************************************************** 

// set the IR sensors pin numbers:
const int frontIrSensor = 22; // Front IR sensor
const int backIrSensor  = 23; // Back IR sensor

// set the Ultrasound sensors pin numbers:
const int trig1 = 7; // Trigger
const int echo1 = 8; // Echo

// set the L293D controller pin numbers:
const int motor1_enable	=0;
const int motor2_enable	=2;
const int motor1_pin1	=3; //Left Motor
const int motor1_pin2	=4;
const int motor2_pin1	=5; //Right Motor
const int motor2_pin2	=6;

// set the push buttons pin numbers:
const int b1=25; //button right front
const int b2=26; //button right back
const int b3=27; //button left  front
const int b4=28; //button left  back

//*****************************************************

//Readings for the IR sensors
int frontIrSensorValue 	= 0;
int backIrSensorValue 	= 0;
int black	= 80; //the maximal value that differenciate black from white

//Readings for Buttons
int buttonsRight =0;
int buttonsLeft	 =0;

//variables for the algorithme
unsigned long timeNow;
int forceForward	=0;
int forceBackward	=0;
int searchDirection	=1; //1 for left and 0 for right

//*****************************************************

//Setup and initializations
void setup() {
	Serial.begin(9600);
	timeNow=millis();
	//******************
	pinMode(b1, INPUT);
	pinMode(b2, INPUT);
	pinMode(b3, INPUT);
	pinMode(b4, INPUT);
	//******************
	pinMode(frontIrSensor, INPUT);
	pinMode(backIrSensor, INPUT);
	// **************
	pinMode(trig1, OUTPUT); 
	pinMode(echo1, INPUT); 
	//***************
	pinMode(motor1_enable,OUTPUT);
	pinMode(motor2_enable,OUTPUT);
	pinMode(motor1_pin1,OUTPUT);
	pinMode(motor1_pin2,OUTPUT);
	pinMode(motor2_pin1,OUTPUT);
	pinMode(motor2_pin2,OUTPUT);
	// **************
	digitalWrite(motor1_enable,HIGH);
	digitalWrite(motor2_enable,HIGH);
	digitalWrite(motor1_pin1,LOW);
	digitalWrite(motor1_pin2,LOW);
	digitalWrite(motor2_pin1,LOW);
	digitalWrite(motor2_pin2,LOW);
	//*****************
	digitalWrite(trig1, LOW);
	//*****************
	searchDirection=1; // Default search direction is right
	forceForward=0;
	forceBackward=0;
}

//*****************************************************

//Read from IR sensors
void checkGroundColor(){
	frontIrSensorValue = digitalRead(frontIrSensor);
	backIrSensorValue  = digitalRead(backIrSensor);
}

//Read from US sensor
long ultrason1(){
	long readingEcho =0;
	long cm1=0;
	int i;
	/*
	 * To reduce the reading errors, we take 5 measurements
	 * every 25 micro secs and the return the average value
	 */
	for(i=0;i<5;i++){
  		digitalWrite(trig1, HIGH); 
  		delayMicroseconds(25); 
  		digitalWrite(trig1, LOW);
  		readingEcho = pulseIn(echo1, HIGH);              
        cm1 = cm1+ readingEcho/ 58,2;  
    } 
  	return cm1/5;
}

//Read push buttons State
void checkCollision() {
	buttonsRight=0;
	buttonsLeft=0; 
	if ((digitalRead(b1)==1)||(digitalRead(b2)==1)) {buttonsRight=1;}
	else { buttonsRight=0;}
	if ((digitalRead(b3)==1)||(digitalRead(b4)==1)) {buttonsLeft=1;}
	else { buttonsLeft=0;}
}

//Turn Robot Left
void leftTurn() {
    digitalWrite(motor1_pin1,HIGH);
    digitalWrite(motor1_pin2,LOW);
    digitalWrite(motor2_pin1,LOW);
    digitalWrite(motor2_pin2,HIGH);
}

//Turn Robot right                      
void rightTurn() {
    digitalWrite(motor1_pin1,LOW);
    digitalWrite(motor1_pin2,HIGH);
    digitalWrite(motor2_pin1,HIGH);
    digitalWrite(motor2_pin2,LOW); 
} 

//Move Robot Forward                     
void moveForward() { 
	digitalWrite(motor1_pin1,HIGH);
	digitalWrite(motor1_pin2,LOW);
	digitalWrite(motor2_pin1,HIGH);
	digitalWrite(motor2_pin2,LOW);  
}

//Move Robot Backward                
void moveBackward() {
	digitalWrite(motor1_pin1,LOW);
	digitalWrite(motor1_pin2,HIGH);
	digitalWrite(motor2_pin1,LOW);
	digitalWrite(motor2_pin2,HIGH);
}

//Turn Robot Left until it finds the enemy, then push it
void seekAndDestroyLeft() {
	long ClosestObstacle =0;
	ClosestObstacle=ultrason1();
	if(1<ClosestObstacle<140) {moveForward();}                                                                                                      
	else {leftTurn();}
}
  
//Turn Robot Right until it finds the enemy, then push it
void seekAndDestroyRight() {
	long ClosestObstacle =0;
	ClosestObstacle=ultrason1();
	if(1<ClosestObstacle<140) {moveBackward();}
	else {rightTurn();}
}   

int isPerimeterReached(){
	checkGroundColor();
	if ((frontIrSensorValue>black) || (backIrSensorValue>black))  return 1;
	else return 0;
}

int isFrontPerimeterReached(){
	checkGroundColor();
	if (frontIrSensorValue>black) return 1;
	else return 0;
}

int isBackPerimeterReached(){
	checkGroundColor();
	if (backIrSensorValue>black) return 1;
	else return 0;
}

int isCollisionFromRightSide(){
	checkCollision();
	if (buttonsRight==1) return 1;
	else return 0;
}

int isCollisionFromLeftSide(){
	checkCollision();
	if (buttonsLeft==1) return 1;
	else return 0;
}

//*****************************************************
 
//Main Execution Loop 
void loop() {
 
	//Check if the robot need to move backward because it reached the perimeter
	if (forceBackward==1){
		//Move the robot backward for two seconds until it is back to the ring.
		timeNow=millis();
		do{
			moveBackward();
			if ((millis()-timeNow>2000)||(isBackPerimeterReached())) {forceBackward=0;}
		}while(forceBackward==1);
	}

	//Check if the robot need to move forward because it reached the perimeter
	else if(forceForward==1){
		//Move the robot forward for two seconds until it is back to the ring.
		timeNow=millis();
		do{
			moveForward();  
			if ((millis()-timeNow>2000) ||(isFrontPerimeterReached())){forceForward=0;}
		}while(forceForward==1);
	}
         
	//We are away from the perimeters, search for the ennemy robot and push it
	else if(!(isPerimeterReached())) {
    
		// Check if we are being pushed from the right, start searching for the ennemy robot from the right.
		if (isCollisionFromRightSide()) { 
			searchDirection=1;
			seekAndDestroyRight(); 
		}
		// Check if we are being pushed from the left, start searching for the ennemy robot from the left.
		else if (buttonsLeft==1) { 
			searchDirection=0;
			seekAndDestroyLeft(); 
		}	
    
		//We are not being pushed, start searching for the ennemy robot from the last known direction.    
		else if (searchDirection==0) {seekAndDestroyLeft();}
		else if (searchDirection==1) {seekAndDestroyRight();}                       

	}	 
    
	//Check if the robot reached the perimeter     
	else if (isFrontPerimeterReached()&&forceBackward==0) { 
		forceBackward=1;
	}
                                                                                                                  
	else if (isBackPerimeterReached&&forceForward==0) { 
		forceForward=1;                                              
	}                                                                   

//Proceed to the next Loop            
}
