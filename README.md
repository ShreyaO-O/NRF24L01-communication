# NRF24L01 Two-Way Wireless Communication

This repository demonstrates two types of two-way communication using the **NRF24L01** module:

1. **Arduino ↔ Raspberry Pi**
2. **Arduino ↔ Arduino/ESP32**

---

## 📁 Files Overview

| File Name        | Purpose                                     |
|------------------|---------------------------------------------|
| `Arduino.cpp`    | Used in Arduino-RPi communication setup     |
| `Rpi.py`         | Raspberry Pi code (Python) for RF24         |
| `Arduino1.ino`   | Arduino 1 for Arduino-Arduino communication |
| `Arduino2.ino`   | Arduino 2 for Arduino-Arduino communication |

---

### 🔄 Description

This setup allows **two-way communication** between an Arduino and a Raspberry Pi and between two Arduinos. One sends a message, and the other acknowledges it with a response.

### 🛠 Hardware Required

- 1 × Arduino Uno/Nano
- 1 × Raspberry Pi (with SPI support)
- 2 × NRF24L01 Modules
- Jumper wires
- 10µF capacitor (across VCC & GND of NRF)

### 🔌 Wiring

| NRF24L01 Pin | Arduino Uno/Nano | Raspberry Pi     | ESP32               |
|--------------|------------------|------------------|---------------------|
| VCC          | 3.3V             | 3.3V             | 3.3V                |
| GND          | GND              | GND              | GND                 |
| CE           | D9               | GPIO22           | GPIO4 (customizable)|
| CSN (CS)     | D10              | GPIO8 (CE0 - SPI)| GPIO5 (customizable)|
| SCK          | D13              | GPIO11 (SCK)     | GPIO18              |
| MOSI         | D11              | GPIO10 (MOSI)    | GPIO23              |
| MISO         | D12              | GPIO9 (MISO)     | GPIO19              |

> ⚠️ **Important Notes:**
> - **Do not connect VCC to 5V.** NRF24L01 operates only on 3.3V.
> - A **10µF capacitor** across VCC and GND on the NRF module is recommended for stability.
> - On **ESP32**, CE and CSN can be mapped to any GPIO using software SPI if needed.

### 🧪 Running the Arduino-RPi Setup

#### ➤ Arduino

Upload the Arduino codes to your Arduino using the Arduino IDE.

#### ➤ Raspberry Pi

1. Install required libraries:
   ```bash
   sudo apt update
   sudo apt install python3-pip
   pip3 install spidev
   
2. Enable SPI:
   ```bash
   sudo raspi-config   # Interfacing Options → SPI → Enable
   
3. Go to the directory and run code
   ```bash
     python3 Rpi.py


