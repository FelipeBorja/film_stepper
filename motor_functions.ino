

void moveMotor() {
    // only move the designated # of steps
    if (stepsToGo > 0) {
        // we keep a count of the # microseconds that have gone by
        // if # is greater then the delay we want, then we should move
        // Note: micros() has a resolution of 4 microseconds, and will always be a multiple of 4
        // micros() will reset to 0 after 70 min of running the arduino (so it should stop running)
        if (micros() - prevStepMicros >= stepIntervalMicros) {
            // increase the overall time count by the step interval
            prevStepMicros += stepIntervalMicros;
            // move the motor a step
            singleStep();
            stepsToGo --;
            // if we're at the end of our steps left and within the # steps needed for acceleration
            if (stepsToGo <= numAccelSteps) {
                // slow down to the slow speed
                if (stepIntervalMicros < slowMicrosBetweenSteps) {
                    stepIntervalMicros += stepAdjustmentMicros;
                }
            }
            // if we're starting off, and haven't accelerated fully yet
            else {
                // decrease the delay -> which increases the speed
                if (stepIntervalMicros > fastMicrosBetweenSteps) {
                    stepIntervalMicros -= stepAdjustmentMicros;
                }
            }
        }
    }
    else {
          Serial.print("reached end. stepDelta: ");
          Serial.println(stepAdjustmentMicros);
//        direction = ! direction;
//        digitalWrite(directionPin, direction);
//            // next two lines just for the demo
//        delay(2000);
//        Serial.println("Changing direction");
//        stepsToGo = numSteps;
//        prevStepMicros = micros();
    }
}

void singleStep() {

    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin, LOW);

}
