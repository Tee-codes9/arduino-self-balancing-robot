# 🤖 Arduino Self-Balancing Robot

A dynamic, self-balancing dual-motor robot developed using an **Arduino Uno**, **MPU6050 IMU sensor**, and **L298N motor driver**. Built for the MSA University **Deep Minds Event**, this project demonstrates real-time feedback loops, accelerometer/gyroscope sensor fusion, and dynamic equilibrium physics.

---

## 📌 Features
* **Real-time Sensor Fusion:** Reads raw 6-DOF data (accelerometer and gyroscope) from the MPU6050 sensor via I2C to calculate accurate tilt angles.
* **Active Equilibrium Control:** Continuously computes error and drives dual DC motors to balance the chassis dynamically.
* **Custom Motor Control Logic:** Leverages PWM signals via the L298N motor driver to adjust wheel rotation direction and velocity rapidly.

---

## 🛠️ Hardware Stack & Components
* **Microcontroller:** Arduino Uno (ATmega328P)
* **Sensor:** MPU6050 Accelerometer & Gyroscope Module
* **Motor Driver:** L298N Dual H-Bridge Motor Driver
* **Motors:** 2x DC Gear Motors + Wheels
* **Power Source:** External Li-ion / DC Power Pack
* **Chassis:** Custom dual-deck robot frame

---

## 💻 Tech Stack & Libraries
* **Language:** Embedded C / C++
* **IDE:** Arduino IDE / VS Code (PlatformIO)
* **Libraries Used:** 
  * `Wire.h` (I2C communication)
  * `MPU6050.h` / `I2Cdev.h` (Sensor interface)

---

## 🚀 Circuit & Setup
1. **MPU6050 Connection:**
   * `VCC` ➔ 5V | `GND` ➔ GND
   * `SDA` ➔ A4 | `SCL` ➔ A5
2. **L298N Driver Connection:**
   * `IN1`, `IN2` ➔ Digital Pins for Left Motor Direction
   * `IN3`, `IN4` ➔ Digital Pins for Right Motor Direction
   * `ENA`, `ENB` ➔ PWM Digital Pins for Speed Control

---

## 🎓 Showcase
Demonstrated at the **MSA University Deep Minds Showcase** to highlight physics integration, dynamic system control, and hardware-software interaction.
