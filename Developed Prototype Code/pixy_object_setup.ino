//Haley Stewart
//Jack Charlton
//Line following with delays. In-progress
//2/29/2024

void pixy_object_setup() {
  Serial.begin (115200); // BAUD rate
  Serial.print("Starting...\n");

  pixy.init();
  //pixy.changeProg("video"); // required for (optional) RGB values
  pixy.setLamp(1, 1);  // upper lamp brightness, lower lamp brightness = 1
}
