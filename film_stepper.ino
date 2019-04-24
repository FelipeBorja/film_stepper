// testing a stepper motor with a Pololu A4988 driver board or equivalent
// found: https://forum.arduino.cc/index.php?topic=506797.0

// this version uses micros() to manage timing to allow high step rates to be tested
// and illustrates a simple method for accleration and deceleration

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

byte directionPin = 9;
byte stepPin = 8;
byte enablePin = 10;
// Pins for the LCD screen
byte sdaPin = 4;
byte sclPin = 5;

// Predetermined times in microseconds
unsigned long prevStepMicros = 0;
// Delays between steps. For slower movements the delay is longer.
unsigned long slowMicrosBetweenSteps = 1500;
unsigned long fastMicrosBetweenSteps = 300;
unsigned long stepIntervalMicros;
unsigned long stepAdjustmentMicros;

// Steps and revolutions
int stepsPerRev = 200;
// number of steps needed to accelerate
int numAccelSteps = 100; // 100 is a half turn of a 200 step motor
int revolutions = 20;

int numSteps = revolutions * stepsPerRev;
int stepsToGo;
byte direction = 1;

// Initialize LCD screen with I2C backpack.
// Hardware initialized like so: LiquidCrystal_I2C lcdname(addr,en,rw,rs,d4,d5,d6,d7,bl,blpol);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, sdaPin, sclPin, 6, 7, 3, POSITIVE);


void setup() {

    Serial.begin(115200);
    Serial.println("Starting Stepper Demo with acceleration");

    // Set up pins
    pinMode(directionPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
    
    digitalWrite(enablePin, LOW);
    // If we want to accelerate, we need to slowly increase the step sizes over time.
    stepAdjustmentMicros = (slowMicrosBetweenSteps - fastMicrosBetweenSteps) / numAccelSteps;
    stepIntervalMicros = slowMicrosBetweenSteps;
    stepsToGo = numSteps;
    digitalWrite(directionPin, direction);

    screenPrint("starting up", 500, 3);
}

void loop() {

    moveMotor();

}
