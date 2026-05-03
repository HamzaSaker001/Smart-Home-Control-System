# Smart Home Control System (AVR-Based) 🏠

### Overview
A secure, dual-layer home automation system designed using **ATmega32**. It features role-based access control (Admin/User) to manage home appliances via UART communication.

### Key Features
* **Security Layer:** Implements a password-protected login system with data stored in **EEPROM** for non-volatile credential management[cite: 1].
* **Environmental Control:** Automated AC system triggered by an **LM35** temperature sensor[cite: 1].
* **Lighting System:** Controls 6 isolated lamp circuits, including a dedicated PWM-based **Dimmer Circuit**[cite: 1].
* **Remote Management:** Supports remote commands via **UART/Bluetooth** protocols[cite: 1].

### Hardware & Technologies
* **Microcontroller:** AVR ATmega32[cite: 1].
* **Peripherals:** LCD 16x2, Keypad 4x4, EEPROM, LM35 Sensor[cite: 1].
* **Protocols:** UART, PWM[cite: 1].
