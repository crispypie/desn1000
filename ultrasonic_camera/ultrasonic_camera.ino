// Import library
#include <Servo.h>
#include <Ultrasonic.h>
#include <L298N.h>

// Ultrasonic pins
const unsigned int TRIG = 2;
const unsigned int ECHO_A = 3; // Echo of Front Ultrasonic
const unsigned int ECHO_B = 4; // Echo of Left Ultrasonic
const unsigned int ECHO_C = 10; // Echo of Right Ultrasonic

// Motor A pins
const unsigned int IN1_A = 7;
const unsigned int IN2_A = 8;
const unsigned int EN_A = 9;
int motorSpeedA = 0;

// Motor B pins
const unsigned int IN1_B = 12;
const unsigned int IN2_B = 13;
const unsigned int EN_B = 11;
int motorSpeedB = 0;

// Servo A pin
const unsigned int SER_A = 5;
int servoAngleA = 90;

// Servo B pin
const unsigned int SER_B = 6;
int servoAngleB = 90;

// Ultrasonic instance
Ultrasonic ultrasonicFront(TRIG, ECHO_A);
Ultrasonic ultrasonicLeft(TRIG, ECHO_B);
Ultrasonic ultrasonicRight(TRIG, ECHO_C);

// Motor instance
L298N motorA(EN_RIGHT, IN1_RIGHT, IN2_RIGHT);
L298N motorB(EN_LEFT, IN1_LEFT, IN2_LEFT);

// Servo instance
Servo servoA;
Servo servoB;

// Function prototypes
void printSensorData();
void servoInit();
void motorInit();
String getJoystickData();
void changeServoAngle(int spaceIndex, String input);
void changeMotors(int spaceIndex, String input);

void setup() {
  Serial.begin(9600); //////////////////////////////////// Not sure which baud rate to use //////////////////////////////////////
  while (!Serial) {} // Wait of serial to be ready
  Serial.println("Serial Ready");

  servoInit();
  motorInit();

  Serial.println("Initialization Complete!");
}

void loop() {
  if (Serial.available()) {
    String input = getJoystickData();
    int spaceIndex = input.indexOf(' '); // Find the index of space character

    changeServoAngle(spaceIndex, input); ///////////////////////////////// How does exactly the motor driver and servos interact /////////////////////////////////

  } else {
    Serial.println("Invalid input. Please enter two numbers separated by a space.");
  }

  // Print the sensor data
  printSensorData();
}

// Print the data from the sensors
void printSensorData() {
  Serial.print("Front: ");
  Serial.println(ultrasonicFront.read(CM));
  Serial.print("Left: ");
  Serial.println(ultrasonicLeft.read(CM));
  Serial.print("Right: ");
  Serial.println(ultrasonicRight.read(CM));
  delay(10);
}

// Initialize the servos
void servoInit() {
  // Servo A
  servoA.attach(SER_A);
  servoA.write(servoAngleA);

  // Servo B
  servoB.attach(SER_B);
  servoB.write(servoAngleB);
}

// Initialize motors
void motorInit() {
  motorA.setSpeed(motorSpeedA);
  motorB.setSpeed(motorSpeedB);
}

// Get the data from the python program
String getJoystickData() {
  String input = Serial.readStringUntil('\n'); // Read until newline
  input.trim() //Trim trailing whitespace
  return input;
}

void changeServoAngle(int spaceIndex, String input) {
  // Check if valid input, we are assuming only 2 numbers are given
  if (spaceIndex > 0) {
    String part1 = input.substring(0, spaceIndex); // Extract the first part
    String part2 = input.substring(spaceIndex + 1); // Extract the second part

    // Check if both parts are non-empty before converting to integers
    if (part1.length() > 0 && part2.length() > 0) {
      servoAngleA = part1.toInt(); // Convert the first part to an integer
      servoAngleB = part2.toInt(); // Convert the second part to an integer

      // Output the two angles
      Serial.print("Servo 1 Angle: ");
      Serial.println(servoAngleA);
      Serial.print("Servo 2 Angle: ");
      Serial.println(servoAngleB);

      // Change the angles
      servoA.write(servoAngleA); 
      servoB.write(servoAngleB);
    } else {
      Serial.println("Invalid input. Both numbers must be provided.");
    }
  } else {
    Serial.println("Invalid input. Please enter two numbers separated by a space.");
  }
}

// Change the motors speed and direction
void changeMotors(int spaceIndex, String input) {
  int motorDirectionA = 0;
  int motorDirectionB = 0;

  // Check if valid input, we are assuming only 2 numbers are given
  if (spaceIndex > 0) {
    String part1 = input.substring(0, spaceIndex); // Extract the first part
    String part2 = input.substring(spaceIndex + 1); // Extract the second part

    // Check if both parts are non-empty before converting to integers
    if (part1.length() > 0 && part2.length() > 0) {
      motorDirectionA = part1.toInt(); // Convert the first part to an integer
      motorDirectionB = part2.toInt(); // Convert the second part to an integer
      motorSpeedA = (motorDirectionA / 180) * 255;
      motorSpeedB = (motorDirectionB / 180) * 255;

      // Change the direction of the motors
      motorA.setSpeed(motorSpeedA);
      if (motorDirectionA == 90) {
        motorA.stop();
      } else if (motorDirectionA < 90) {
        motorA.backward();
      } else if (motorDirectionA > 90) {
        motorA.forward();
      }

      motorB.setSpeed(motorSpeedB);
      if (motorDirectionB == 90) { 
        motorA.stop();
      } else if (motorDirectionB < 90) {
        motorA.forward();
      } else if (motorDirectionB > 90) {
        motorA.backward();
      }

    } else {
      Serial.println("Invalid input. Both numbers must be provided.");
    }
  } else {
    Serial.println("Invalid input. Please enter two numbers separated by a space.");
  }
}

