//Haley Stewart
//Jack Charlton
//Setup Ultrasonic sensors
//2/29/2024

void ultrasonic_setup(int trigPin[], int echoPin[]) { // take in ultrasonic data
  //Serial Port begin
 int trigPin1 = trigPin[0]; // Trigger left
 int echoPin1 = echoPin[0]; // Echo left
 int trigPin2 = trigPin[1]; // Trigger center
 int echoPin2 = echoPin[1]; // Echo center
 int trigPin3 = trigPin[2]; // Trigger right
 int echoPin3 = echoPin[2]; // Echo right

 Serial.begin (115200); // BAUD rate
 Serial.print("Starting...\n");

 //Define inputs and outputs
 pinMode(trigPin1, OUTPUT);
 pinMode(echoPin1, INPUT);
 pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT);
 pinMode(trigPin3, OUTPUT);
 pinMode(echoPin3, INPUT);
}
