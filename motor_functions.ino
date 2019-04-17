

void moveMotor() {
    if (stepsToGo > 0) {
        if (micros() - prevStepMicros >= stepIntervalMicros) {
            prevStepMicros += stepIntervalMicros;
            singleStep();
            stepsToGo --;
            if (stepsToGo <= numAccelSteps) {
                if (stepIntervalMicros < slowMicrosBetweenSteps) {
                    stepIntervalMicros += stepAdjustmentMicros;
                }
            }
            else {
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
//        // next two lines just for the demo
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
