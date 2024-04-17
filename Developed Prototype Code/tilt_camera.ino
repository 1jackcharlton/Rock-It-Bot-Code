//Haley Stewart
//Jack Charlton
//Line following with delays. In-progress
//2/29/2024

void tilt_camera() { // adjust the camera servo
  no_vector_count = no_vector_count + 1; // counter of no vector goes up
  stop(1000); //needs to be changed to stop indefinetly?
  tilt.write(120); //tilt down
  delay(1500); // wait 1.5 sec
  tilt.write(110); //return to normal tilt
}
