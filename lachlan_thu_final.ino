#include <Servo.h>
#include <Ultrasonic.h>
#include <L298N.h>

// Ultrasonic sensor pins
const unsigned int TRIG_FRONT = 2; // Orange
const unsigned int TRIG_BACK = 4; // Purple
const unsigned int ECHO_FRONT = 3; // Yellow
const unsigned int TRIG_RIGHT = 5; // Grey

// Motor A pins
const unsigned int IN1_RIGHT = 8; // Orange
const unsigned int IN2_RIGHT = 9; // Red
const unsigned int EN_RIGHT = 10; // Black, extra
int motorSpeedA = 0;

// Motor B pins
const unsigned int IN1_LEFT = 12; // Brown 
const unsigned int IN2_LEFT = 13; // Black
const unsigned int EN_LEFT = 11; // Brown, extra
int motorSpeedB = 0;

// Servo A pin
const unsigned int SER_A = 6;
int servoAngleA = 90;

// Servo B pin
const unsigned int SER_B = 7;
int servoAngleB = 90;

// Ultrasonic instances
Ultrasonic ultrasonicFront(TRIG_FRONT, ECHO_FRONT);
Ultrasonic ultrasonicLeft(TRIG_LEFT, ECHO_LEFT);
Ultrasonic ultrasonicRight(TRIG_BACK, TRIG_RIGHT);

// Motor instances
L298N motorA(EN_RIGHT, IN1_RIGHT, IN2_RIGHT);  // Fixed L298N motor initialization
L298N motorB(EN_LEFT, IN1_LEFT, IN2_LEFT);    // Fixed L298N motor initialization

// Servo instances
Servo servoA;
Servo servoB;

// Function prototypes
void printSensorData();
void servoInit();
void motorInit();
void changeServoAngle(char input);
void changeMotors(char input);

void printSensorData() {
  Serial.print("Front: ");
  Serial.println(ultrasonicFront.read(CM));
  delay(500);
  Serial.print("Left: ");
  Serial.println(ultrasonicLeft.read(CM));
  delay(500);
  Serial.print("Right: ");
  Serial.println(ultrasonicRight.read(CM));
  delay(500);
}

void servoInit() {
  servoA.attach(SER_A);
  servoB.attach(SER_B);
  servoA.write(servoAngleA);  // Initialize servo A to 90 degrees
  servoB.write(servoAngleB);  // Initialize servo B to 90 degrees
}

void motorInit() {
  pinMode(IN1_RIGHT, OUTPUT);
  pinMode(IN2_RIGHT, OUTPUT);
  pinMode(EN_RIGHT, OUTPUT);
  pinMode(IN1_LEFT, OUTPUT);
  pinMode(IN2_LEFT, OUTPUT);
  pinMode(EN_LEFT, OUTPUT);

  motorSpeedA = 0;
  motorSpeedB = 0;
}

void changeServoAngle(char input) {
  // Servo control based on user input
  if (input == 'A') {
    servoAngleA = (servoAngleA == 0) ? 90 : 0;
    servoA.write(servoAngleA);
    Serial.print("Servo A set to: ");
    Serial.println(servoAngleA);
  } 
  else if (input == 'B') {
    servoAngleB = (servoAngleB == 0) ? 90 : 0;
    servoB.write(servoAngleB);
    Serial.print("Servo B set to: ");
    Serial.println(servoAngleB);
  }
}

void changeMotors(char input) {
  // Motor control based on user input
  switch(input) {
    case 'F': // Move Forward
      motorSpeedA = 100;
      motorSpeedB = 100;
      motorA.setSpeed(motorSpeedA);
      motorB.setSpeed(motorSpeedB);
      motorA.forward();
      motorB.forward();
      Serial.println("Moving Forward");
      break;
    case 'B': // Move Backward
      motorSpeedA = 100;
      motorSpeedB = 100;
      motorA.setSpeed(motorSpeedA);
      motorB.setSpeed(motorSpeedB);
      motorA.backward();
      motorB.backward();
      Serial.println("Moving Backward");
      break;
    case 'L': // Turn Left
      motorSpeedA = 100;
      motorSpeedB = 100;
      motorA.setSpeed(motorSpeedA);
      motorB.setSpeed(motorSpeedB);
      motorA.backward();
      motorB.forward();
      Serial.println("Turning Left");
      break;
    case 'R': // Turn Right
      motorSpeedA = 100;
      motorSpeedB = 100;
      motorA.setSpeed(motorSpeedA);
      motorB.setSpeed(motorSpeedB);
      motorA.forward();
      motorB.backward();
      Serial.println("Turning Right");
      break;
    case 'S': // Stop
      motorSpeedA = 0;
      motorSpeedB = 0;
      motorA.setSpeed(motorSpeedA);
      motorB.setSpeed(motorSpeedB);
      motorA.stop();
      motorB.stop();
      Serial.println("Motors Stopped");
      break;
    default:
      Serial.println("Invalid motor command");
      break;
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {}  // Wait for serial to be ready
  Serial.println("Serial Ready");

  servoInit();
  motorInit();

  Serial.println("Initialization Complete!");
  Serial.println("Control the motors and servos with the following commands:");
  Serial.println("Motors: F (Forward), B (Backward), L (Left), R (Right), S (Stop)");
  Serial.println("Servos: A (Toggle Servo A), B (Toggle Servo B)");
}

void loop() {
  if (Serial.available()) {
    char input = Serial.read();  // Read the incoming character
    if (input == 'A' || input == 'B') {
      changeServoAngle(input);
    }
    else if (input == 'F' || input == 'B' || input == 'L' || input == 'R' || input == 'S') {
      changeMotors(input);
    }
  }

  // Optionally print the sensor data in the loop
  printSensorData();
}
