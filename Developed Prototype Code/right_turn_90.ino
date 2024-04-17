//Haley Stewart
//Jack Charlton
//Rotate robot 90 degrees to the left based off of ultrasonic data
//3/14/2024

void right_turn_90(long leftU, long centerU, long rightU) {
  if (centerU > 10) {  //not getting centerU fast enough, need to implement millis() into a variable and use it as a 'delay'
    forward(5);
  } else if ((centerU < 10) && (centerU != 0) && (leftU != 0) && (rightU != 0)) {  //should never be 0, getting zeros at startup
    //instead of turning for a certain time. take snapshot of center ultrasonic, turn robot to left until right ultra is that same distance
    int tempCenter;
    tempCenter = centerU; 
    Serial.print("tempCenter: ");
    Serial.print(tempCenter);
    Serial.println();
    int T1 = millis();
    while (leftU < tempCenter) {           // wait until center sensor is reading about what the left sensor was reading + 2in since the distance is greater at 90 turn
      infrared_detect(); //update ultrasonic data inside while loop
      leftU = tempAvg[0];
      centerUR = tempAvg[1];
      rightU = tempAvg[2];
      centerUL = tempAvg[3];
      centerU = (centerUL + centerUR)/2;

      Serial.print("INSIDE WHILE:");
      Serial.print(leftU);
      Serial.print("in, ");
      Serial.print("(left, avg)");
      Serial.println();
      //delay(5);

      Serial.print(centerU);
      Serial.print("in, ");
      Serial.print("(center, avg)");
      Serial.println();
      //delay(5);

      Serial.print(rightU);
      Serial.print("in, ");
      Serial.print("(right, avg)");
      Serial.println();
      right(5);  // keep turning left
    }
    halfSwitch = 1;  // we have made half a turn
    T2 = millis();
    if (halfSwitch == 1) {
      T3 = millis();
      while (millis() - T3 < T2 - T1) {
        right(5);
      }
      halfSwitch = 0;
      rightTurnCounter++;
    }
  }
}
