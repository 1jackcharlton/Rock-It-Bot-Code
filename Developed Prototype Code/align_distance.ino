//Haley Stewart
//Jack Charlton
//Line following with delays. In-progress
//2/29/2024

void align_distance() {  // adjust the robot so the within 4.5 inches of the wall
                         //flag.write(90);
  infrared_detect();
  leftU = tempAvg[0];
  centerUR = tempAvg[1];  //when ultrasonic is 9, 10, 11 in, we can use x1 120 x2 100
  rightU = tempAvg[2];
  centerUL = tempAvg[3];
  centerU = (centerUL + centerUR) / 2;
  while ((leftU > 4.7) || (leftU < 4.3)) {  // want to be 4.5
    infrared_detect();
    leftU = tempAvg[0];
    centerUR = tempAvg[1];  //when ultrasonic is 9, 10, 11 in, we can use x1 120 x2 100
    rightU = tempAvg[2];
    centerUL = tempAvg[3];
    centerU = (centerUL + centerUR) / 2;
    if (centerU < 4) {
      backward(250);
    } else {
      if (leftU > 4.5) {
        right(500);
        backward(500);
        left(500);
        forward(500);
        stop(250);
      } else {
        left(500);
        backward(500);
        right(500);
        forward(500);
        stop(250);
      }
    }
      infrared_detect();
      leftU = tempAvg[0];
      centerUR = tempAvg[1];  //when ultrasonic is 9, 10, 11 in, we can use x1 120 x2 100
      rightU = tempAvg[2];
      centerUL = tempAvg[3];
      centerU = (centerUL + centerUR) / 2;
  }
}
