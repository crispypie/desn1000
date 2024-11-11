#include <Servo.h>
#include <Ultrasonic.h>
#include <L298N.h>

// ALLOCATE PINS

// Motor A pins
const unsigned int IN2_RIGHT = 8; // Orange
const unsigned int IN1_RIGHT = 9; // Red
const unsigned int EN_RIGHT = 10; // Black, extra
int motorSpeedRight = 0;

// Motor B pins
const unsigned int IN1_LEFT = 12; // Brown 
const unsigned int IN2_LEFT = 13; // Black
const unsigned int EN_LEFT = 11; // Brown, extra
int motorSpeedLeft = 0;

// Servo A pin (arm alignment)
int maxArmAngle = 180;
int minArmAngle = 115;
int incrementArm = 5;
const unsigned int SER_ARM = 5;
int armAngle = maxArmAngle;

// Servo B pin (gripper open/close)
int maxGripperAngle = 180;
int minGripperAngle = 110;
int incrementGripper = 10;
const unsigned int SER_GRIP = 6;
int gripperAngle = maxGripperAngle;

// Ultrasonic sensor pins
const unsigned int TRIG_FRONT = 2; // Orange
const unsigned int ECHO_FRONT = 3; // Yellow

const unsigned int TRIG_REAR = 4; // Purple
const unsigned int ECHO_REAR = 7; // Grey


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
void changeMotors(String input);
void changeMotorsIncrement(String input);
void automatedMotors(String input);
void fullAutomation();
void constructMap();
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
  if (input == "di") {
    if (armAngle != minArmAngle) {
      armAngle -= incrementArm;
      servoArm.write(armAngle);
      Serial.print("Arm set to: ");
      Serial.print(armAngle);
      Serial.print(" degrees");
    } else {
      Serial.print("Arm cannot be lowered further.");
    }
  } else if (input == "d") {
    if (armAngle != minArmAngle) {
      armAngle = minArmAngle;
      servoArm.write(armAngle);
      Serial.print("Arm set to: ");
      Serial.print(armAngle);
      Serial.print(" degrees");
    } else {
      Serial.print("Arm cannot be lowered further.");
    }
  } else if (input == "ui") {
    if (armAngle != maxArmAngle) {
      armAngle += incrementArm;
      servoArm.write(armAngle);
      Serial.print("Arm set to: ");
      Serial.print(armAngle);
      Serial.print(" degrees");
    } else {
      Serial.print("Arm cannot be raised further.");
    }
  } else if (input == "u") {
    if (armAngle != maxArmAngle) {
      armAngle = maxArmAngle;
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
    if (gripperAngle != maxGripperAngle) {
      gripperAngle += incrementGripper;
      servoGripper.write(gripperAngle);
      Serial.print("Gripper set to: ");
      Serial.print(gripperAngle);
      Serial.print(" degrees");
    } else {
      Serial.print("Gripper cannot be opened further.");
    }
  } else if (input == "o") {
    if (gripperAngle != maxGripperAngle) {
      gripperAngle = maxGripperAngle;
      servoGripper.write(gripperAngle);
      Serial.print("Gripper set to: ");
      Serial.print(gripperAngle);
      Serial.print(" degrees");
    } else {
      Serial.print("Gripper cannot be opened further.");
    }
  } else if (input == "ci") {
    if (gripperAngle != minGripperAngle) {
      gripperAngle -= incrementGripper;
      servoGripper.write(gripperAngle);
      Serial.print("Gripper set to: ");
      Serial.print(gripperAngle);
      Serial.print(" degrees");
    } else {
      Serial.print("Gripper cannot be closed further.");
    }
  } /*else if (input == "c") {
    if (gripperAngle != minGripperAngle) {
      gripperAngle = minGripperAngle;
      servoGripper.write(gripperAngle);
      Serial.print("Gripper set to: ");
      Serial.print(gripperAngle);
      Serial.print(" degrees");
    } else {
      Serial.print("Gripper cannot be closed further.");
    }
  }*/
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

void changeMotorsIncrement(String input) {
  if (input == "fi") {
    motorSpeedRight = 90;
    motorSpeedLeft = 90;
    motorRight.setSpeed(motorSpeedRight);
    motorLeft.setSpeed(motorSpeedLeft);
    motorRight.forward();
    motorLeft.forward();
    delay(250);
    motorRight.stop();
    motorLeft.stop();
  } else if (input == "bi") {
    motorSpeedRight = 90;
    motorSpeedLeft = 90;
    motorRight.setSpeed(motorSpeedRight);
    motorLeft.setSpeed(motorSpeedLeft);
    motorRight.backward();
    motorLeft.backward();
    delay(250);
    motorRight.stop();
    motorLeft.stop();
  } else if (input == "li") {
    motorSpeedRight = 110;
    motorSpeedLeft = 110;
    motorRight.setSpeed(motorSpeedRight);
    motorLeft.setSpeed(motorSpeedLeft);
    motorRight.backward();
    motorLeft.forward();
    delay(250);
    motorRight.stop();
    motorLeft.stop();
  } else if (input == "ri") {
    motorSpeedRight = 110;
    motorSpeedLeft = 110;
    motorRight.setSpeed(motorSpeedRight);
    motorLeft.setSpeed(motorSpeedLeft);
    motorRight.forward();
    motorLeft.backward();
    delay(250);
    motorRight.stop();
    motorLeft.stop();
  } 
}

void automatedMotors(String input) {
  if (input == "fa") {
    Serial.print("Forward automation initiated. Enter (s) to terminate.\n");
    motorSpeedRight = 90;
    motorSpeedLeft = 90;
    motorRight.setSpeed(motorSpeedRight);
    motorLeft.setSpeed(motorSpeedLeft);
    while (ultrasonicFront.read(CM) > 10 && Serial.readStringUntil('\n') != "s") {
      Serial.print("\nMoving forward...");
      motorRight.forward();
      motorLeft.forward();
    }
  } else if (input == "ba") {
    Serial.print("Backward automation initiated. Enter (s) to terminate.\n");
    motorSpeedRight = 90;
    motorSpeedLeft = 90;
    motorRight.setSpeed(motorSpeedRight);
    motorLeft.setSpeed(motorSpeedLeft);
    while (ultrasonicRear.read(CM) > 10 && Serial.readStringUntil('\n') != "s") {
      Serial.print("\nMoving backward...");
      motorRight.backward();
      motorLeft.backward();
    }
  } else if (input == "la") {
    Serial.print("Left automation initiated. Enter (s) to terminate.\n");
    motorSpeedRight = 90;
    motorSpeedLeft = 90;
    motorRight.setSpeed(motorSpeedRight);
    motorLeft.setSpeed(motorSpeedLeft);
    while (ultrasonicFront.read(CM) < 30 && Serial.readStringUntil('\n') != "s") {
      Serial.print("\nLocating opening...");
      motorRight.backward();
      // motorLeft.forward();
    }
  } else if (input == "ra") {
    Serial.print("Right automation initiated. Enter (s) to terminate.\n");
    motorSpeedRight = 90;
    motorSpeedLeft = 90;
    motorRight.setSpeed(motorSpeedRight);
    motorLeft.setSpeed(motorSpeedLeft);
    while (ultrasonicFront.read(CM) < 30 && Serial.readStringUntil('\n') != "s") {
      Serial.print("\nLocating opening...");
      // motorRight.forward();
      motorLeft.backward();
    }
  }

  Serial.print("\n");
  stop();
}

void fullAutomation() {
  Serial.print("Full automation initiated. Enter (s) to terminate.\n");
  while (Serial.readStringUntil('\n') != "s") {
    if (ultrasonicFront.read(CM) > 25) {
      motorSpeedRight = 70;
      motorSpeedLeft = 70;
      motorRight.setSpeed(motorSpeedRight);
      motorLeft.setSpeed(motorSpeedLeft);
      Serial.print("\nMoving forward...");
      motorRight.forward();
      motorLeft.forward();
    } else {
      motorSpeedRight = 100;
      motorSpeedLeft = 100;
      motorRight.setSpeed(motorSpeedRight);
      motorLeft.setSpeed(motorSpeedLeft);
      Serial.print("\nLocating opening...");
      motorRight.forward();
      motorLeft.backward();
    }
  }
  Serial.print("\n");
  stop();
}

void constructMap() {
  Serial.print("Map construction in progress...");

  bool n = false;
  bool ne = false;
  bool e = false;
  bool se = false;
  bool s = false;
  bool sw = false;
  bool w = false;
  bool nw = false;

  if (ultrasonicFront.read(CM) < 25) {
    n = true;
  }
  if (ultrasonicRear.read(CM) < 25) {
    s = true;
  }

  motorSpeedRight = 100;
  motorSpeedLeft = 100;
  motorRight.setSpeed(motorSpeedRight);
  motorLeft.setSpeed(motorSpeedLeft);
  motorRight.forward();
  motorLeft.backward();

  delay(1000); // Allow it to move for one second, may have to alter
  if (ultrasonicFront.read(CM) < 15) {
    ne = true;
  }
  if (ultrasonicRear.read(CM) < 15) {
    sw = true;
  }

  delay(1000); 
  if (ultrasonicFront.read(CM) < 15) {
    e = true;
  }
  if (ultrasonicRear.read(CM) < 15) {
    w = true;
  }

  delay(1000); 
  if (ultrasonicFront.read(CM) < 15) {
    se = true;
  }
  if (ultrasonicRear.read(CM) < 15) {
    nw = true;
  }

  motorRight.backward();
  motorLeft.forward();
  delay(1000 * 3);

  Serial.print("\n");
  stop();

  // PRINT MAP
  Serial.print("Map (X indicates obstacle):\n");
  if (nw == true) {
    Serial.print("X");
  } else {
    Serial.print("O");
  }

  if (n == true) {
    Serial.print("X");
  } else {
    Serial.print("O");
  }

  if (ne == true) {
    Serial.print("X\n");
  } else {
    Serial.print("O\n");
  }

  if (w == true) {
    Serial.print("X");
  } else {
    Serial.print("O");
  }

  Serial.print(" ");

  if (e == true) {
    Serial.print("X\n");
  } else {
    Serial.print("O\n");
  }

  if (sw == true) {
    Serial.print("X");
  } else {
    Serial.print("O");
  }

  if (s == true) {
    Serial.print("X");
  } else {
    Serial.print("O");
  }

  if (se == true) {
    Serial.print("X\n");
  } else {
    Serial.print("O\n");
  }
  
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
    Serial.println("\t\t- Full automation (a)");
    Serial.println("\t\t- Continue forward until 10 cm from nearby surface (fa)");
    Serial.println("\t\t- Continue back until 10 cm from nearby surface (ba)");
    Serial.println("\t\t- Rotate right until a considerable path (30 cm) is found (ra)");
    Serial.println("\t\t- Rotate left until a considerable path (30 cm) is found (la)");

  Serial.println("\nArm control:");
    Serial.println("\t- Up (full extension) (u)");
    Serial.println("\t- Down (full extension) (d)");
    Serial.println("\t- Up (incremental) (ui)");
    Serial.println("\t- Down (incremental) (di)");

  Serial.println("\nGripper control:");
    Serial.println("\t- Open (full extension) (o)");
    /*Serial.println("\t- Close (full extension) (c)");*/
    Serial.println("\t- Open (incremental) (oi)");
    Serial.println("\t- Close (incremental) (ci)");
  
  Serial.println("\nSensor control:");
    Serial.println("\t- Print data (p)");

  Serial.println("\nMapping:");
    Serial.println("\t- Map current position (m)");

  Serial.println("\nTo display this menu again, please click (h).");
  Serial.println("------------------------------------------------");
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("Serial Ready");

  servoInit();
  motorInit();

  Serial.println("Initialization Complete!");
  
  //help();
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
    else if (input == "fi" || input == "bi" || input == "ri" || input == "li") {
      changeMotorsIncrement(input);
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
    else if (input == "oi" || input == "o" || input == "ci" /*|| input == "c"*/) {
      changeGripperAngle(input);
    }
    else if (input == "h") {
      // help();
    }
    else if (input == "p") {
      printSensorData();
    }
    else if (input == "m") {
      constructMap();
    }
    else if (input == " ") {
      Serial.println("Invalid command. Click (h) for help."); 
    }
  }
}
