// Import library
#include <Servo.h>
#include <Ultrasonic.h>
#include <L298N.h>
#include "esp_camera.h"
#include <WiFi.h>

// Camera
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

// Assign pins 
const unsigned int TRIG = 2;
const unsigned int ECHO_A = 3; //Echo of Front Ultrasonic
const unsigned int ECHO_B = 4; //Echo of Left Ultrasonic
const unsigned int ECHO_C = 10; //Echo of Right Ultrasonic

//Ultrasonic instance
Ultrasonic ultrasonicFront(TRIG, ECHO_A);
Ultrasonic ultrasonicLeft(TRIG, ECHO_B);
Ultrasonic ultrasonicRight(TRIG, ECHO_C);

void printSensorData() {
  Serial.print("Front: ");
  Serial.println(ultrasonicFront.read(CM));
  Serial.print("Left: ");
  Serial.println(ultrasonicLeft.read(CM));
  Serial.print("Right: ");
  Serial.println(ultrasonicRight.read(CM));
  delay(10);
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {} // Wait of serial to be ready
  Serial.println("Serial Ready");
}

void loop() {
  //Print the sensor data
  printSensorData();
}
