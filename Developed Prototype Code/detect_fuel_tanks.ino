//Haley Stewart
//Jack Charlton
//Line following with delays. In-progress
//2/29/2024

void detect_fuel_tanks() {  // find the fuel tanks using Pixy
  // feature extraction
  far_x_center = 0;      // shortest distance so all block centers necessarily less than it
  short_x_center = 315;  // farthest distance so all block centers necessarily less than it
  far_block_index = -1;     // init val nonsensical to show update of index
  short_block_index = -1;   // ^
  biggest_area = 0;         // ^
  biggest_block_index = -1;  // which block is biggest
  pixy.ccc.getBlocks();  // grab blocks

  for (index_block = 0; index_block < pixy.ccc.numBlocks; index_block++) {  // for each block
    // Serial.print("  block ");
    // Serial.print(i); // which block
    // Serial.print(": ");
    if (pixy.ccc.blocks[index_block].m_signature == 1) {                                             // fuel tank is first signature
      int temp_area = pixy.ccc.blocks[index_block].m_width * pixy.ccc.blocks[index_block].m_height;  //
      if (temp_area < 1000) { // area of fuel tanks = 1000, false posive is like 6000
        // find furthest block distance
        if (pixy.ccc.blocks[index_block].m_x > far_x_center) {
          far_block_index = index_block;                    // which block is farthest right
          far_x_center = pixy.ccc.blocks[index_block].m_x;  // store current farthest distance
        }
        if (pixy.ccc.blocks[index_block].m_x < short_x_center) {
          short_block_index = index_block;                    // which block is farthest right
          short_x_center = pixy.ccc.blocks[index_block].m_x;  // store current farthest distance
        }
        if (temp_area > biggest_area) {
          biggest_block_index = index_block;  // set block index
          biggest_area = temp_area;           // set max area of block
        }
      }
    }  //signature of the obj, x center of obj, y center of obj, width, height, tracking index, age (frames of tracked)
  }

  //print
  // if (pixy.ccc.numBlocks) {
  //   Serial.println(pixy.ccc.numBlocks);
  //   for (int i = 0; i < pixy.ccc.numBlocks; i++) {
  //     Serial.print("  block ");
  //     Serial.print(i);
  //     Serial.print(": ");
  //     pixy.ccc.blocks[i].print();
  //     delay(1000);
  //   }
  // }

  //delta_x_center = far_x_center - short_x_center; // find how far apart farthest left and farthest right tanks are from each other
}
