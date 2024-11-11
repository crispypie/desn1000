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
int armAngle = 90;

// Servo B pin (gripper open/close)
const unsigned int SER_GRIP = 7;
int gripperAngle = 90;

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
Servo servoGripper; // Pins attached in servoInit

// Ultrasonic instances
Ultrasonic ultrasonicFront(TRIG_FRONT, ECHO_FRONT);
Ultrasonic ultrasonicRear(TRIG_REAR, ECHO_REAR);

// FUNCTION_PROTOYPES

void printSensorData();
void servoInit();
void motorInit();
void changeArmAngle(String input);
void changeGripperAngle(String input);
void changeMotors(String input, int speed);
void automatedMotors(String input);
void fullAutomation();
void help();

// FUNCTIONS

void printSensorData() {
  Serial.print("---------\n");

  Serial.print("Front: ");
  Serial.print(ultrasonicFront.read(CM));
  Serial.print(" cm");

  Serial.print("\nRear: ");
  Serial.print(ultrasonicRear.read(CM));
  Serial.print(" cm");

  Serial.print("\n---------\n");
}

void servoInit() {
  servoArm.attach(SER_ARM); 
  servoGripper.attach(SER_GRIP);
  servoArm.write(armAngle);  
  servoGripper.write(gripperAngle); 
}

void motorInit() {
  motorRight.setSpeed(0);
  motorLeft.setSpeed(0);
}

void changeArmAngle(String input) {
  // May have to swap up and down in testing
  if (input == "ui") {
    if (armAngle != 0) {
      armAngle = armAngle -= 15;
      servoArm.write(armAngle);
      Serial.print("Arm set to: ");
      Serial.print(armAngle);
      Serial.print(" degrees");
    } else {
      Serial.print("Arm cannot be raised further.");
    }
  } else if (input == "u") {
    if (armAngle != 0) {
      armAngle = 0;
      servoArm.write(armAngle);
      Serial.print("Arm set to: ");
      Serial.print(armAngle);
      Serial.print(" degrees");
    } else {
      Serial.print("Arm cannot be raised further.");
    }
  } else if (input == "di") {
    if (armAngle != 90) {
      armAngle = armAngle += 15;
      servoArm.write(armAngle);
      Serial.print("Arm set to: ");
      Serial.print(armAngle);
      Serial.print(" degrees");
    } else {
      Serial.print("Arm cannot be lowered further.");
    }
  } else if (input == "d") {
    if (armAngle != 90) {
      armAngle = 90;
      servoArm.write(armAngle);
      Serial.print("Arm set to: ");
      Serial.print(armAngle);
      Serial.print(" degrees");
    } else {
      Serial.print("Arm cannot be lowered further.");
    }
  }
}

void changeGripperAngle(String input) {
  // May have to swap open and close in testing
  if (input == "oi") {
    if (gripperAngle != 0) {
      gripperAngle = gripperAngle -= 15;
      servoGripper.write(gripperAngle);
      Serial.print("Gripper set to: ");
      Serial.print(gripperAngle);
      Serial.print(" degrees");
    } else {
      Serial.print("Gripper cannot be opened further.");
    }
  } else if (input == "o") {
    if (gripperAngle != 0) {
      gripperAngle = 0;
      servoGripper.write(gripperAngle);
      Serial.print("Gripper set to: ");
      Serial.print(gripperAngle);
      Serial.print(" degrees");
    } else {
      Serial.print("Gripper cannot be opened further.");
    }
  } else if (input == "ci") {
    if (gripperAngle != 90) {
      gripperAngle = gripperAngle += 15;
      servoGripper.write(gripperAngle);
      Serial.print("Gripper set to: ");
      Serial.print(gripperAngle);
      Serial.print(" degrees");
    } else {
      Serial.print("Gripper cannot be closed further.");
    }
  } else if (input == "c") {
    if (gripperAngle != 90) {
      gripperAngle = 90;
      servoGripper.write(gripperAngle);
      Serial.print("Gripper set to: ");
      Serial.print(gripperAngle);
      Serial.print(" degrees");
    } else {
      Serial.print("Gripper cannot be closed further.");
    }
  }
}

void changeMotors(String input) {
  Serial.println("Please enter speed (1-100): ");
  int speed = 0;
  while (speed == 0) {
    speed = Serial.parseInt();
  }

  if (input == "f") {
    motorSpeedRight = speed;
    motorSpeedLeft = speed;
    motorRight.setSpeed(motorSpeedRight);
    motorLeft.setSpeed(motorSpeedLeft);
    motorRight.forward();
    motorLeft.forward();
    Serial.print("Moving forward at speed: ");
    Serial.print(speed);
  } else if (input == "b") {
    motorSpeedRight = speed;
    motorSpeedLeft = speed;
    motorRight.setSpeed(motorSpeedRight);
    motorLeft.setSpeed(motorSpeedLeft);
    motorRight.backward();
    motorLeft.backward();
    Serial.print("Moving backward at speed: ");
    Serial.print(speed);
  } else if (input == "l") {
    motorSpeedRight = speed;
    motorSpeedLeft = speed;
    motorRight.setSpeed(motorSpeedRight);
    motorLeft.setSpeed(motorSpeedLeft);
    motorRight.backward();
    motorLeft.forward();
    Serial.print("Turning left at speed: ");
    Serial.print(speed);
  } else if (input == "r") {
    motorSpeedRight = speed;
    motorSpeedLeft = speed;
    motorRight.setSpeed(motorSpeedRight);
    motorLeft.setSpeed(motorSpeedLeft);
    motorRight.forward();
    motorLeft.backward();
    Serial.print("Turning right at speed: ");
    Serial.print(speed);
  }
}

