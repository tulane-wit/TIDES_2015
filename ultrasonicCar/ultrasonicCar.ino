// ---------------------------------------------------------------------------
// Download NewPing Library:
// https://code.google.com/p/arduino-new-ping/downloads/list
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

const int motor1Pin1 = 3;    // H-bridge pin 2, 1A
const int motor1Pin2 = 5;    // H-bridgepin 7, 2A
const int motor2Pin1 = 6;    // H-bridge pin 10, 3A
const int motor2Pin2 = 9;    // H-bridge pin 15, 4A
const int enablePin = 4;    // H-bridge enable pin
int analogMotorVoltage = 50;
int maxDelay = 500;

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  startCar();
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void loop() {
  delay(50);    // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.  
  if (getDistance() < 10 ){
    stopCar();
    turnInPlace(90);
  }
  else {
    moveCar(10);
  }
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void turnInPlace(int rotation) {
  // turn motor for a specified amount of time
  int turnTime = map(abs(rotation)%360, 0, 360, 0, maxDelay);
  // OR turn motor at a specific voltage to maxVoltage (if that equals a full rotation)
  // int turnTime = map(abs(rotation)%360, 0, 360, 0, maxVoltage);
  startCar();
  if(rotation < 0) {
    turnInPlaceLeft(analogMotorVoltage);
    delay(turnTime); 
    stopCar();  
  }
  else {
    turnInPlaceRight(analogMotorVoltage);
    delay(turnTime);  
    stopCar();  
  }
}

void turnInPlaceLeft(int volts) {
  // EXERCISE: Write this function
  // LESSON: How to get car to turn in place
  analogWrite(motor1Pin1, 0);   // set leg 1 of the H-bridge low
  analogWrite(motor1Pin2, volts);  // set leg 2 of the H-bridge high 
  // move motors in opposite directions
  analogWrite(motor2Pin1, volts);  
  analogWrite(motor2Pin2, 0);
}

void turnInPlaceRight(int volts) {
  // EXERCISE: Write this function
  analogWrite(motor1Pin1, volts);  
  analogWrite(motor1Pin2, 0); 
  analogWrite(motor2Pin1, 0); 
  analogWrite(motor2Pin2, volts);
}

void startCar() {
  // EXERCISE: Write this function
  // set enablePin high so that motor can turn on:
  digitalWrite(enablePin, HIGH);
}

void stopCar() {
  // EXERCISE: Write this function
  digitalWrite(enablePin, LOW);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void moveCar(int carVelocity) {
  // EXERCISE: Write this function
  // how long, how fast
  if(carVelocity > 0) moveForward(carVelocity%255);
  else moveBackward(abs(carVelocity)%255);
}

void moveForward(int carSpeed) {
  analogWrite(motor1Pin1, carSpeed);  
  analogWrite(motor1Pin2, 0); 
  analogWrite(motor2Pin1, carSpeed); 
  analogWrite(motor2Pin2, 0);
}

void moveBackward(int carSpeed) {
  analogWrite(motor1Pin1, 0);  
  analogWrite(motor1Pin2, carSpeed); 
  analogWrite(motor2Pin1, 0); 
  analogWrite(motor2Pin2, carSpeed);
}

void printPingTime() {
  Serial.print("Ping: ");
  Serial.print(getDistance()); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
}

unsigned int getDistance() {
  // get ping time in microseconds (uS) and divide to get centimeters
  return sonar.ping() / US_ROUNDTRIP_CM;
}

