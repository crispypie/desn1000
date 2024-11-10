#include <Servo.h>
#include <Ultrasonic.h>
#include <L298N.h>

// ALLOCATE PINS

// Motor A pins
const unsigned int IN1_RIGHT = 8; // Orange
const unsigned int IN2_RIGHT = 9; // Red
const unsigned int EN_RIGHT = 10; // Black, extra
int motorSpeedRight = 0;

// Motor B pins
const unsigned int IN1_LEFT = 12; // Brown 
const unsigned int IN2_LEFT = 13; // Black
const unsigned int EN_LEFT = 11; // Brown, extra
int motorSpeedLeft = 0;

// Servo A pin (arm alignment)
const unsigned int SER_ARM = 6;
int servoAngleArm = 90;

// Servo B pin (gripper open/close)
const unsigned int SER_GRIP = 7;
int servoAngleGrip = 90;

// Ultrasonic sensor pins
const unsigned int TRIG_FRONT = 2; // Orange
const unsigned int ECHO_FRONT = 3; // Yellow

const unsigned int TRIG_REAR = 4; // Purple
const unsigned int ECHO_REAR = 5; // Grey

// SET UP INSTANCES

// Motor instances
L298N motorRight(EN_RIGHT, IN1_RIGHT, IN2_RIGHT);
L298N motorLeft(EN_LEFT, IN1_LEFT, IN2_LEFT); 

// Servo instances
Servo servoArm; // Pins attached in servoInit
Servo servoGrip; // Pins attached in servoInit

// Ultrasonic instances
Ultrasonic ultrasonicFront(TRIG_FRONT, ECHO_FRONT);
Ultrasonic ultrasonicRear(TRIG_REAR, ECHO_REAR);

// FUNCTION_PROTOYPES

void printSensorData();
void servoInit();
void motorInit();
void changeServoAngle(char input);
void changeMotors(char input);
void help();

// FUNCTIONS

void printSensorData() {
  Serial.print("---------\n");

  Serial.print("Front: ");
  Serial.println(ultrasonicFront.read(CM));

  Serial.print("Rear: ");
  Serial.println(ultrasonicRear.read(CM));

  delay(1000);
}

void servoInit() {
  servoArm.attach(SER_ARM); 
  servoGrip.attach(SER_GRIP);
  servoArm.write(servoAngleArm);  
  servoGrip.write(servoAngleGrip); 
}

void motorInit() {
  motorRight.setSpeed(0);
  motorLeft.setSpeed(0);
}

void changeServoAngle(char input) {
  // Servo control based on user input
  if (input == 'F') {
    if (servoAngleArm != 0) {
      servoAngleArm = servoAngleArm -= 15;
      servoArm.write(servoAngleArm);
      Serial.print("\n========================\n");
      Serial.print("Arm set to: ");
      Serial.println(servoAngleArm);
      Serial.print("========================\n");
    } else {
      Serial.print("\n========================\n");
      Serial.print("Arm cannot be lowered further.\n");
      Serial.print("========================\n");
    }
  } else if (input == 'R') {

  } else if (input == 'B') {
    servoAngleGrip = (servoAngleGrip == 0) ? 90 : 0;
    servoGrip.write(servoAngleGrip);
    Serial.print("Servo B set to: ");
    Serial.println(servoAngleGrip);
  }
}

void changeMotors(char input) {
  // Motor control based on user input
  switch(input) {
    case 'f': // Move Forward
      motorSpeedRight = 100;
      motorSpeedLeft = 100;
      motorRight.setSpeed(motorSpeedRight);
      motorLeft.setSpeed(motorSpeedLeft);
      motorRight.forward();
      motorLeft.forward();
      Serial.println("Moving Forward");
      break;
    case 'b': // Move Backward
      motorSpeedRight = 100;
      motorSpeedLeft = 100;
      motorRight.setSpeed(motorSpeedRight);
      motorLeft.setSpeed(motorSpeedLeft);
      motorRight.backward();
      motorLeft.backward();
      Serial.println("Moving Backward");
      break;
    case 'l': // Turn Left
      motorSpeedRight = 100;
      motorSpeedLeft = 100;
      motorRight.setSpeed(motorSpeedRight);
      motorLeft.setSpeed(motorSpeedLeft);
      motorRight.backward();
      motorLeft.forward();
      Serial.println("Turning Left");
      break;
    case 'r': // Turn Right
      motorSpeedRight = 100;
      motorSpeedLeft = 100;
      motorRight.setSpeed(motorSpeedRight);
      motorLeft.setSpeed(motorSpeedLeft);
      motorRight.forward();
      motorLeft.backward();
      Serial.println("Turning Right");
      break;
    default:
      Serial.println("Invalid motor command");
      break;
  }
}

void help() {
  Serial.println("Welcome to the tabulator user interface!");

  Serial.println("\nMotor control:");
    Serial.println("\t- Forward (f)");
    Serial.println("\t- Back (b)");
    Serial.println("\t- Right (r)");
    Serial.println("\t- Left (l)");

  Serial.println("\n\nArm control:");
    Serial.println("\t- Up (full extension) (u)");
    Serial.println("\t- Down (full extension) (d)");
    Serial.println("\t- Up (incrimental) (ui)");
    Serial.println("\t- Down (incrimental) (di)");

  Serial.println("\n\nGripper control:");
    Serial.println("\t- Open (full extension) (o)");
    Serial.println("\t- Close (full extension) (c)");
    Serial.println("\t- Open (incrimental) (oi)");
    Serial.println("\t- Close (incrimental) (ci)");
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {}  // Wait for serial to be ready
  Serial.println("Serial Ready");

  servoInit();
  motorInit();

  Serial.println("Initialization Complete!");
  help();
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    if (input == "f" || input == "b" || input == "r" || input == "l") {
      changeMotors(input);
    }
    else if (input == "u" || input == "d" || input == "ui" || input == "di") {
      changeServoAngle(input);
    }
    else if (input == 'H') {
      help();
    } 
    else if (input == 'S') {
      printSensorData();
    }
  }

  // Optionally print the sensor data in the loop
  // printSensorData();
}
