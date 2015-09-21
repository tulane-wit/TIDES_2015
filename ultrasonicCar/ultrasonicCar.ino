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
const int enablePin1 = 8;    // H-bridge enable pin 1
const int enablePin2 = 10;    // H-bridge enable pin 2
int analogMotorVoltage = 50;
int maxDelay = 500;

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  startCar();
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void loop() {
  delay(50);    // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.  
  if (getDistance() < 10 ){
    stopCar();
    turnInPlaceRight(90);
  }
  else {
    moveCar(10);
  }
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void turnInPlaceLeft(int volts) {
  // EXERCISE: Write this function
  // LESSON: How to get car to turn in place
}

void turnInPlaceRight(int volts) {
  // EXERCISE: Write this function

}

void startCar() {
  // EXERCISE: Write this function
  // set enablePin high so that motor can turn on:

}

void stopCar() {
  // EXERCISE: Write this function
}

void moveCar(int carVelocity) {
  // EXERCISE: Write this function
  // how long, how fast

}

void moveForward(int carSpeed) {
  // EXERCISE: Write this function

}

void moveBackward(int carSpeed) {
  // EXERCISE: Write this function

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

