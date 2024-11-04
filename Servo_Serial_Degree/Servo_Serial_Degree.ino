#include <Servo.h>

Servo servo1;  // Create a servo object for the first servo
Servo servo2; // create servo object to control a servo
int servo1_pin = 9;
int servo2_pin = 10;

int servo1_angle = 90;
int servo2_angle = 90;  // variable to store the servo position

void setup() {
  servo1.attach(servo1_pin);  // attaches the servo on pin 9 to the servo object
  servo1.write(servo1_angle);      // Set initial servo position to 0 degrees

  servo2.attach(servo2_pin);  // attaches the servo on pin 9 to the servo object
  servo2.write(servo2_angle);
  // Initialize serial communication
  Serial.begin(115200);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

  // Print a message to indicate that serial communication is ready
  Serial.println("Serial Ready");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n'); // Read the input string until a newline
    input.trim(); // Remove any leading or trailing whitespaces

    // Split the input string into two parts based on the space
    int spaceIndex = input.indexOf(' '); // Find the space character

    if (spaceIndex > 0) {
      String part1 = input.substring(0, spaceIndex); // Extract the first part
      String part2 = input.substring(spaceIndex + 1); // Extract the second part

      // Check if both parts are non-empty before converting to integers
      if (part1.length() > 0 && part2.length() > 0) {
        servo1_angle = part1.toInt(); // Convert the first part to an integer
        servo2_angle = part2.toInt(); // Convert the second part to an integer

        // Output the two angles
        Serial.print("Servo 1 Angle: ");
        Serial.println(servo1_angle);
        Serial.print("Servo 2 Angle: ");
        Serial.println(servo2_angle);

        servo1.write(servo1_angle); 
        servo2.write(servo2_angle);
      } else {
        Serial.println("Invalid input. Both numbers must be provided.");
      }
    } else {
      Serial.println("Invalid input. Please enter two numbers separated by a space.");
    }
  }
}
