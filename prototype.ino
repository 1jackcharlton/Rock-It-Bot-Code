/*
* Three ultrasonic sensor array 
* Pixy2 camera
* Prototype Program for A/V P.S. Subproject
*/


#include <Pixy2.h>

Pixy2 pixy;

void ultrasonic(int trigPin[], int echoPin[]);
void camera();

// For breadboard
//can't use pins 10, 11, 12, 13 because Pixy uses these to communicate with Arduino
int trigPin1 = 6; // Trigger left
int echoPin1 = 4; // Echo left
int trigPin2 = 5; // Trigger center
int echoPin2 = 8; // Echo center
int trigPin3 = 9; // Trigger right
int echoPin3 = 7; // Echo right

int trigPin[3] = {trigPin1, trigPin2, trigPin3};
int echoPin[3] = {echoPin1, echoPin2, echoPin3};

/*
//For PCB
int trigPin1 = 7; // Trigger pinright
int echoPin1 = 6; // Echo pinright
int trigPin2 = 5; // Trigger pincenter
int echoPin2 = 4; // Echo pinforward
int trigPin3 = 3; // Trigger pinleft
int echoPin3 = 2; // Echo pinleft
*/

long duration1, inches1, duration2, inches2, duration3, inches3; // input collected data
long cm1avg, inches1avg, cm2avg, inches2avg, cm3avg, inches3avg; // average vals
int count1 = 0, count2 = 0, count3 = 0; // counters for averaging




void setup() {
 //Serial Port begin
 Serial.begin (115200); // BAUD rate
 Serial.print("Starting...\n");

 pixy.init();
 //pixy.changeProg("video"); // required for (optional) RGB values
 pixy.setLamp(0,0);  // upper lamp brightness, lower lamp brightness = 1

 //Define inputs and outputs
 pinMode(trigPin1, OUTPUT);
 pinMode(echoPin1, INPUT);
 pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT);
 pinMode(trigPin3, OUTPUT);
 pinMode(echoPin3, INPUT);
}





void loop() {
  ultrasonic(trigPin, echoPin);
  camera();

}




// ARRAY OF ULTRASONIC SENSOR FUNCTION
void ultrasonic(int trigPin[], int echoPin[]) {
 int trigPin1 = trigPin[0]; // Trigger left
 int echoPin1 = echoPin[0]; // Echo left
 int trigPin2 = trigPin[1]; // Trigger center
 int echoPin2 = echoPin[1]; // Echo center
 int trigPin3 = trigPin[2]; // Trigger right
 int echoPin3 = echoPin[2]; // Echo right
 
 // Ultrasonic sensor 1
 // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
 // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
 
 digitalWrite(trigPin1, LOW);
 delayMicroseconds(5);
 digitalWrite(trigPin1, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin1, LOW);

 // Read the signal from the sensor: a HIGH pulse whose
 // duration is the time (in microseconds) from the sending
 // of the ping to the reception of its echo off of an object.
 pinMode(echoPin1, INPUT);
 duration1 = pulseIn(echoPin1, HIGH);

 // Convert the time into a distance
 inches1 = (duration1/2) / 74; // Divide by 74 or multiply by 0.0135
 if ((inches1  < 100) && (inches1 != 0)) //total length of the course with added 4" buffer length, filtering outliers
  inches1avg += inches1;
  count1 += 1;
  if (count1 == 3) // initiate averaging
    inches1avg = inches1avg/3;
    count1 = 0; // reset counter for averaging
    cm1avg = inches1avg*2.54; // conversion
    
    Serial.print(inches1avg);
    Serial.print("in, ");
    Serial.print(cm1avg);
    Serial.print("cm (left, avg)");
    Serial.println();
    inches1avg = 0; // reset avg




 delay(10); // 10 miliseconds




 // Ultrasonic sensor 2
 digitalWrite(trigPin2, LOW);
 delayMicroseconds(5);
 digitalWrite(trigPin2, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin2, LOW);

 pinMode(echoPin2, INPUT);
 duration2 = pulseIn(echoPin2, HIGH);

 // Convert the time into a distance
 inches2 = (duration2/2) / 74; // Divide by 74 or multiply by 0.0135
 if ((inches2  < 100) && (inches2 != 0)) //total length of the course with added 4" buffer length, filtering outliers
  inches2avg += inches2;
  count2 += 1;
  if (count2 == 3) // initiate averaging
    inches2avg = inches2avg/3;
    count2 = 0; // reset counter for averaging
    cm2avg = inches2avg*2.54; // conversion
    
    Serial.print(inches2avg);
    Serial.print("in, ");
    Serial.print(cm2avg);
    Serial.print("cm (center, avg)");
    Serial.println();
    inches2avg = 0; // reset avg


 delay(10); // delay 10 miliseconds





 // Ultrasonic sensor 3
 digitalWrite(trigPin3, LOW);
 delayMicroseconds(5);
 digitalWrite(trigPin3, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin3, LOW);


 pinMode(echoPin3, INPUT);
 duration3 = pulseIn(echoPin3, HIGH);


  // Convert the time into a distance
 inches3 = (duration3/2) / 74; // Divide by 74 or multiply by 0.0135
 if ((inches3  < 100) && (inches3 != 0)) //total length of the course with added 4" buffer length, filtering outliers
  inches3avg += inches3;
  count3 += 1;
  if (count3 == 3) // initiate averaging
    inches3avg = inches3avg/3;
    count3 = 0; // reset counter for averaging
    cm3avg = inches3avg*2.54; // conversion
    
    Serial.print(inches3avg);
    Serial.print("in, ");
    Serial.print(cm3avg);
    Serial.print("cm (right, avg)");
    Serial.println();
    inches3avg = 0; // reset avg

 delay(2000); //delay 2 seconds
}



// PIXY2 CAMERA BLOCK DETECTING FUNCTION
void camera() {
  // Auto block detector
  int i; 
  // grab blocks
  pixy.ccc.getBlocks();
  
  // If there are detect blocks, print them
  if (pixy.ccc.numBlocks)
  {
    Serial.print("Detected ");
    Serial.println(pixy.ccc.numBlocks); // how many blocks
    for (i=0; i<pixy.ccc.numBlocks; i++) // for each block
    {
      Serial.print("  block "); 
      Serial.print(i); // which block
      Serial.print(": ");
      pixy.ccc.blocks[i].print(); //signature of the obj, x center of obj, y center of obj, width, height, tracking index, age (frames of tracked)
    }
  }
  delay(10);
}