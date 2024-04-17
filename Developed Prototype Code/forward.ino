//Haley Stewart
//Jack Charlton
//Line following with delays. In-progress
//2/29/2024
//TODO

void forward(int runtime) {
  frontLeft.writeMicroseconds(2326); //left ccw 2326
  frontRight.writeMicroseconds(550); //right clockwise is  600
  backLeft.writeMicroseconds(counterClockwise); //cclockwise is 2400
  backRight.writeMicroseconds(625); //675
  delay(runtime);
}

void slow(int runtime) {
  frontLeft.writeMicroseconds(1750); //left ccw decrease is slower
  frontRight.writeMicroseconds(1200); //right clockwise is 500 //600 //1500 increase is slower
  backLeft.writeMicroseconds(1850); //cclockwise is 2500 /2400
  backRight.writeMicroseconds(1275); //clockwise
  delay(runtime);
}
