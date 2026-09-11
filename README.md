# Automatic Trash Can

An Arduino-based automated trash can that detects when the trash reaches a certain level and automatically operates the lid and trash-pushing mechanism using an ultrasonic sensor, stepper motor, and servo motor.

# About the Project

This is an embedded systems project that demonstrates how an Arduino can be used to automate a simple waste management system. The system uses an ultrasonic sensor to measure the distance between the sensor and the trash inside the can.

When the ultrasonic sensor detects trash within approximately 10 cm for 3 continuous seconds, the system considers the trash can to be full. The stepper motor then operates the lid mechanism, while the servo motor presses down the trash to create additional space.

After the trash has been pressed down, the servo motor returns to its original position and the stepper motor returns the lid mechanism to its initial position.

The project demonstrates how basic sensors, motors, and an Arduino microcontroller can work together to create an automated solution for preventing a trash can from overflowing.

# Key Features

- Automatic trash level detection using an ultrasonic sensor
- Detects trash within approximately 10 cm
- Requires continuous detection for 3 seconds before activating
- Automatic lid control using a stepper motor
- Automatic trash pressing using a servo motor
- Servo movement from 0° to 90°
- Stepper motor control using a 2048-step revolution
- Automatic return of the lid after the trash is pressed
- Continuous ultrasonic distance monitoring
- Serial Monitor output for distance measurements
- Stops the pressing operation when the trash is no longer detected

# Hardware Used

- Arduino microcontroller board
- Ultrasonic sensor
- Servo motor
- Stepper motor
- Breadboard
- Jumper wires
- Resistors
- Motor driver/control circuitry
- Trash can/container

# Pin Connections

| **Function** | **Arduino Pins** |
| --- | --- |
| Ultrasonic Trigger | Pin 12 |
| Ultrasonic Echo | Pin 13 |
| Servo Motor | Pin 2 |
| Stepper Motor Coil 1 | Pin 6 |
| Stepper Motor Coil 2 | Pin 5 |
| Stepper Motor Coil 3 | Pin 4 |
| Stepper Motor Coil 4 | Pin 3 |

# System Operation

### Trash Level Detection

The ultrasonic sensor continuously measures the distance between the sensor and the trash.

When the sensor detects an object at a distance of 10 cm or less, the Arduino starts a timer.

The trash is considered full only when the detected distance remains within the 10 cm range for approximately 3 seconds.

This prevents the system from immediately activating due to a temporary sensor reading.

### Trash Can Full

When the trash remains within the detection range for 3 seconds:

1. The stepper motor rotates the lid mechanism by one-quarter of a revolution.
2. The system waits for 1 second.
3. The servo motor gradually moves from 0° to 90°.
4. The servo presses the trash down.
5. The servo returns to its original 0° position.
6. The system waits for 1 second.
7. The stepper motor rotates in the reverse direction to return the lid mechanism to its original position.
8. The system waits for another second before returning to normal monitoring.

### Trash Detection During Pressing

While the servo motor is pressing the trash, the ultrasonic sensor continues measuring the distance.

If the trash is no longer detected within the 10 cm range, the pressing sequence is stopped and the servo immediately returns to 0°.

This allows the system to respond to changes in the detected trash level while the pressing mechanism is operating.

# Ultrasonic Sensor

The ultrasonic sensor is used to measure the distance between the sensor and the trash.

The Arduino sends a trigger pulse and measures the time required for the ultrasonic signal to return. The measured time is then converted into a distance in centimeters.

The programmed detection range is approximately **10 cm**.

A distance of `0 cm` is treated as an invalid or undetected reading.

# Motor Control

### Stepper Motor

The stepper motor is configured for **2048 steps per revolution** and operates at a speed of **10 RPM**.

When the trash can is detected as full, the stepper motor rotates:

- **512 steps forward** to operate the lid
- **512 steps backward** to return the lid

The 512-step movement corresponds to one-quarter of a 2048-step revolution.

### Servo Motor

The servo motor starts at **0°**.

When the trash can is detected as full, the servo gradually moves from:

**0° → 90°**

The servo moves one degree at a time with a short delay between movements.

After pressing the trash, the servo returns to:

**90° → 0°**

# Display Information

This project does not use a display module. Instead, the Arduino outputs the ultrasonic sensor readings through the Serial Monitor.

The Serial Monitor displays the measured distance in centimeters while the system is operating.

Example:

```text
Distance: 25 cm
Distance: 18 cm
Distance: 12 cm
Distance: 9 cm
Distance: 9 cm
```

# Video Documentation

- [Project Demonstration and Testing Videos](https://drive.google.com/drive/folders/1LACWk1MhXUkFy2tc8t_SobiZMc3fAqfB?usp=sharing)
