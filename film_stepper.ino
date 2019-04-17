// testing a stepper motor with a Pololu A4988 driver board or equivalent
// found: https://forum.arduino.cc/index.php?topic=506797.0

// this version uses micros() to manage timing to allow high step rates to be tested
// and illustrates a simple method for accleration and deceleration

byte directionPin = 9;
byte stepPin = 8;
byte enablePin = 10;

unsigned long prevStepMicros = 0;
unsigned long slowMicrosBetweenSteps = 1500; // microseconds
unsigned long fastMicrosBetweenSteps = 300;
unsigned long stepIntervalMicros;
unsigned long stepAdjustmentMicros;

int stepsPerRev = 200;
int numAccelSteps = 100; // 100 is a half turn of a 200 step motor
int revolutions = 20;

int numSteps = revolutions * stepsPerRev;
int stepsToGo;
byte direction = 1;

void setup() {

    Serial.begin(115200);
    Serial.println("Starting Stepper Demo with acceleration");

    % Set up pins
    pinMode(directionPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
    
    digitalWrite(enablePin, LOW);
    stepAdjustmentMicros = (slowMicrosBetweenSteps - fastMicrosBetweenSteps) / numAccelSteps;
    stepIntervalMicros = slowMicrosBetweenSteps;
    stepsToGo = numSteps;
    digitalWrite(directionPin, direction);

    hello();
}

void loop() {

    moveMotor();

}
