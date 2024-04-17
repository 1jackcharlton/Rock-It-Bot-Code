//Haley Stewart
//Jack Charlton
//Line following with delays. In-progress. Ultrasonics are working
//3/17/2024

#include <Servo.h>
#include <Pixy2.h>

Pixy2 pixy;

#define X_CENTER (pixy.frameWidth / 2)

//LED Pins
#define GREENPIN 38
#define REDPIN 39
#define BLUEPIN 40

#define pin1 A1   // left
#define pin2 A14  // center right
#define pin3 A15  // right
#define pin4 A0   // center left

#define PHOTO_SENSOR_PIN A2 //photoresistor





//Ultrasonic Pins
// int trigPin[3] = { 7, 8, 9 };     //7,8,9
// int echoPin[3] = { 24, 23, 22 };  //24,23,22
// int tempAvg[3] = { 0, 0, 0 };     //store the ultrasonic data into temp variable

//IR Pins
float tempAvg[4] = { 0, 0, 0, 0 };  //store the ultrasonic data into temp variable

long duration1, inches1, duration2, inches2, duration3, inches3, inches4, inches;  // input collected data
long cm1avg, inches1avg, cm2avg, inches2avg, cm3avg, inches3avg, inches4avg;       // average vals
int count1 = 0, count2 = 0, count3 = 0, count4 = 0;                                // counters for averaging
long inchesavg, cmavg;
int directionNum;

Servo frontLeft;   //drive, servo is running slower than the others at the same speed
Servo frontRight;  //drive
Servo backLeft;
Servo backRight;
Servo tilt;
Servo flag;
Servo leftClaw;
Servo centerClaw;
Servo rightClaw;
Servo clawTrack;

int servoPinFL = 4;  //left -> needs to go ccw to go "forward"
int servoPinFR = 3;  //right -> needs to go cw to go "forward"
int servoPinBL = 5;
int servoPinBR = 6;
int servoPinTilt = 2;
int servoPinFlag = 46;
int servoPinLC = 14;  //left claw
int servoPinCC = 15;  //center claw
int servoPinRC = 16;  //right claw
int servoPinClawPulley = 47;

int pos1 = 1500;  //store frontLeft stopped position
int pos2 = 1500;  //store frontRight stopped position
int pos3 = 1500;
int pos4 = 1500;

int clockwise = 600;  //normally 500
int stalled = 1500;
int counterClockwise = 2400;  //normally 2500
int frontCounterClockwise = 2326;
int frontClockwise = 674;
int open = 160;  // claw servo val usually 180
int closed = 0;  // claw servo val

//distances are 3 average values over the span of 30ms from ultrasonic sensors. fake input data below in inches:
int leftDistance = 5;     //left ultrasonic sensor
int middleDistance = 10;  //middle ultrasonic sensor
int rightDistance = 4;    //right ultrasonic sensor

int counter = 0;

// feature extraction
int far_x_center = 0;      // shortest distance so all block centers necessarily less than it
int short_x_center = 315;  // farthest distance so all block centers necessarily less than it
int delta_x_center = 0;
int far_block_index = -1;      // init val nonsensical to show update of index
int short_block_index = -1;    // ^
int biggest_area = 0;          // ^
int biggest_block_index = -1;  // which block is biggest
int index_block;               // iterator variable
int valx1, valx2;              // alignment pixel values for fuel tanks
int aligned_counter = 0;

// Flags to ensure messages are processed only once
bool startMessageReceived = false;
bool efMessageReceived = false;
bool endMessageSent = false;

//define trig pins

// void course() {
//   forward(10);
//   delay(5900); //need to debug delays //17s 1000ms in 1 sec //9.13
//   left(10);
//   delay(1500); //2
//   forward(10);
//   delay(2000);
//   right(10);
//   delay(1500);
//   left(10);
//   delay(1500);
//   delay(1500);
//   forward(10);
//   delay(2000);
//   stop(10);
// }

void waitForStart() {
  //pinMode(START_BUTTON_PIN, INPUT_PULLUP); // Set the button pin as input with internal pull-up resistor
  pinMode(PHOTO_SENSOR_PIN, INPUT); // Set the photoresistor pin as input

  while ((analogRead(PHOTO_SENSOR_PIN) < 750) && (!startMessageReceived)) {
    // Wait for the button press or bright light condition
    // Serial.print("PHOTO_SENSOR: ");
    // Serial.print(analogRead(PHOTO_SENSOR_PIN));
    Serial.println();
    delay(50); // Adjust this delay as needed
    String incoming = Serial1.readStringUntil('\n');
    incoming.trim();
    Serial.println(incoming); // Debug print the incoming message
    
    if (incoming == "COMPETITION_START") {
      // Handle the "COMPETITION_START" message
      startMessageReceived = true;
    }
  }

  // Button has been pressed or bright light detected, continue with the program
}


