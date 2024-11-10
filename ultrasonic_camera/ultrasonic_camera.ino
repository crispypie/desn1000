// Import library
#include <Servo.h>
#include <Ultrasonic.h>
#include <L298N.h>

// Ultrasonic sensor pins
const unsigned int TRIG_FRONT = 2; // Orange
const unsigned int TRIG_BACK = 4; // Purple
const unsigned int ECHO_FRONT = 3; // Yellow
const unsigned int ECHO_BACK = 5; // Grey

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
Ultrasonic ultrasonicBack(TRIG_BACK, ECHO_BACK);

// Motor instances
L298N motorA(EN_RIGHT, IN1_RIGHT, IN2_RIGHT);  // Fixed L298N motor initialization
L298N motorB(EN_LEFT, IN1_LEFT, IN2_LEFT);    // Fixed L298N motor initialization

// Servo instances
Servo servoA;
Servo servoB;

// Function prototypes
void servoInit();
void motorInit();
String getJoystickData();
void printSensorData();
void changeServoAngle(String input);
void changeMotors(int spaceIndex, String input);

void setup() {
  Serial.begin(9600); 
  while (!Serial) {} // Wait of serial to be ready
  Serial.println("Serial Ready");

  servoInit();
  motorInit();

  Serial.println("Initialization Complete!");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readString();

    if (isAlpha(input[0])) {
      changeServoAngle(input);
    } else {
      int spaceIndex = input.indexOf(' ');
      changeMotors(input, spaceIndex);
    }
  }
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

// Print the data from the sensors
void printSensorData() {
  Serial.print("Front: ");
  Serial.println(ultrasonicFront.read(CM));
  Serial.print("Back: ");
  Serial.println(ultrasonicBack.read(CM));
  delay(1000);
}

void changeServoAngle(String input) {
  if (input == "U") {
    servoAngleA += servoAngle >= 180 ? 0 : 10;
    servoA.write(servoAngleA);
  } else if (input == "D") {
    servoAngleA -= servoAngle <= 0 ? 0 : 10;
    servoA.write(servoAngleA);
  } else if (input == "R") {
    servoAngleB += servoAngle >= 180 ? 0 : 10;
    servoB.write(servoAngleB);
  } else if (input == "L") {
    servoAngleB -= servoAngle <= 0 ? 0 : 10;
    servoB.write(servoAngleB);
  }
}

// Change the motors speed and direction
void changeMotors(String input, int spaceIndex) {
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

      // Change motor A
      if (motorDirectionA == 90) {
          motorSpeedA = 0;
          motorA.setSpeed(motorA);
          motorA.stop();
          Serial.println("Stops");
      } else if (motorDirectionA > 90) {
          motorA.setSpeed(motorSpeedA);
          motorA.forward();
          Serial.println("Going forwards");
      } else if (motorDirectionA < 90) {
          motorA.setSpeed(motorSpeedA);
          motorA.backward();
          Serial.println("Going backwards");
      } else {
        Serial.println("Invalid Number for input");
      }

      // Change motor B
      if (motorDirectionB == 90) {
          motorSpeedB = 0;
          motorB.setSpeed(motorSpeedB);
          motorB.stop();
          Serial.println("Stops");
      } else if (motorDirectionB > 90) {
          motorB.setSpeed(motorSpeedB);
          motorB.forward();
          Serial.println("Going forwards");
      } else if (motorDirectionB < 90) {
          motorB.setSpeed(motorSpeedB);
          motorB.backward();
          Serial.println("Going backwards");
      } else {
        Serial.println("Invalid Number for input");
      }

      // Print the integers
      Serial.print("First integer: ");
      Serial.println(motorDirectionA);
      Serial.print("Second integer: ");
      Serial.println(motorDirectionB);
      delay(1000);

    } else {
      Serial.println("Invalid input. Both numbers must be provided.");
    }
  } else {
    Serial.println("Invalid input. Please enter two numbers separated by a space.");
  }
}

