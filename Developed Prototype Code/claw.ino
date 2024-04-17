//Haley Stewart
//Jack Charlton
//Functions for claw mechanism.
//3/17/24

void openClaws(int position) {
  leftClaw.write(position); //TODO find value
  centerClaw.write(position);  //22
  rightClaw.write(position);
}

void closeClaws(int position) {
  leftClaw.write(position); //TODO find value
  centerClaw.write(position); //800
  rightClaw.write(position);
}

void lowerClaws(int runtime) {
  clawTrack.writeMicroseconds(1300); //TODO find value, 1500 stall 500?
  delay(runtime); //TODO find time to stop raising/lowering
  clawTrack.writeMicroseconds(stalled);
}

void raiseClaws(int runtime) {
  clawTrack.writeMicroseconds(1725); //TODO find value //clockwise raise 2500
  delay(runtime);
  clawTrack.writeMicroseconds(stalled);
}