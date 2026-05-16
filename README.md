# 🏠 Smart Home System

A full embedded home automation system built on AVR microcontroller (ATmega32), supporting both **remote control via Bluetooth** and **local control via LCD & Keypad**. Designed with a multi-user login system, persistent memory, and automated environment sensing.

---

## 📌 Project Overview

Smart home technology aims to make everyday appliances controllable, intelligent, and accessible. This system allows an admin and registered users to control lights, air conditioning, and a door — either remotely from a PC/mobile or locally through a keypad interface.

---

## ✨ Features

- 🔐 **Multi-user login system** — Admin and User roles with password protection
- 📱 **Bluetooth remote control** — via PC or mobile terminal
- ⌨️ **LCD & Keypad local interface** — user-only local access
- 💡 **6 Lamps** — 5 ON/OFF lamps + 1 PWM dimmer-controlled lamp
- 🌡️ **Temperature-based AC control** — Auto ON above 28°C, Auto OFF below 21°C
- 🚪 **Servo-controlled door** — Admin-only remote command
- 💾 **External EEPROM** — Stores usernames & passwords across power cycles
- 🚨 **Security alarm** — Fires after 3 wrong login attempts, requires hardware reset

---

## 🗂️ System Architecture

```
                        ┌─────────────────────┐
  Mobile / PC  ◄──BT──► │   ATmega32 MCU      │
                        │                     │
  LCD + Keypad ◄──────► │  • Login System     │
                        │  • Lamp Control     │
  EEPROM       ◄──I2C──► │  • AC Logic         │
                        │  • Door Control     │
  Temp Sensor  ──ADC──► │  • Alarm System     │
                        └──────┬──────────────┘
                               │
        ┌──────────────────────┼──────────────────────┐
        ▼                      ▼                      ▼
   5x Relay            Dimmer Circuit           Servo Motor
  (ON/OFF Lamps)      (PWM Lamp L6)            (Door)
        │
        ▼
   DC Motor (AC)
```

---

## ⚙️ Specifications

### 🔑 Login System
| Feature | Admin | User |
|---|---|---|
| Remote access (Bluetooth) | ✅ | ✅ |
| Local access (LCD/Keypad) | ❌ | ✅ |
| Register / remove users | ✅ | ❌ |
| Door control | ✅ | ❌ |
| Lamp & AC control | ✅ | ✅ |
| EEPROM read/write | ✅ | Read only |

### 💡 Lamp Control
- 5 standard lamps: ON/OFF via relay
- 1 dimmer lamp: PWM-controlled (0–5V → current control)
- All lamps electrically isolated (relay-based)

### 🌡️ Temperature & AC
- Sensor: LM35 (or equivalent)
- AC ON if temperature > 28°C
- AC OFF if temperature < 21°C
- Actuator: DC motor (simulates AC unit)

### 🚨 Security
- 3 failed login attempts → system lockdown + alarm activation
- System requires hardware reset to recover
- Usernames and passwords stored in external EEPROM (24C08)

---

## 🧰 Components

| Component | Model | Purpose |
|---|---|---|
| Microcontroller | ATmega32 | Main controller |
| Bluetooth Module | HC-05 | Remote communication |
| External EEPROM | 24C08 | Persistent credential storage |
| LCD | LM016L (16x2) | Local display |
| Keypad | 4x4 Matrix | Local input |
| Temperature Sensor | LM35 | Ambient temperature reading |
| Transistors + Relays | NPN x5 | Lamp switching (isolation) |
| Solid-State Relay | SSR | Dimmer circuit |
| Servo Motor | Standard | Door actuator |
| DC Motor | — | Air conditioning simulation |

---

## 🔌 Communication Interfaces Used

- **UART** — Bluetooth module (Tx/Rx)
- **I2C** — External EEPROM (24C08)
- **ADC** — Temperature sensor (LM35)
- **PWM** — Dimmer lamp control
- **GPIO** — Relays, keypad, servo

---

## 🛠️ Tools & Environment

- **Language:** Embedded C
- **MCU:** ATmega32 (AVR)
- **Simulation:** Proteus
- **Programmer:** AVRDUDE / USBasp

---

## 👥 Team

Project built as part of the **Embedded Systems Diploma** at AMIT Learning.

---

## 📄 License

This project is for educational purposes.
