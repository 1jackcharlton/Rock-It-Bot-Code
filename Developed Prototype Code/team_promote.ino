//Haley Stewart
//Jack Charlton
//Team promotion code to blink LEDs with a UK blue
//3/7/2024

void LEDsetup(){
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  //start up in blue?
  int r, g, b;
  r = 255;
  g = 255; //255 is off
  b = 255; //b=0 is UK blue
  analogWrite(REDPIN, r);
  analogWrite(GREENPIN, g);
  //this section needs to be repeated or put into the loop()
  analogWrite(BLUEPIN, b); //blue on
}

void team_promote_LED() { // activate LEDs for team promotion
  int r, g, b;
  r = 255;
  g = 255; //255 is off
  b = 0; //b=0 is UK blue
  analogWrite(REDPIN, r);
  analogWrite(GREENPIN, g);
  //this section needs to be repeated or put into the loop()
  analogWrite(BLUEPIN, b); //blue on
  //delay(runtime);
  //analogWrite(BLUEPIN, 255); //blue off
  //delay(runtime);
}

void team_promote_flag(){
  stop(500); 
  flag.write(130); //tilt 
  team_promote_LED(); //blue on
  delay(1000); // wait 1 sec
  analogWrite(BLUEPIN, 255); //blue off
  flag.write(0); //tilt away
  delay(500); // wait 1 sec
  team_promote_LED();
  flag.write(130); //tilt back to normal
  analogWrite(BLUEPIN, 255); //blue off
  delay(500);
  flag.write(0);
  delay(500);
  //flag.write(150); //flag horizontal
}
