//Haley Stewart
//Jack Charlton
//Line following with delays. In-progress
//2/29/2024

void stop(int runtime) {
  frontLeft.writeMicroseconds(stalled);
  frontRight.writeMicroseconds(stalled);
  backLeft.writeMicroseconds(stalled);
  backRight.writeMicroseconds(stalled);
  delay(runtime);
}
