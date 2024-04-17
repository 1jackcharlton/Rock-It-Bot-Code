//Haley Stewart
//Jack Charlton
//Servo init for claws
//3/17/24

// Connection Details:
// Black - Ground
// Red - VCC
// White - APC RX to Mega TX (18)
// Green - APC TX to Mega RX (19)

// Flags to ensure messages are processed only once
// bool startMessageReceived = false;
// bool efMessageReceived = false;
// bool endMessageSent = false;

void comm_setup() {
  Serial.begin(9600); // Start serial communication for debugging
  Serial1.begin(9600); // Initialize Serial1 for communication with APC220
}

void comm_loop() {
  // Check for the "COMPETITION_START" message
  if (!startMessageReceived && Serial1.available()) {
    String incoming = Serial1.readStringUntil('\n');
    incoming.trim();
    Serial.println(incoming); // Debug print the incoming message
    
    if (incoming == "COMPETITION_START") {
      // Handle the "COMPETITION_START" message
      startMessageReceived = true;
    }
  }

  // Check for the "Finished early" message
  if (!efMessageReceived && Serial1.available()) {
    String incoming = Serial1.readStringUntil('\n');
    incoming.trim();
    Serial.println(incoming); // Debug print the incoming message
    
    if (incoming == "Finished early") {
      // Handle the "Finished early" message
      efMessageReceived = true;
    }
  }

  // Send the "Competition end" message
  if (!endMessageSent) {
    competitionEndSent();
    endMessageSent = true;
  }

  // Additional logic can be placed here, following the same pattern for other conditions
}

// Function to send the "Competition end" message
void competitionEndSent() {
  Serial1.println("We are pressing the button now");
  // Optional: Additional actions after sending the message
}