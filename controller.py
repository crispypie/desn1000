import pygame
import time
import serial


# Initialize pygame and the joystick
pygame.init()
pygame.joystick.init()


# Get the first joystick
joystick = pygame.joystick.Joystick(0)
joystick.init()


print(f"Initialized controller: {joystick.get_name()}")


serialPort = '/dev/tty.usbmodem101'


# Set up the serial connection (adjust COM port and baud rate as needed)
ser = serial.Serial(serialPort, 9600, timeout=1)
time.sleep(1)  # Give the connection a second to settle


# Function to send a message over the serial connection
def send_serial_message(message):
  message = message + "\n"
  ser.write(message.encode())  # Encode string to bytes and send it over serial
  print(f"Sent: {message}")


def read_serial_message():
  if ser.in_waiting > 0:  # Check if data is available to read
      message = ser.readline().decode('utf-8').strip()  # Read, decode, and strip whitespace
      print("Received message:", message)
  
def map_range(value, old_min, old_max, new_min, new_max):
  # Map the value from old range to new range
  return (value - old_min) * (new_max - new_min) / (old_max - old_min) + new_min


# Mapping a number from (-1, 1) to (0, 180)
def map_to_servo_range(value):
  return map_range(value, -1, 1, 0, 180)


servo1_angle = 90
servo2_angle = 90


def joy_deadzone(value):
  deadzone = 0.03
  if (-deadzone < value < deadzone):
    return 0
  else:
    return value
  
# Main loop to capture events
try:
  while True:
    pygame.event.pump()  # Process event queue
    
    left_joy_axis_x = joy_deadzone(joystick.get_axis(0))
    left_joy_axis_y = joy_deadzone(joystick.get_axis(1))
    right_joy_axis_x = joy_deadzone(joystick.get_axis(2))
    right_joy_axis_y = joy_deadzone(joystick.get_axis(3))
    
    servo1_angle = round(map_to_servo_range(left_joy_axis_y))
    servo2_angle = round(map_to_servo_range(right_joy_axis_y))
    
    send_serial_message(f"{servo1_angle} {servo2_angle}")
    
    read_serial_message()
    
    pygame.time.Clock().tick(60)
    
except KeyboardInterrupt:
  print("Exiting...")
  
finally:
  # Clean up
  ser.close()  # Close the serial connection when done
  pygame.joystick.quit()
  pygame.quit()