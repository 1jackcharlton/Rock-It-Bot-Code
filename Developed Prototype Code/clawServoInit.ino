//Haley Stewart
//Jack Charlton
//Servo init for claws
//3/17/24

void clawServoInit() { //Claw mechanism init
  leftClaw.attach(servoPinLC);
  centerClaw.attach(servoPinCC);
  rightClaw.attach(servoPinRC);
  clawTrack.attach(servoPinClawPulley);
  //TODO: start the servos closed?
  //closeClaws();
}
