//Haley Stewart
//Jack Charlton
//Line following with delays. In-progress
//2/29/2024

void backward(int runtime) {
  frontLeft.writeMicroseconds(frontClockwise); //left cw 674
  frontRight.writeMicroseconds(2400); //right ccw 
  backLeft.writeMicroseconds(600); //cw
  backRight.writeMicroseconds(2325);
  delay(runtime);
}
