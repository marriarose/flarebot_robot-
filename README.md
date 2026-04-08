#Fire Detection & Obstacle Avoidance Robot (Bluetooth Controlled)

## Overview

This project is an Arduino-based smart robot that combines:

* Fire detection using a flame sensor
* Obstacle avoidance using an ultrasonic sensor
* Manual control via Bluetooth (HC-05 module)

The robot can operate in **two modes**:

* **Manual Mode** – controlled via Bluetooth commands
* **Auto Mode** – autonomously avoids obstacles and detects fire

---

## Features

* Detects fire and triggers alert (LED + buzzer)
* Sends alert messages via Bluetooth
* Avoids obstacles automatically
* Switch between manual and autonomous modes
* Simple motor control for movement

---

## Working Logic

### Modes

* `M` → Manual Mode
* `A` → Auto Mode

### Manual Controls (via Bluetooth)

| Command | Action        |
| ------- | ------------- |
| F       | Move Forward  |
| B       | Move Backward |
| R       | Turn Right    |
| S       | Stop          |

---

### Auto Mode Behavior

1. **Fire Detection**

   * If flame detected:

     * Robot stops
     * LED turns ON
     * Buzzer activates
     * Sends `"Fire detected!"`

2. **Obstacle Avoidance**

   * Measures distance using ultrasonic sensor
   * If obstacle < 15 cm:

     * Stops → turns right → continues
   * Else:

     * Moves forward

---

## Hardware Requirements

* Arduino (Uno/Nano)
* HC-05 Bluetooth Module
* Flame Sensor
* Ultrasonic Sensor (HC-SR04)
* Motor Driver (L298N or similar)
* DC Motors + Wheels
* Buzzer
* LED
* Power Supply

---

## Pin Configuration

| Component       | Pin |
| --------------- | --- |
| Flame Sensor    | D2  |
| LED             | D3  |
| Motor IN1       | D4  |
| Motor IN2       | D5  |
| Motor IN3       | D6  |
| Motor IN4       | D7  |
| Ultrasonic ECHO | D8  |
| Ultrasonic TRIG | D9  |
| Buzzer          | D10 |
| Bluetooth RX    | D11 |
| Bluetooth TX    | D12 |

---

## Setup Instructions

1. Connect all components as per pin configuration
2. Upload the Arduino code
3. Pair HC-05 with your phone (default PIN: `1234` or `0000`)
4. Use a Bluetooth terminal app to send commands

---

## 📡 Serial Output

* Displays distance readings
* Shows fire detection alerts

---

## Notes

* Flame sensor gives **LOW signal when fire is detected**
* Adjust distance threshold (`15 cm`) as needed
* Ensure proper motor power supply for stable operation

---