void setup() {
  servoInit();
  //pixy_line_setup();  //hope this works
  pixy_object_setup();
  LEDsetup();
  //ultrasonic_setup(trigPin, echoPin);
  clawServoInit();
  //pixyLoop();
  comm_setup();

  //test only once
  //test();

  //forward(1500);
  //right(10);
  //delay(950);
  //left();
  //delay(2200);
  //delay(1500);
  //forward();
  //delay(2000);
  //stop(10);
}

float timeSinceStart = millis();  //need this?
float t1L, t1R;
int Lswitch = 0, Rswitch = 0;
int no_vector_count = 0;  // amount of times no vector found
int vector_ignore = 0;    // if 0 then no ignore vectors until fully turned
int state = 0;            // 9 lowers 1st, 10 raises // state 0
long leftU, centerU, rightU, centerUL, centerUR;
int switcht = 0;   // adjust when to pause periodically in adjust_ultrasonic
int time_rec = 0;  //for ultrasonsic
int leftTurnCounter = 0;
int rightTurnCounter = 0;
int halfSwitch = 0;  // we have not made half a turn so 0
int T1, T2, T3, delta_t_turn;
int raise = 0;

void loop() {
  //pixyLoop();


  switch (state) {
    case -1:
    stop(1);
    break;

    case 0:  // go off the robot and to the end of the ramp
      //line_following_function();
      waitForStart(); //wait for LED 
      lowerClaws(1500);
      flag.write(130);  //horizontal
      delay(1000);
      flag.write(0);  //to raise flag to vertical position
      //raiseClaws(2700);  //2sec
      forward(500);
      if (raise != 1) {
      
      //delay(50);
      raiseClaws(2000); //perfect
      raise++;
      }
      forward(6000);  //8s to get to intersection on its own, 6500 for tandem robot
      stop(1000);
      // while ((centerUR == 0) && (centerUL == 0)) {
      //   slow(100);  //?
      //   infrared_detect();
      //   leftU = tempAvg[0];
      //   centerUR = tempAvg[1];
      //   rightU = tempAvg[2];
      //   centerUL = tempAvg[3];
      //   if (centerUL == 0) {
      //     centerU = centerUR;
      //   } else if (centerUR == 0) {
      //     centerU = centerUL;
      //   } else {
      //     centerU = (centerUL + centerUR) / 2;
      //   }
      // }
      raise = 0;
      state = 1;  // need conditions for state change
      break;

    case 1:  // on ramp or coming off of robot, first left turn
      //line_following_function();
      //int {test1, test2, test3};
      //slow(500); //TODO go forward half a second after ramp?
      infrared_detect();
      leftU = tempAvg[0];
      centerUR = tempAvg[1];
      rightU = tempAvg[2];
      centerUL = tempAvg[3];
      if (centerUL == 0) {
        centerU = centerUR;
      } else if (centerUR == 0) {
        centerU = centerUL;
      } else {
        centerU = (centerUL + centerUR) / 2;
      }

      if (raise != 1) {
      lowerClaws(1500);
      //delay(50);
      //raiseClaws(2000); //perfect
      raise++;
      }

      //adjust_robot_ultrasonic(leftU, centerU, rightU);

      if (leftTurnCounter != 1) {
        //adjust_robot_ultrasonic(leftU, centerU, rightU);
        left_turn_90(leftU, centerU, rightU);
        //stop(2000);
      } else {
        left(500);
        forward(1000);
        right(500); //250
        backward(2000);
        stop(1000);
        forward(3000);
        leftTurnCounter = 0;
        state = 2;
      }
      break;

    case 2:  //approach second left turn
    // get fuel tanks

      if (leftTurnCounter != 1) {  //approach wall close to fuel tanks and rotate right 90 deg to face them
        forward(1);
        infrared_detect();
        leftU = tempAvg[0];
        centerUR = tempAvg[1];
        rightU = tempAvg[2];
        centerUL = tempAvg[3];
        if (centerUL == 0 ){
          centerU = centerUR;
        } else if (centerUR == 0 ){
          centerU = centerUL;
        } else {
          centerU = (centerUL + centerUR)/2;
        }

        if (centerU < 13) {  // 15
          slow(50);
          if (centerU < 11) {  // 12
            T3 = millis();
            while (millis() - T3 < (2.5 * delta_t_turn)) {  // make a 90 turn
              left(1);
            }
            leftTurnCounter++;
          }
        }
      } else { 
        stop(3000);
        forward(1000);
        left(250); // back into fuel tanks
        backward(1000);
        right(250);
        forward(1000);
        left(250); // back into fuel tanks
        backward(500);
        right(250);
        backward(2000);
        stop(1000);
        backward(500);
        leftTurnCounter = 0;
        state = 3;
      }


      break;

      case 3:
      if (raise != 1) {
      //lowerClaws(1500);
      //delay(50);
      raiseClaws(2000); //perfect
      raise++;
      }
      forward(11000);  // cross the trench
      centerU = 0;
      while(centerU < 3.5){ //?
        backward(20);

        infrared_detect();
        leftU = tempAvg[0];
        centerUR = tempAvg[1];
        rightU = tempAvg[2];
        centerUL = tempAvg[3];
        if (centerUL == 0) {
          centerU = centerUR;
        } else if (centerUR == 0) {
          centerU = centerUL;
        } else {
          centerU = (centerUL + centerUR) / 2;
        }
      }
      
      state = 4;       // go to team promotion
      break;
      

    

    
    case 4:
      //reverse a little bit and turn 180 to face the button - dont need to face button
      //team promotion BEFORE hitting the launch button but after the thruster assembly
      //check time/communicate with other robot
      //press button by ramming into it. Maybe we just reverse straight from assembly instead of rotating
      //done
      //team_promote_LED(250); // 5 second duration
      team_promote_flag();  // wave flag team_promote_flag() now has the LEDs too
      //forward(7000);
      //straighten();
      leftTurnCounter = 0;
      if (efMessageReceived == true){
        state = 5;
      }
      //implement fail safe for if they don't push button
      if (millis() > 90000) {
        state = 5;
      }
      break;


// old case 5
    // case 5:
    //   forward(1);
    //   infrared_detect();
    //   leftU = tempAvg[0];
    //   centerUR = tempAvg[1];
    //   rightU = tempAvg[2];
    //   centerUL = tempAvg[3];
    //   if (centerUL == 0) {
    //     centerU = centerUR;
    //   } else if (centerUR == 0) {
    //     centerU = centerUL;
    //   } else {
    //     centerU = (centerUL + centerUR) / 2;
    //   }

    //   if (leftTurnCounter != 1) {//TODO
    //   //left_turn_90(leftU, centerU, rightU);
    //   left(2200); //TODO hard code?
    //   leftTurnCounter++;
    //   } else{
    //     forward(3000);
    //     backward(5500);
    //     state = 6;

    //   }
        // back up into the button
      //int switch_promote; // val that changes if collide with wall

      // while(switch_promote == Z){
      //   backward(1);
      //   switch_promote = f(); // logic using switch input
      // }
    break;




    case 5:
if (leftTurnCounter != 1) {  //approach wall close to fuel tanks and rotate right 90 deg to face them
        forward(1);
        infrared_detect();
        leftU = tempAvg[0];
        centerUR = tempAvg[1];
        rightU = tempAvg[2];
        centerUL = tempAvg[3];
        if (centerUL == 0 ){
          centerU = centerUR;
        } else if (centerUR == 0 ){
          centerU = centerUL;
        } else {
          centerU = (centerUL + centerUR)/2;
        }

        // if (centerU < 12) {  // 15
        //   slow(50);
        //   if (centerU < 8) {  // 12
            T3 = millis();
            while (millis() - T3 < (2.5 * delta_t_turn)) {  // make a 90 turn
              left(1);
            }
            leftTurnCounter++;
          // }
        // }
      // } else { 
        forward(3000);
        backward(5500);
        leftTurnCounter = 0;
        state = 6;
      }
    break;


    case 6:
      stop(1);  // done!11!!1!!!!

    break;

    case 8:  // we gave up on fuel tanks
             // turn 180, back into the wall, claws close, claws go up, go over the trench, team promote, and push launchbutton
      // T3 = millis();
      // while (millis() - T3 < (2.5 * delta_t_turn)) {  // make a 180
      //   left(1);
      // }

      // backward(2500);  // straighten
      // pull up servos using servoPinPulley
      if (raise != 1) {
      lowerClaws(1500);
      //delay(50);
      raiseClaws(2000); //perfect
      raise++;
      }
      stop(1);
      

      break;

    case 9:  // test state
    

      break;



    case 12:  // straighten
      //straighten();
      //align_distance();
      infrared_detect();
      leftU = tempAvg[0];
      centerUR = tempAvg[1];  //when ultrasonic is 9, 10, 11 in, we can use x1 120 x2 100
      rightU = tempAvg[2];
      centerUL = tempAvg[3];
      //delay(500);
      centerU = (centerUL + centerUR) / 2;
      if (((centerUL - centerUR < 0.25) && (centerUL - centerUR > -0.25)) && (centerUR != 0) && (centerUL != 0)) {
        analogWrite(BLUEPIN, 255);  //blue off; //blue on
      }
      //state = 3;  //end case
      break;
  }

}  //end loop
