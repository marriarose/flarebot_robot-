#include <SoftwareSerial.h>

// Bluetooth pins
SoftwareSerial BT(11, 12); // RX, TX

// Sensor Pins
#define FLAME_SENSOR 2
#define LED 3
#define TRIG 9
#define ECHO 8
#define BUZZER_PIN 10  

// Motor Pins
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7

long duration;
int distance;

char command;
bool manualMode = false;

// -------- Motor Functions --------
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// -------- Setup --------
void setup() {
  pinMode(FLAME_SENSOR, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  BT.begin(9600);   // HC-05

  delay(2000);
}

// -------- Loop --------
void loop() {

  // -------- Bluetooth Control --------
  if (BT.available()) {
    command = BT.read();

    if (command == 'M') {
      manualMode = true;
      BT.println("Manual Mode ON");
    }
    else if (command == 'A') {
      manualMode = false;
      BT.println("Auto Mode ON");
    }

    if (manualMode) {
      if (command == 'F') forward();
      else if (command == 'B') backward(); 
      else if (command == 'S') stopRobot();
      else if (command == 'R') turnRight();
    }
  }

  // -------- AUTO MODE --------
  if (!manualMode) {

    int flame = digitalRead(FLAME_SENSOR);
    bool flameDetected = (flame == LOW);

    if (flameDetected) {
      stopRobot();
      digitalWrite(LED, HIGH);
      digitalWrite(BUZZER_PIN, LOW);
      BT.println("Fire detected!");
      Serial.println("Fire detected!");
    } 
    else {
      digitalWrite(LED, LOW);
      digitalWrite(BUZZER_PIN, HIGH);

      // Ultrasonic
      digitalWrite(TRIG, LOW);
      delayMicroseconds(2);
      digitalWrite(TRIG, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG, LOW);

      duration = pulseIn(ECHO, HIGH);
      distance = duration * 0.034 / 2;

      Serial.print("Distance: ");
      Serial.println(distance);

      if (distance < 15) {
        stopRobot();
        delay(200);
        turnRight();
        delay(500);
        stopRobot();
        delay(200);
      } else {
        forward();
      }
    }
  }

  delay(50);
}