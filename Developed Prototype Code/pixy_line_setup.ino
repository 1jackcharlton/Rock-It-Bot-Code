//Haley Stewart
//Jack Charlton
//Line following with delays. In-progress
//2/29/2024

void pixy_line_setup()
{
  Serial.begin(115200);
  Serial.print("Starting...\n");

  // initialize the pixy object
  pixy.init();
  // Full brightness
  pixy.setLamp(1, 1);
  // Change to line tracking program
  pixy.changeProg("line");
  // instruct the pixy to follow lighter lines on darker backgrounds and not vice versa
  pixy.line.setMode(LINE_MODE_WHITE_LINE);
}
