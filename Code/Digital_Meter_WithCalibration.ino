#include <EmonLib.h>
#include <LiquidCrystal.h>

/* Create LCD Instance and Initalize LCD Pins
   Control Pins: (RS -> Pin 7) (EN -> Pin 6)
   Data Pins (D4 -> Pin 5) (D5 -> Pin 4) (D6 -> Pin 3) (D7 -> Pin 8) */
LiquidCrystal lcd(7, 6, 5, 4, 3, 8);

/* Create Energy Monitor Instance */
EnergyMonitor emon;

/* Voltage Sensor and Current Sensor Pins */
#define VoltSensorPin 14 /* Pin 14 is Analog pin 0: A0 */
#define CurrSensorPin 16 /* Pin 16 is Analog pin 2: A2 */

/* Voltage and Current sensors Calibration Variables */
#define VoltCalibration 150   // Used by default
#define CurrCalibration 21.5  // Used by default
float vCalib = 149;           // Used in Calibration function
float cCalib = 21;            // Used in Calibration function

/* Variables for storing Electricity Usage in kWh */
float kWh = 0;
unsigned long lastmillis = millis();

/* Define LED and PushButton Pins */
#define BUTTON_PIN  2 // Pin connected to the pushbutton
#define LED_PIN  12   // Pin connected to the LED
bool CalibrationBtnPressed = false; //PushButton Flag

void setup() 
{
  /* Begin Serial Communication */
  Serial.begin(9600);
  /* Initalize Sensors pins */
  emon.voltage(VoltSensorPin, VoltCalibration, 1.7); // Voltage: input pin, calibration, phase_shift
  emon.current(CurrSensorPin, CurrCalibration); // Current: input pin, calibration.
  /* Intialize 20x4 LCD */
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("Digital Electricity");
  lcd.setCursor(7, 1);
  lcd.print("Meter");
  delay(3000);
  lcd.clear();
  /* Set button pin as input with internal pull-up resistor enabled */
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  /* Set LED pin as output */
  pinMode(LED_PIN, OUTPUT);
  /* Attach interrupt to detect falling edge on the button pin (interrupt 0) */
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
}

void loop() 
{
  emon.calcVI(20, 2000);
  kWh = kWh + emon.apparentPower * (millis() - lastmillis) / 3600000000.0;
  yield();
  /* Serial Communication */
  Serial.print("Vrms: ");
  Serial.print(emon.Vrms, 2);
  Serial.print("V");
  Serial.print("\tIrms: ");
  Serial.print(emon.Irms, 4);
  Serial.print("A");
  Serial.print("\tPower: ");
  Serial.print(emon.apparentPower, 4);
  Serial.print("W");
  Serial.print("\tkWh: ");
  Serial.print(kWh, 5);
  Serial.println("kWh");
  /* LCD */
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vrms:");
  lcd.print(emon.Vrms, 2);
  lcd.print(" V");
  lcd.setCursor(0, 1);
  lcd.print("Irms:");
  lcd.print(emon.Irms, 4);
  lcd.print(" A");
  lcd.setCursor(0, 2);
  lcd.print("Power:");
  lcd.print(emon.apparentPower, 4);
  lcd.print(" W");
  lcd.setCursor(0, 3);
  lcd.print("kWh:");
  lcd.print(kWh, 4);
  lcd.print(" kWh");
  /* Check if Button is pressed */
  if(CalibrationBtnPressed == true)
  {
    VoltageCalibration();
    CurrentCalibration();
    CalibrationBtnPressed = false;
  }

  delay(1000);
  lastmillis = millis();
}

void VoltageCalibration() 
{
  lcd.clear();
  lcd.print("Calibrating Voltage");
  lcd.setCursor(8, 1);
  lcd.print("....");
  lcd.blink();
  digitalWrite(LED_PIN, HIGH); // Turn on LED (turns off after the whole calibration process is complete)
  float targetVoltage = 220; // Target RMS voltage for calibration
  float vCalibStep = 0.05;      // Calibration step size

  for (int i = 0; i < 100; i++) 
  {
    emon.voltage(VoltSensorPin, vCalib, 1.7); // Set voltage calibration
    emon.current(CurrSensorPin, CurrCalibration); // Set current calibration
    emon.calcVI(20, 2000); // Calculate voltage and current values

    if (abs(emon.Vrms - targetVoltage) < 0.1) 
    { 
      // Check if close to target voltage
      lcd.clear();
      lcd.print("Calibration Done!");
      lcd.setCursor(0, 1);
      lcd.print("vCalib = ");
      lcd.print(vCalib, 3); // Display calibration value
      delay(3000);
      lcd.clear();
      break;
    }

      vCalib += (emon.Vrms < targetVoltage) ? vCalibStep : -vCalibStep; // Adjust calibration
  }
}

void CurrentCalibration() 
{
  lcd.clear();
  lcd.print("Calibrating Current");
  lcd.setCursor(8, 1);
  lcd.print("....");
  lcd.blink();

  float targetCurrent = 0.4545; // Target RMS current for calibration
  float cCalibStep = 0.01;     // Calibration step size

  for (int i = 0; i < 100; i++)
  { 
    emon.voltage(VoltSensorPin, vCalib, 1.7); // Set voltage calibration
    emon.current(CurrSensorPin, cCalib);      // Set current calibration
    emon.calcVI(20, 2000);                    // Calculate voltage and current values

    if (abs(emon.Irms - targetCurrent) < 0.005) 
    { // Check if close to target current
      lcd.clear();
      lcd.print("Calibration Done!");
      lcd.setCursor(0, 1);
      lcd.print("cCalib = ");
      lcd.print(cCalib, 3); // Display calibration value 
      lcd.noBlink();
      delay(3000);
      digitalWrite(LED_PIN, LOW); // Turn off LED
      break;
    }

    cCalib += (emon.Irms < targetCurrent) ? cCalibStep : -cCalibStep; // Adjust calibration
  }
}

// Interrupt service routine (ISR) for button press detection
void buttonISR() 
{
  /* Debounce Protection */
  delay(80);
  if(digitalRead(BUTTON_PIN) != 0)
  {
    return; 
  }
  /* Changing Button Flag */
  CalibrationBtnPressed = true;
}