void automatedMotors(String input) {
  if (input == "fa") {
    Serial.print("Forward automation initiated. Enter (s) to terminate.\n");
    motorSpeedRight = 20;
    motorSpeedLeft = 20;
    motorRight.setSpeed(motorSpeedRight);
    motorLeft.setSpeed(motorSpeedLeft);
    while (ultrasonicFront.read(CM) > 10 && Serial.readStringUntil('\n') != "s") {
      Serial.print("\nMoving forward...");
      motorRight.forward();
      motorLeft.forward();
    }
  } else if (input == "ba") {
    Serial.print("Backward automation initiated. Enter (s) to terminate.\n");
    motorSpeedRight = 20;
    motorSpeedLeft = 20;
    motorRight.setSpeed(motorSpeedRight);
    motorLeft.setSpeed(motorSpeedLeft);
    while (ultrasonicRear.read(CM) > 10 && Serial.readStringUntil('\n') != "s") {
      Serial.print("\nMoving backward...");
      motorRight.backward();
      motorLeft.backward();
    }
  } else if (input == "la") {
    Serial.print("Left automation initiated. Enter (s) to terminate.\n");
    motorSpeedRight = 20;
    motorSpeedLeft = 20;
    motorRight.setSpeed(motorSpeedRight);
    motorLeft.setSpeed(motorSpeedLeft);
    while (ultrasonicFront.read(CM) < 30 && Serial.readStringUntil('\n') != "s") {
      Serial.print("\nLocating opening...");
      motorRight.backward();
      motorLeft.forward();
    }
  } else if (input == "ra") {
    Serial.print("Right automation initiated. Enter (s) to terminate.\n");
    motorSpeedRight = 20;
    motorSpeedLeft = 20;
    motorRight.setSpeed(motorSpeedRight);
    motorLeft.setSpeed(motorSpeedLeft);
    while (ultrasonicFront.read(CM) < 30 && Serial.readStringUntil('\n') != "s") {
      Serial.print("\nLocating opening...");
      motorRight.forward();
      motorLeft.backward();
    }
  }

  Serial.print("\n");
  stop();
}

void fullAutomation() {
  Serial.print("Full automation initiated. Enter (s) to terminate.\n");
  motorSpeedRight = 20;
  motorSpeedLeft = 20;
  motorRight.setSpeed(motorSpeedRight);
  motorLeft.setSpeed(motorSpeedLeft);
  while (Serial.readStringUntil('\n') != "s") {
    if (ultrasonicFront.read(CM) > 10) {
      Serial.print("\nMoving forward...");
      motorRight.forward();
      motorLeft.forward();
    } else {
      Serial.print("\nLocating opening...");
      motorRight.forward();
      motorLeft.backward();
    }
  }
  Serial.print("\n");
  stop();
}

void stop() {
  motorSpeedRight = 0;
  motorSpeedLeft = 0;
  motorRight.setSpeed(motorSpeedRight);
  motorLeft.setSpeed(motorSpeedLeft);
  motorRight.forward();
  motorLeft.forward();
  Serial.print("Stopping...");
}

void help() {
  Serial.println("\n------------------------------------------------");
  Serial.println("Welcome to the tabulator user interface!");

  Serial.println("\nMotor control:");
    Serial.println("\tBasic controls"); 
    Serial.println("\t\t- Forward (f)");
    Serial.println("\t\t- Back (b)");
    Serial.println("\t\t- Right (r)");
    Serial.println("\t\t- Left (l)");
    Serial.println("\t\t- Stop (s)");

  Serial.println("\n\tAutomated controls");
    Serial.println("\t\t- Continue forward until 10 cm from nearby surface (fa)");
    Serial.println("\t\t- Continue back until 10 cm from nearby surface (ba)");
    Serial.println("\t\t- Rotate right until a considerable path (30 cm) is found (ra)");
    Serial.println("\t\t- Rotate left until a considerable path (30 cm) is found (la)");

  Serial.println("\nArm control:");
    Serial.println("\t- Up (full extension) (u)");
    Serial.println("\t- Down (full extension) (d)");
    Serial.println("\t- Up (incrimental) (ui)");
    Serial.println("\t- Down (incrimental) (di)");

  Serial.println("\nGripper control:");
    Serial.println("\t- Open (full extension) (o)");
    Serial.println("\t- Close (full extension) (c)");
    Serial.println("\t- Open (incrimental) (oi)");
    Serial.println("\t- Close (incrimental) (ci)");
  
  Serial.println("\nSensor control:");
    Serial.println("\t- Print data (p)");

  Serial.println("\nTo display this menu again please click (h).");
  Serial.println("------------------------------------------------");
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("Serial Ready");

  servoInit();
  motorInit();

  Serial.println("Initialization Complete!");
  
  help();
}

void loop() {
  if (Serial.available() > 0) {
    String input = "";
    input = Serial.readStringUntil('\n');
    Serial.println("\n");
    if (input == "f" || input == "b" || input == "r" || input == "l") {
      changeMotors(input);
    }
    else if (input == "s") {
      stop();
    } 
    else if (input == "fa" || input == "ba" || input == "ra" || input == "la") {
      automatedMotors(input);
    }
    else if (input == "a") {
      fullAutomation();
    }
    else if (input == "ui" || input == "u" || input == "di" || input == "d") {
      changeArmAngle(input);
    }
    else if (input == "oi" || input == "o" || input == "ci" || input == "c") {
      changeGripperAngle(input);
    }
    else if (input == "h") {
      help();
    }
    else if (input == "p") {
      printSensorData();
    }
  }
}
