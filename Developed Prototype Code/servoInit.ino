//Haley Stewart
//Jack Charlton
//Line following with delays. In-progress
//2/29/2024

void servoInit() {
  //Initialize servos
  frontLeft.attach(servoPinFL);
  frontRight.attach(servoPinFR);
  backLeft.attach(servoPinBL);
  backRight.attach(servoPinBR);
  tilt.attach(servoPinTilt);
  tilt.write(110); //going down in number goes backward 110
  flag.attach(servoPinFlag);
}
