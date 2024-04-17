//Haley Stewart
//Jack Charlton
//Get ultrasonic sensor data
//3/8/2024

void infrared_detect() {  // take in ultrasonic data
  // IR sensor 1 left
  float volts1 = analogRead(pin1)*0.0048828125; // val from sensor
  float distance1 = 13*pow(volts1, -1); // datasheet 
  if (distance1 <= 50 && (distance1 != 0)){ // ignore > 30 cm readings
    inches1 = distance1 * 0.393701; // cm to inches
    inches1avg += inches1;
    count1 += 1;
  } else {
    distance1 = 0;
  }

  if (count1 == 3) {  // initiate averaging 
    inches1avg = inches1avg / 3;
    count1 = 0;                  // reset counter for averaging
    tempAvg[0] = inches1avg;
    Serial.print("left: ");
    Serial.println(inches1avg);
    inches1avg = 0;  // reset avg

  }

  delay(10);  // 10 miliseconds

  float volts2 = analogRead(pin2)*0.0048828125; // val from sensor center right
  float distance2 = 13*pow(volts2, -1); // datasheet 
  if (distance2 <= 50 && (distance2 != 0)){ // ignore > 30 cm readings
    inches2 = distance2 * 0.393701; // cm to inches
    inches2avg += inches2;
    count2 += 1;
  } else {
    distance2 = 0;
  }

  if (count2 == 3) {  // initiate averaging
    inches2avg = inches2avg / 3;
    count2 = 0;                  // reset counter for averaging
    //inches2avg = inches2avg*10/12; // compensate for calibration
    tempAvg[1] = inches2avg;
    Serial.print("center right: ");
    Serial.println(inches2avg);
    inches2avg = 0;  // reset avg

  }

  delay(10);  // 10 miliseconds

  float volts3 = analogRead(pin3)*0.0048828125; // val from sensor right
  float distance3 = 13*pow(volts3, -1); // datasheet 
  
  if ((distance3 <= 50) && (distance3 != 0)){ // ignore > 30 cm readings
    inches3 = distance3 * 0.393701; // cm to inches
    inches3avg += inches3;
    count3 += 1;
  } else {
    distance3 = 0;
  }

  if (count3 == 3) {  // initiate averaging
    inches3avg = inches3avg / 3;
    count3 = 0;                  // reset counter for averaging
    //inches3 = 11/17*inches3; // compensate for calibration
    tempAvg[2] = inches3avg;
    Serial.print("right: ");
    Serial.println(inches3avg);
    inches3avg = 0;  // reset avg
  }

  delay(10);  // 10 miliseconds

  float volts4 = analogRead(pin4)*0.0048828125; // val from sensor center left
  float distance4 = 13*pow(volts4, -1); // datasheet 
  if (distance4 <= 50 && (distance4 != 0)){ // ignore > 50 cm readings
    inches4 = distance4 * 0.393701; // cm to inches
    inches4avg += inches4;
    count4 += 1;
  } else {
    distance4 = 0;
  }

  if (count4 == 3) {  // initiate averaging
    inches4avg = inches4avg / 3;
    count4 = 0;                  // reset counter for averaging
    tempAvg[3] = inches4avg;
    Serial.print("center left: ");
    Serial.println(inches4avg);
    inches4avg = 0;  // reset avg
  }

  delay(10);  // 10 miliseconds
}
