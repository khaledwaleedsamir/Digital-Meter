# Digital Electricity Meter with Calibration

This project implements a digital electricity watthour meter using Arduino, incorporating voltage and current sensors for power measurement. It includes calibration functionality to ensure accurate measurement readings.

## Table of Contents

- [Overview](#overview)
- [Components](#components)
- [Installation](#installation)
- [Usage](#usage)
- [Acknowledgments](#acknowledgments)

## Overview

This project utilizes the following components to build a digital electricity meter:

- **Energy Monitor Library**: Used for voltage and current measurement.
- **LiquidCrystal Library**: Used to interface with a 20x4 LCD display.
- **Arduino UNO**: Microcontroller board for program execution.
- **Current and Voltage Sensors**: Connected to specific analog pins for electricity measurement.

The project includes calibration routines (`VoltageCalibration()` and `CurrentCalibration()`) to adjust sensor calibration values (`vCalib` and `cCalib`) for accurate measurement results.

## Components

- Arduino UNO board
- Current Sensor (SCT-013-000)

    <img src="Photos and Videos/Current_Sensor.png" alt="Project Logo" width="200" height="200">

- Voltage Sensor (ZMPT101B)

    <img src="Photos and Videos/Voltage_Sensor.png" alt="Project Logo" width="300" height="250">
- 20x4 LCD Display
- Pushbutton for calibration initiation
- Resistors, wires, capacitors, LEDs, and breadboard (for circuit connections)

## Installation

1. **Hardware Setup**:
   - The voltage sensor and current sensor are connected to the specified analog pins `VOLT_SENSOR_PIN`  and `CURR_SENSOR_PIN` (Must be an analog pin).
   - The LCD display is connected to the Arduino board using appropriate pins.
   - A pushbutton is connected to the designated pin (`BUTTON_PIN`) for calibration initiation and an LED is connected to light during calibration.
   - The Voltage Sensor (ZMPT101B) is connected in parallel with the AC load (in this case the 100 watts lamp).
   - The current Sensor is clipped over one of the two wires of the AC load.
   - Voltage sensor output is taken directly from the ZMPT101B module to the Arduino board.
   - Current sensor output is a a little bit more complicated as this sensor module senses current (0 to 100 Amps ) and outputs current (0 to 50 mA) depending on sensed current so we need to take this current output and change it to a suitable voltage output to connect it to the Arduino board, the following circuit is used to do this conversion:

      <img src="Photos and Videos/CurrentSensorOutputConnection.png" alt="Project Logo" width="410" height="218">

   - Full circuit connection:

      <img src="Photos and Videos/Full_Circuit_Connection.jpeg" alt="Project Logo" width="640" height="360">

2. **Software Setup**:
   - Clone or download this repository.
   - Open the Arduino IDE.
   - Import the necessary libraries (`EmonLib.h` and `LiquidCrystal.h`).
   - Upload the sketch (`digital_electricity_meter.ino`) to your Arduino board.
   - Change in the configuration macros to adjust pins, calibration variables and delay times.
   - The following table lists the configuration macros used in the project along with their descriptions:
        | Macro                   | Description                                      |
        |-------------------------|--------------------------------------------------|
        | `LCD_RS_PIN`            | Pin number for LCD RS (Register Select)          |
        | `LCD_EN_PIN`            | Pin number for LCD EN (Enable)                   |
        | `LCD_D4_PIN`            | Pin number for LCD D4 data line                 |
        | `LCD_D5_PIN`            | Pin number for LCD D5 data line                 |
        | `LCD_D6_PIN`            | Pin number for LCD D6 data line                 |
        | `LCD_D7_PIN`            | Pin number for LCD D7 data line                 |
        | `VOLT_SENSOR_PIN`         | Analog pin for voltage sensor                    |
        | `CURR_SENSOR_PIN`         | Analog pin for current sensor                    |
        | `BUTTON_PIN`            | Pin number for pushbutton (must be an interrupt pin) |
        | `LED_PIN`               | Pin number for LED indicator                     |
        | `BUTTON_DEBOUNCE_DELAY` | Debouncing delay for pushbutton in milliseconds  |
        | `TARGET_VOLTAGE`        | Target RMS voltage for calibration               |
        | `TARGET_CURRENT`        | Target RMS current for calibration               |
        | `CALIBRATION_ITERATIONS`| Number of iterations for calibration             |
        | `VOLTAGE_CALIBRATION_STEP` | Step size for voltage calibration              |
        | `CURRENT_CALIBRATION_STEP` | Step size for current calibration              |
        | `VOLTAGE_ERROR`         | Allowable error margin for voltage calibration   |
        | `CURRENT_ERROR`         | Allowable error margin for current calibration   |

## Usage

1. **Calibration**:
   - Calibration should be done using an AVOmeter, first you connect an AC load then measure this connected load voltage and current, next change the (`TARGET_VOLTAGE` and `TARGET_CURRENT`) macros to the obtained AVOmeter reading. (voltage should be equal to the household electricity voltage and current depends on the load resistance).
   - Press the pushbutton (`BUTTON_PIN`) to initiate calibration.
   - Follow the LCD prompts to complete voltage and current calibration.
   - Red LED should turn on during the calibration process and turn off afterwards.
   - The ZMPT101B voltage sensor module includes a multi-turn potentiometer that can also be used for calibration.
   - If the calibration process is not converging towards the desired values, consider adjusting the following parameters:
      - Number of Iterations (`CALIBRATION_ITERATIONS`):
          Increase the number of calibration iterations to allow more time for the system to adjust and converge towards the optimal calibration values.
      - Step Size (`VOLTAGE_CALIBRATION_STEP`, `CURRENT_CALIBRATION_STEP`):
         Modify the step size used for calibration adjustments. A larger step size can accelerate convergence, while a smaller step size may provide finer adjustments for stability.
      - Allowable Error Margin (`VOLTAGE_ERROR` , `CURRENT_ERROR`):
         Adjust the allowable error margin to define the tolerance level within which the calibrated values are considered acceptable. A wider error margin may allow for greater variability in readings, whereas a narrower margin may prioritize precision.     
   - Experiment with different combinations of these parameters to optimize the calibration process. Fine-tuning these parameters can enhance calibration accuracy and ensure reliable sensor measurements.
   
2. **Measurement**:
   - After calibration, the Arduino will continuously measure and display RMS voltage, current, power, and cumulative energy usage (kWh) on the LCD display.

## Contributing

Contributions to this project are welcome! If you have any suggestions, improvements, or bug fixes, feel free to submit a pull request.

## Acknowledgments

- [OpenEnergyMonitor Project](https://learn.openenergymonitor.org/electricity-monitoring/ct-sensors/interface-with-arduino) for the Energy Monitor Library.
- Arduino and LiquidCrystal Library contributors.
