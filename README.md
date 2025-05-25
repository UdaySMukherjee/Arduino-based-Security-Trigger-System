# 🔐 Arduino Security Trigger System
### Created by **Uday Sankar Mukherjee**  
📺 YouTube: [USMTechLab](https://www.youtube.com/@USMTechLab)

---

## 📌 Project Description

This Arduino-based **Security Trigger System** detects environmental changes (like motion or vibration) using an analog sensor. If armed and a trigger condition is met, it activates an **alarm system with sound and flashing LEDs**.

✨ **Key Features:**
- Arm/Disarm system via button
- Smart threshold calibration
- Visual alerts using LEDs
- Audible alerts via buzzer
- Smooth and stylish code logic

---

## 🧰 Hardware Required

| Component          | Quantity |
|-------------------|----------|
| Arduino Uno/Nano  | 1        |
| Analog Sensor (e.g., LDR, microphone, etc.) | 1 |
| Red LED           | 1        |
| Green LED         | 1        |
| Trigger LEDs      | 2        |
| 220Ω Resistors    | 3–5      |
| Push Button       | 1        |
| Buzzer/Speaker    | 1        |
| Breadboard & Jumper Wires | 1 set    |

---

## 🧷 Wiring Diagram

| Pin             | Connected To             |
|----------------|--------------------------|
| A0              | Analog Sensor Output     |
| 4               | Red LED (Armed Status)   |
| 5               | Green LED (Disarmed)     |
| 6               | Push Button              |
| 7               | Triggered LED 1          |
| 8               | Triggered LED 2          |
| 12              | Buzzer/Speaker           |
| GND, 5V         | Shared across components |

> ℹ️ *Use 220Ω resistors in series with LEDs to prevent burning.*

---

## 🔄 How It Works

### 🔧 Calibration
- System takes multiple analog readings at startup.
- Calculates baseline and sets a **custom threshold**.
- Detects large deviations to trigger alerts.

### 🟢 Arm/Disarm Logic
- Press the button to toggle states.
- Armed = Red LED ON 🔴
- Disarmed = Green LED ON 🟢

### 🚨 Trigger Mode
- If armed and the sensor value drops below threshold:
  - LEDs blink rapidly.
  - Buzzer sweeps tones (up and down).

---

## ▶️ Uploading & Running

1. Connect all hardware components as per wiring.
2. Upload the sketch to your Arduino board.
3. On power-up:
   - LEDs blink to indicate boot.
   - System auto-calibrates.
4. Press the button to toggle **Armed/Disarmed**.
5. Move your hand or create a disturbance near the sensor — see the system in action!

---

### 🧑‍💻 Author
Uday Sankar Mukherjee
YouTube Channel: USMTechLab

Feel free to star ⭐ and fork 🍴 this project if you find it helpful!
