# Digital Electricity Meter with Calibration (Arduino)

This project implements a digital electricity meter using Arduino, incorporating voltage and current sensors for power measurement. It includes calibration functionality to ensure accurate measurement readings.

## Table of Contents

- [Overview](#overview)
- [Components](#components)
- [Installation](#installation)
- [Usage](#usage)
- [Acknowledgments](#acknowledgments)

## Overview

This Arduino project utilizes the following components to build a digital electricity meter:

- **Energy Monitor Library**: Used for voltage and current measurement.
- **LiquidCrystal Library**: Used to interface with a 20x4 LCD display.
- **Arduino UNO**: Microcontroller board for program execution.
- **Current and Voltage Sensors**: Connected to specific analog pins for electricity measurement.

The project includes calibration routines (`VoltageCalibration()` and `CurrentCalibration()`) to adjust sensor calibration values (`vCalib` and `cCalib`) for accurate measurement results.

## Components

- Arduino UNO board
- Energy Monitor (e.g., SCT-013-000 for current sensing)
- Voltage Sensor (e.g., ZMPT101B for voltage sensing)
- 20x4 LCD Display
- Pushbutton for calibration initiation
- Resistors, wires, and breadboard (for circuit connections)

## Installation

To run this project on your Arduino board:

1. **Hardware Setup**:
   - Connect the voltage sensor and current sensor to the specified analog pins (`VoltSensorPin` and `CurrSensorPin`).
   - Connect the LCD display to the Arduino board using appropriate pins.
   - Attach a pushbutton to the designated pin (`BUTTON_PIN`) for calibration initiation.

2. **Software Setup**:
   - Clone or download this repository.
   - Open the Arduino IDE.
   - Import the necessary libraries (`EmonLib.h` and `LiquidCrystal.h`).
   - Upload the sketch (`digital_electricity_meter.ino`) to your Arduino board.

## Usage

1. **Calibration**:
   - Press the pushbutton (`BUTTON_PIN`) to initiate calibration.
   - Follow the LCD prompts to complete voltage and current calibration.
   
2. **Measurement**:
   - After calibration, the Arduino will continuously measure and display RMS voltage, current, power, and cumulative energy usage (kWh) on the LCD display.

## Contributing

Contributions to this project are welcome! If you have any suggestions, improvements, or bug fixes, feel free to submit a pull request.

## Acknowledgments

- [OpenEnergyMonitor Project](https://learn.openenergymonitor.org/electricity-monitoring/ct-sensors/interface-with-arduino) for the Energy Monitor Library.
- Arduino and LiquidCrystal Library contributors.
