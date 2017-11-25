# Sumo Fighter Robot
An Arduino based autonomous Sumo Fighter Robot.

<img src="Pics/photo_1.jpg" width="300"> <img src="Pics/photo_2.jpg" width="300">

# Mechanical Design:
Solidworks drawing are available under: 
https://github.com/TrifiAmanallah/Sumo-Fighter-Robot/tree/master/Mechanics

![picture](Pics/photo_3.png)

# Eletrical Components:
The Robot is composed of:
 - An arduin Uno board.
 - Two infra Red sensors, one on the front and one the back.
   Both are pointed down to detect when the robot reaches the perimeters of the ring.
   Reference: Cny70
   Datasheet: Sumo-Fighter-Robot\Datasheets\Cny70.pdf
 - One Ultrasound sensor to detect the oppenent robot.
   Sensor is put on the front of the robot pointed at 90 degrees from ground.
   Reference: Parallax-28015
   Datasheet: Sumo-Fighter-Robot\Datasheets\Parallax-28015.pdf
 - One H-bridge motor driver
   Reference: L293D
   Datasheet: Sumo-Fighter-Robot\Datasheets\L293D.pdf 
 - Two DC Motors
   Reference: Valeo Baureihe 0278
   Datasheet: Sumo-Fighter-Robot\Datasheets\Motor_3.pdf
-  Four push buttons, to detect if the robot is being pushed from either sides.
   Two buttons on each sides of the robot. 
-  One Lipo Battery
   Reference: Turnigy 2200mAh
   Datasheet: Sumo-Fighter-Robot\Datasheets\Lipo_batteries.pdf
   
   # Wiring Components:
   
   The Motors:
   
   <img src="Electrical_Wiring/wiring_l293d.png" width="500">
   
   The Ultrasound sensor:
   
   <img src="Electrical_Wiring/wiring_ultrasound.png" width="500">
 
   The IR sensor:
   
   <img src="Electrical_Wiring/wiring_infrared.JPG" width="500">
 
   The push buttons:
   
   <img src="Electrical_Wiring/wiring_pushbutton.jpg" width="500">
 
   
