/*
 * Function for simple movement with acceleration to reach higher speeds
 * Parameters and how they affect function:
 * slowInterval -> slower speed of motor
 * fastInterval -> faster speed of motor
 * numAccelSteps -> slower or faster acceleration
 * revolutions -> how far the motor will go
 * 
 * For testing a stepper motor with a Pololu A4988 driver board or equivalent
 * found: https://forum.arduino.cc/index.php?topic=506797.0
 * This uses micros() to manage timing to allow high step rates to be tested, 
 * uses a simple method for accleration and deceleration.
 * Note: micros() has a resolution of 4 microseconds, and will always be a multiple of 4
 * micros() will reset to 0 after 70 min of running the arduino (so it should stop running)
 */
void moveMotor() {
    // only move the designated # of steps
    if (stepCounter > 0) {
      /*
       * prevStepTime = count of # microseconds that have gone by
       * Only move if difference is > than the desired delay
       * 
       */
        if (micros() - prevStepTime >= stepInterval) {
            // increase the overall time count by the step interval
            prevStepTime += stepInterval;
            // move the motor a step
            singleStep();
            stepCounter --;
            // if we're at the end of our steps left and within the # steps needed for acceleration
            if (stepCounter <= numAccelSteps) {
                // slow down to the slow speed
                if (stepInterval < slowInterval) {
                    stepInterval += stepAdjustment;
                }
            }
            // if we're starting off, and haven't accelerated fully yet
            else {
                // decrease the delay -> which increases the speed
                if (stepInterval > fastInterval) {
                    stepInterval -= stepAdjustment;
                }
            }
        }
    }
    else {
          Serial.print("reached end. stepDelta: ");
          Serial.println(stepAdjustment);
          /*
           * Code for switching direction
           */
        direction = ! direction;
        digitalWrite(directionPin, direction);
            // next two lines just for the demo
        Serial.println("Changing direction");
        lcd.clear();
        lcd.print("Changing direction");
        delay(3000);
        lcd.clear();
        stepCounter = totalSteps;
        prevStepTime = micros();
    }
}

void singleStep() {

    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin, LOW);

}

/*
 * Can be used to calculate the number of steps that should be input 
 * in order to go a certain distance
 * travelDist -> in inches
 * pitchD -> in inches
 * Has a cap distance to make sure we don't crash the carriage
 */
int getSteps(double travelDist, double pitchD) {
    double maxDist = 30.0;
    if (travelDist > maxDist) {
      travelDist = maxDist;
      Serial.println("WARNING: lower travelDist (currently capped)");
    }
    int revs = travelDist / (pitchD*3.14159);
    int steps = revs * stepsPerRev;
    return steps;
}

/*
 * Used to determine the interval value (delay) required for specific
 * speed of the motor
 * metersPerSec -> speed
 * travelDist -> in inches
 */
int getInterval(int steps, double metersPerSec, double travelDist) {
    double ftPerSec = 3.28084*metersPerSec;
    double timeSec = (travelDist/12) / ftPerSec;
    int interval = (timeSec*1000000)/steps;
    return interval;
}
