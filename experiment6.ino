#include <Servo.h>
#include <Stepper.h>

const int stepsPerRevolution = 2048;

Servo pusherServo;
Stepper lidStepper(stepsPerRevolution, 6, 5, 4, 3);

const int servoPin = 2;
const int trigPin = 12;
const int echoPin = 13;

bool motorsActivated = false;
int servoPosition = 0;
const int maxServoPosition = 90;
unsigned long trashFullStartTime = 0;
const unsigned long trashFullDuration = 3000;
const int detectionRange = 10;

void setup() {
  pusherServo.attach(servoPin);
  lidStepper.setSpeed(10);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pusherServo.write(0);

  Serial.begin(9600);
}

void loop() {
  int distance = measureDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance <= detectionRange) {
    if (trashFullStartTime == 0) {
      trashFullStartTime = millis();
    }

    if ((millis() - trashFullStartTime >= trashFullDuration) && !motorsActivated) {
      motorsActivated = true;

      lidStepper.step(stepsPerRevolution / 4);
      delay(1000);

      for (servoPosition = 0; servoPosition <= maxServoPosition; servoPosition += 1) {
        pusherServo.write(servoPosition);
        delay(100);

        distance = measureDistance();
        if (distance > detectionRange || distance == 0) {
          stopMotors();
          return;
        }
      }

      pusherServo.write(0);
      delay(1000);

      lidStepper.step(-stepsPerRevolution / 4);
      delay(1000);

      motorsActivated = false;
    }
  } else {
    trashFullStartTime = 0;
    motorsActivated = false;
  }

  delay(100);
}

int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}

void stopMotors() {
  pusherServo.write(0);
  motorsActivated = false;
}
