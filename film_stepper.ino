/*
 * FILM lab
 * Functionality for moving horizontal surge motor
 * 
*/
#include <Wire.h>
//#include <LiquidCrystal_I2C.h>

/*
 * Pin setup:
 */
byte directionPin = 9;
byte stepPin = 8;
byte enablePin = 10;
// Pins for the LCD screen
byte sdaPin = 4;
byte sclPin = 5;


/*
 * Motor Properties:
 */
int stepsPerRev = 200;  // = 360/step angle of motor
byte direction = 1;

/*
 * Setup variables for simple movement
 */
// Delays between steps. For slower movements the delay is longer.
unsigned long slowInterval = 1500;
unsigned long fastInterval = 300; // fastest is capped at 300
// number of steps needed to accelerate
int numAccelSteps = 100; // 100 is a half turn of a 200 step motor
int revolutions = 20;
unsigned long stepInterval;
unsigned long stepAdjustment;
int stepCounter;
int totalSteps; 

// counter for simple movement
unsigned long prevStepTime = 0;

/*
 * Initialize LCD screen with I2C backpack
 * 
 * Hardware initialized like so: LiquidCrystal_I2C lcdname(addr,en,rw,rs,d4,d5,d6,d7,bl,blpol);
 */
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, sdaPin, sclPin, 6, 7, 3, POSITIVE);


void setup() {

    Serial.begin(115200);

    // Set up pins
    pinMode(directionPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
    
    digitalWrite(enablePin, LOW);
    /*
     * Setup variables for move motor function
     */
    totalSteps = revolutions * stepsPerRev;
    //totalSteps = getSteps(24.0, 0.891);
    // step change if we're accelerating
    stepAdjustment = (slowInterval - fastInterval) / numAccelSteps;
    stepInterval = slowInterval;
    stepCounter = totalSteps;
    digitalWrite(directionPin, direction);

    screenPrint("Starting up", 500, 3);
}

void loop() {
    moveMotor();

}
