//Haley Stewart
//Jack Charlton
// adjust the robot so the ultrasonic distances between the walls and robot are the same
//3/8/2024

void adjust_robot_ultrasonic(long leftU, long centerU, long rightU) {
  // if (leftU && rightU == 3) { //if left and right are in middle, center is big we are good
  //   forward(5);
  // }

  int dt = 30; // amount of time to run the motors
  
  if ((millis() > 4500) && (leftU != 0) && (rightU != 0) && (centerU != 0)) {  //run the robot to the end to test turn, make sure readings are not 0
      if (centerU < 7 && rightU < 6) {
        backward(dt);
        left(dt);
      } else if (centerU < 7 && leftU < 6) {
        backward(dt);
        right(dt);
      } else if (leftU < 6) {  // 7in to wall from sensors while robot is on center line
        right(dt);
      } else if (rightU < 6) {  // 7in to wall from sensors while robot is on center line //TODO add != 0
        left(dt); //this
      } else if (centerU < 6) {
        //stop(1000);
        backward(dt);
        left(dt);
      }
      else {
        forward(dt);
      }
    
    // if (switcht == 0){//time not recorded
    //   switcht = 1; // first time running, initialization of time period
    //   time_rec = millis(); // record time period
    // }
    // if ((switcht == 1) && (millis() - time_rec > 3000)){ // if time has been recorded and time passed is 2 seconds
    //   stop(1000); //stop for 2 seconds?
    //   switcht = 0; // let new time period be recorded
    // }
  }
}
