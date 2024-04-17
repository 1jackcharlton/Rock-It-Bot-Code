//Haley Stewart
//Jack Charlton
//Straight Angle
//3/13/2024

void straighten() {  // used for finding when parallel to left wall
  infrared_detect();
  leftU = tempAvg[0];
  centerUR = tempAvg[1];
  rightU = tempAvg[2];
  centerUL = tempAvg[3];

  Serial.println("CenterUR: ");
  Serial.print(centerUR);
  Serial.println("CenterUL: ");
  Serial.print(centerUL);
  centerU = (centerUL + centerUR) / 2;
  //int triggerSensor = 0;
  while (((centerUL - centerUR > 0.25) || (centerUL - centerUR < -0.25)) || (centerUR == 0)|| (centerUL == 0)) {
    if (centerUL > centerUR) {  //left is a little more forward
      right(50);
      stop(500);
    }
    if (centerUL < centerUR) {  //right is a little more forward
      left(50);
      stop(500);
    }
    infrared_detect();
    leftU = tempAvg[0];
    centerUR = tempAvg[1];
    rightU = tempAvg[2];
    centerUL = tempAvg[3];
    centerU = (centerUL + centerUR) / 2;
  }
}