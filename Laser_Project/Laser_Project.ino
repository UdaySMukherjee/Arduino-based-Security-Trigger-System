/*
  ==========================================
   Security Trigger System - Arduino Sketch
   Author: Uday Sankar Mukherjee
   YouTube: USMTechLab
  ==========================================

   Description:
   This program simulates a sensor-triggered alarm system using
   LEDs, a speaker, and a sensor input. It features:
     - Arm/Disarm mode toggle
     - Calibration-based sensitivity thresholding
     - Audio and visual alert system

   Pins:
     A0  - Sensor Input
     4   - Red LED (Armed)
     5   - Green LED (Disarmed)
     6   - Button to Arm/Disarm
     7   - Triggered LED 1
     8   - Triggered LED 2
     12  - Speaker

*/

const int triggeredLED  = 7;
const int triggeredLED2 = 8;
const int RedLED        = 4;
const int GreenLED      = 5;
const int inputPin      = A0;
const int speakerPin    = 12;
const int armButton     = 6;

boolean isArmed      = true;
boolean isTriggered  = false;
int buttonVal        = 0;
int prev_buttonVal   = 0;
int reading          = 0;
int threshold        = 0;

const int lowrange   = 2000;
const int highrange  = 4000;

void setup() {
  // Configure I/O pins
  pinMode(triggeredLED, OUTPUT);
  pinMode(triggeredLED2, OUTPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  pinMode(armButton, INPUT);

  // Startup blink to show system boot
  digitalWrite(triggeredLED, HIGH);
  delay(500);
  digitalWrite(triggeredLED, LOW);

  // Calibrate and set initial arm/disarm state
  calibrate();
  setArmedState();
}

void loop() {
  // Read sensor value
  reading = analogRead(inputPin);

  // Read arm/disarm button
  buttonVal = digitalRead(armButton);
  if ((buttonVal == HIGH) && (prev_buttonVal == LOW)) {
    setArmedState();
    delay(500); // debounce delay
  }
  prev_buttonVal = buttonVal;

  // Trigger system if reading crosses threshold
  if (isArmed && (reading < threshold)) {
    isTriggered = true;
  }

  // If triggered, activate alert sequence
  if (isTriggered) {
    // Rising tone
    for (int i = lowrange; i <= highrange; i++) {
      tone(speakerPin, i, 250);
    }

    // Falling tone
    for (int i = highrange; i >= lowrange; i--) {
      tone(speakerPin, i, 250);
    }

    // Flashing LEDs
    for (int i = 0; i < 5; i++) {
      digitalWrite(triggeredLED, HIGH);
      delay(50);
      digitalWrite(triggeredLED, LOW);
      delay(50);
      digitalWrite(triggeredLED2, HIGH);
      delay(50);
      digitalWrite(triggeredLED2, LOW);
      delay(50);
    }
  }

  delay(20); // loop pacing
}

void setArmedState() {
  if (isArmed) {
    // Switch to Disarmed mode
    digitalWrite(GreenLED, HIGH);
    digitalWrite(RedLED, LOW);
    isTriggered = false;
    isArmed = false;
  } else {
    // Switch to Armed mode with confirmation tone
    digitalWrite(GreenLED, LOW);
    digitalWrite(RedLED, HIGH);
    tone(speakerPin, 220, 125);
    delay(200);
    tone(speakerPin, 196, 250);
    isArmed = true;
  }
}

void calibrate() {
  int sample = 0;
  int baseline = 0;
  const int min_diff = 200;
  const int sensitivity = 50;
  int success_count = 0;

  // Ensure both LEDs are off during calibration
  digitalWrite(RedLED, LOW);
  digitalWrite(GreenLED, LOW);

  // Collect 10 samples for smoothing
  for (int i = 0; i < 10; i++) {
    sample += analogRead(inputPin);
    digitalWrite(GreenLED, HIGH);
    delay(50);
    digitalWrite(GreenLED, LOW);
    delay(50);
  }

  // Detect baseline threshold from signal spikes
  do {
    sample = analogRead(inputPin);
    if (sample > baseline + min_diff) {
      success_count++;
      threshold += sample;

      digitalWrite(GreenLED, HIGH);
      delay(100);
      digitalWrite(GreenLED, LOW);
      delay(100);
    } else {
      success_count = 0;
      threshold = 0;
    }
  } while (success_count < 3);

  // Average and apply sensitivity offset
  threshold = (threshold / 3) - sensitivity;

  // Confirm calibration with tone
  tone(speakerPin, 196, 250);
  delay(200);
  tone(speakerPin, 220, 125);
}
