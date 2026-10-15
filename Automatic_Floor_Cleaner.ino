
/*
  Automatic Floor Cleaning Robot
  --------------------------------
  Controller  : Arduino UNO
  Sensor      : HC-SR04 Ultrasonic Sensor
  Motor Driver: L298N
  Motors      : 2 DC Gear Motors

  Features:
  - Moves forward automatically
  - Detects obstacles using ultrasonic sensor
  - Stops when an obstacle is detected
  - Moves backward
  - Turns and continues cleaning
*/

#define TRIG_PIN 9
#define ECHO_PIN 10

// Left motor
#define ENA 5
#define IN1 6
#define IN2 7

// Right motor
#define ENB 3
#define IN3 8
#define IN4 11

#define MOTOR_SPEED 150

// Minimum safe distance in cm
#define OBSTACLE_DISTANCE 20

void setup() {
  Serial.begin(9600);

  // Ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Motor driver
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopRobot();

  delay(1000);
}

void loop() {

  long distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If obstacle is detected
  if (distance <= OBSTACLE_DISTANCE) {

    stopRobot();
    delay(300);

    // Move backward
    moveBackward();
    delay(500);

    stopRobot();
    delay(300);

    // Turn right
    turnRight();
    delay(700);

    stopRobot();
    delay(200);
  }

  else {
    // No obstacle → move forward
    moveForward();
  }

  delay(50);
}


// -------------------------------------
// Get distance from ultrasonic sensor
// -------------------------------------

long getDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  // If no echo is received
  if (duration == 0) {
    return 400;
  }

  long distance = duration * 0.034 / 2;

  return distance;
}


// -------------------------------------
// Move Forward
// -------------------------------------

void moveForward() {

  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


// -------------------------------------
// Move Backward
// -------------------------------------

void moveBackward() {

  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


// -------------------------------------
// Turn Right
// -------------------------------------

void turnRight() {

  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);

  // Left motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Right motor backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


// -------------------------------------
// Stop Robot
// -------------------------------------

void stopRobot() {

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}