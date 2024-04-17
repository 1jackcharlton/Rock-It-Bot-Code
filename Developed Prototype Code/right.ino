//Haley Stewart
//Jack Charlton
//Line following with delays. In-progress
//2/29/2024

void right(int runtime) {
  frontLeft.writeMicroseconds(2326); //ccw
  frontRight.writeMicroseconds(2400); //ccw 
  backLeft.writeMicroseconds(counterClockwise); //ccww
  backRight.writeMicroseconds(2325); //ccw
  delay(runtime);
}
