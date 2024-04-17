//Haley Stewart
//Jack Charlton
//Get ultrasonic sensor data
//3/8/2024

int ultrasonic_detect(int trigPin[], int echoPin[]) {  // take in ultrasonic data
  int trigPin1 = trigPin[0];                            // Trigger left
  int echoPin1 = echoPin[0];                            // Echo left
  int trigPin2 = trigPin[1];                            // Trigger center
  int echoPin2 = echoPin[1];                            // Echo center
  int trigPin3 = trigPin[2];                            // Trigger right
  int echoPin3 = echoPin[2];                            // Echo right

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
  //noInterrupts();
  duration1 = pulseIn(echoPin1, HIGH);
  //interrupts(); //enter dance mode

  // Convert the time into a distance
  inches1 = (duration1 / 2) / 74;           // Divide by 74 or multiply by 0.0135
  if ((inches1 < 50) && (inches1 != 0)) {  //total length of the course with added 4" buffer length, filtering outliers
    inches1avg += inches1;
    count1 += 1;
  }
  if (count1 == 3) {  // initiate averaging
    inches1avg = inches1avg / 3;
    count1 = 0;                  // reset counter for averaging
    cm1avg = inches1avg * 2.54;  // conversion
    tempAvg[0] = inches1avg;
    inches1avg = 0;  // reset avg
  }

  // change output from void to distances, ignore prints after
  /*
  Serial.print(inches1avg);
  Serial.print("in, ");
  Serial.print(cm1avg);
  Serial.print("cm (left, avg)");
  Serial.println();
  */

  delay(10);  // 10 miliseconds

  // Ultrasonic sensor 2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  pinMode(echoPin2, INPUT);
  //noInterrupts();
  duration2 = pulseIn(echoPin2, HIGH);
  //interrupts();

  // Convert the time into a distance
  inches2 = (duration2 / 2) / 74;           // Divide by 74 or multiply by 0.0135
  if ((inches2 < 50) && (inches2 != 0)) {  //total length of the course with added 4" buffer length, filtering outliers
    inches2avg += inches2;
    count2 += 1;
  }
  if (count2 == 3) {  // initiate averaging
    inches2avg = inches2avg / 3;
    count2 = 0;                  // reset counter for averaging
    cm2avg = inches2avg * 2.54;  // conversion
    tempAvg[1] = inches2avg;
    inches2avg = 0;  // reset avg
  }

  // change output from void to distances, ignore prints after
  /*
  Serial.print(inches2avg);
  Serial.print("in, ");
  Serial.print(cm2avg);
  Serial.print("cm (center, avg)");
  Serial.println();
  */
  

  delay(10);  // delay 10 miliseconds

  // Ultrasonic sensor 3
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);

  
  pinMode(echoPin3, INPUT);
  //noInterrupts();
  duration3 = pulseIn(echoPin3, HIGH);
  //interrupts();


  // Convert the time into a distance
  inches3 = (duration3 / 2) / 74;           // Divide by 74 or multiply by 0.0135
  if ((inches3 < 50) && (inches3 != 0)) {  //total length of the course with added 4" buffer length, filtering outliers
    inches3avg += inches3;
    count3 += 1;
  }
  if (count3 == 3) {  // initiate averaging
    inches3avg = inches3avg / 3;
    count3 = 0;                  // reset counter for averaging
    cm3avg = inches3avg * 2.54;  // conversion
    tempAvg[2] = inches3avg;
    inches3avg = 0;  // reset avg
  }
  // change output from void to distances, ignore prints after
  /*
  Serial.print(inches3avg);
  Serial.print("in, ");
  Serial.print(cm3avg);
  Serial.print("cm (right, avg)");
  Serial.println();
  */

  //return tempAvg[0], tempAvg[1], tempAvg[2]; 

  delay(10);  //delay 10 miliseconds
}
