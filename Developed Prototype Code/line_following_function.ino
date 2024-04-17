//Haley Stewart
//Jack Charlton
//Line following with delays. In-progress
//2/29/2024

void line_following_function() {
  timeSinceStart = millis(); //update the time since start repeatedly
  int8_t res;
  int32_t error;
  int xl = -20; //-20
  int xr = 20; //20
  
  // Get latest data from Pixy, including main vector, new intersections and new barcodes.
  res = pixy.line.getMainFeatures();
  //int Vector = pixy.line.getAllFeatures(1);
  Serial.print(res);
  //delay(100);

 //if error or nothing detected, stop motors
  if (res <= 0) {
    // tilt the camera to try to find the line
    tilt_camera();

    // back up and try to find the line
    if (no_vector_count == 3){// no vector for 3 consecutive tries
      stop(1000); //needs to be changed to stop indefinetly?
      backward(1000);
      stop(1000);
      forward(500);
      no_vector_count = 0;
    }
    return;
  }

  if (res&LINE_VECTOR)
  {
    int delta_x = pixy.line.vectors->m_x1 - pixy.line.vectors->m_x0; //assign values from res for the change in x values
    //float delta_x = pixy.line.vectors[0].m_x0; //get bottom of vector
    int y0 = pixy.line.vectors->m_y0;
    int y1 = pixy.line.vectors->m_y1;
    
    // Calculate heading error with respect to m_x1, which is the far-end of the vector,
    // the part of the vector we're heading toward.
    error = (int32_t)pixy.line.vectors->m_x1 - (int32_t)X_CENTER;

    if (y1 > y0) { //the vector is going from head to tail instead of tail to head. Flip vector 
      delta_x = -delta_x;
    }

    pixy.line.vectors->print();

    // If vector is heading away and down from us (arrow pointing up), or if should continue forward until intersection
    if (((delta_x > xl) && (delta_x < xr)) || (Lswitch == 1) || (Rswitch == 1)) //implement line adjust later
    {
      forward(5); //5ms 
      //slow down a little if intersection is present so we don't miss it
    }
    else if (delta_x < xl) { //if the line is pointing to the left
      if (Lswitch == 0){ //switch var == 0 means left vector's initial detection
        t1L = millis(); // time 1 left
        Lswitch = 1; //switch var == 1 means left vector is not newly detected
      }
    }
    else if (delta_x > xr) { //if the line is pointing to the right
      if (Rswitch == 0){//switch var == 0 means right vector's initial detection
        t1R = millis(); // time 1 right
        Rswitch = 1;//switch var == 1 means right vector is not newly detected
      }
    }

    if ((timeSinceStart - t1L > 2500)&&(Lswitch == 1)) { //take a snapshot of t1 and compare to the running clock (1 and a half seconds)
      left(5); // logic to wait until on top of the turn above full 90 degree
      //vector_ignore = 1; // if 1 then ignore vectors until fully turned 
      // add logic to make a full 90 degree turn and ignore vector until turn complete
      Lswitch = 0;// reset Lswitch
    }

    if ((timeSinceStart - t1R > 2500)&&(Rswitch == 1)) { //take a snapshot of t1 and compare to the running clock
      right(5);// logic to wait until on top of the turn above full 90 
      //vector_ignore = 1; // if 1 then ignore vectors until fully turned 
      Rswitch = 0;// reset Rswitch
      // maybe add delay
    } 
  }
}
