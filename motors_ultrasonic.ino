// Import library
#include <Servo.h>
#include <Ultrasonic.h>
#include <L298N.h>

// Define pins

  // Motor A
const unsigned int IN1_A = 7;
const unsigned int IN2_A = 8;
const unsigned int EN_A = 9;

  // Motor B
const unsigned int IN1_B = 12;
const unsigned int IN2_B = 13;
const unsigned int EN_B = 11;

  // Servo A
const unsigned int SER_A = 5;

  // Servo B
const unsigned int SER_B = 6;

  // Ultrasonic A
const unsigned int TRIG_A = 2;
const unsigned int ECHO_A = 3;

// Create motor instance
L298N motorA(EN_A, IN1_A, IN2_A);
L298N motorB(EN_B, IN1_B, IN2_B);

// Servo Objects
Servo servoA;
Servo servoB;

// Ultrasonic instance
Ultrasonic ultrasonicA(TRIG_A, ECHO_A);

// Code to run once on setup
void setup() {
  Serial.begin(9600);
  while (!Serial) {} // Wait of serial to be ready
  Serial.println("Serial Ready");

  // Initialize Motors
  motorA.setSpeed(100);
  motorB.setSpeed(100);

  // Initialize Servos
    // Servo A
  servoA.attach(SER_A);
  servoA.write(90); // set 90 degrees
    // Servo A
  servoB.attach(SER_B);
  servoB.write(90); // set 90 degrees

  Serial.println("Initialization Complete");
}

// Code to run repeatedly
void loop() {
  Serial.println(ultrasonicA.read());
  motorA.backward();
  motorB.forward();
  servoA.write(70);
  servoB.write(70);
  delay(3000);
  motorA.forward();
  motorB.backward();
  servoA.write(120);
  servoB.write(120);
  delay(3000);
}


