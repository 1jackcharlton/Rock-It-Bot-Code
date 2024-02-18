/*
 Pixy2 Test Program

 Pixy2 Connection:
ISPC ports on Arduino and Pixy2
*/
#include <Pixy2.h>

Pixy2 pixy;

void setup() {
  Serial.begin(115200); // BAUD rate
  Serial.print("Starting...\n");
  
  pixy.init();
  pixy.setLamp(1, 1);  // upper lamp brightness, lower lamp brightness = 1
}

void loop() {
  // AUTO BLOCK DETECTOR
  //////////////////////
  int i; 
  // grab blocks
  pixy.ccc.getBlocks();
  
  // If there are detect blocks, print them
  if (pixy.ccc.numBlocks)
  {
    Serial.print("Detected ");
    Serial.println(pixy.ccc.numBlocks); // how many blocks
    for (i=0; i<pixy.ccc.numBlocks; i++) // for each block
    {
      Serial.print("  block "); 
      Serial.print(i); // which block
      Serial.print(": ");
      pixy.ccc.blocks[i].print(); //signature of the obj, x center of obj, y center of obj, width, height, tracking index, age (frames of tracked)
    }
  }
  //////////////////////
}
