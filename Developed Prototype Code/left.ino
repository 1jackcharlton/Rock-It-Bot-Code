//Haley Stewart
//Jack Charlton
//Line following with delays. In-progress
//2/29/2024

void left(int runtime) { //correct, moves fast
  frontLeft.writeMicroseconds(frontClockwise); //clockwise
  frontRight.writeMicroseconds(600); //clockwise
  backLeft.writeMicroseconds(600); //clockwww
  backRight.writeMicroseconds(675); //clockwise
  delay(runtime);
}
