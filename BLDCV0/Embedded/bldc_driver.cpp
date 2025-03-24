#include "bldc_driver.hpp"

// Phase class implementation
Phase::Phase(uint8_t hin, uint8_t sd, uint8_t cur) 
    : hinPin(hin)
    , sdPin(sd)
    , currentPin(cur)
    , pwmDuty(0)
    , current(0) {
    // Configure pins
    pinMode(hinPin, OUTPUT);
    pinMode(sdPin, OUTPUT);
    pinMode(currentPin, INPUT);
    disableOutput();
}

void Phase::setPWM(uint16_t duty) {
    pwmDuty = duty;
    analogWrite(hinPin, duty);
}

void Phase::enableOutput() {
    digitalWrite(sdPin, HIGH);  // Release shutdown
}

void Phase::disableOutput() {
    digitalWrite(sdPin, LOW);   // Assert shutdown
    setPWM(0);
}

void Phase::shutdown() {
    disableOutput();
}

void Phase::release() {
    enableOutput();
}

uint16_t Phase::readCurrent() {
    current = analogRead(currentPin);
    return current;
}

// BLDCDriver class implementation
BLDCDriver::BLDCDriver(uint8_t hinA, uint8_t sdA, uint8_t curA,
                       uint8_t hinB, uint8_t sdB, uint8_t curB,
                       uint8_t hinC, uint8_t sdC, uint8_t curC)
    : phaseA(hinA, sdA, curA)
    , phaseB(hinB, sdB, curB)
    , phaseC(hinC, sdC, curC)
    , currentStep(CommutationStep::STEP1)
    , motorSpeed(0)
    , isRunning(false)
    , overcurrentThreshold(900) {  // Default threshold, can be adjusted
}

void BLDCDriver::begin() {
    initADC();
    initPWM();
    
    // Ensure all phases are disabled at start
    phaseA.disableOutput();
    phaseB.disableOutput();
    phaseC.disableOutput();
}

void BLDCDriver::initADC() {
    // Configure ADC for current sensing
    analogReference(DEFAULT);
    // Perform dummy reads to initialize ADCs
    phaseA.readCurrent();
    phaseB.readCurrent();
    phaseC.readCurrent();
}

void BLDCDriver::initPWM() {
    // Configure PWM frequency and resolution
    // This will depend on your specific microcontroller
    // Example for Arduino:
    // TCCR1B = TCCR1B & B11111000 | B00000001; // Set PWM frequency to 31372.55 Hz
}

void BLDCDriver::setSpeed(uint16_t speed) {
    motorSpeed = speed;
    if (isRunning) {
        updateCommutation();
    }
}

void BLDCDriver::start() {
    if (!isRunning) {
        isRunning = true;
        currentStep = CommutationStep::STEP1;
        phaseA.release();
        phaseB.release();
        phaseC.release();
        updateCommutation();
    }
}

void BLDCDriver::stop() {
    isRunning = false;
    phaseA.disableOutput();
    phaseB.disableOutput();
    phaseC.disableOutput();
}

BLDCDriver::PhaseCurrent BLDCDriver::getCurrents() {
    return {
        phaseA.readCurrent(),
        phaseB.readCurrent(),
        phaseC.readCurrent()
    };
}

bool BLDCDriver::isOverCurrent() {
    auto currents = getCurrents();
    return (currents.phaseA > overcurrentThreshold ||
            currents.phaseB > overcurrentThreshold ||
            currents.phaseC > overcurrentThreshold);
}

void BLDCDriver::setOvercurrentThreshold(uint16_t threshold) {
    overcurrentThreshold = threshold;
}

void BLDCDriver::commutate() {
    if (!isRunning) return;
    
    // Advance to next commutation step
    currentStep = static_cast<CommutationStep>((static_cast<int>(currentStep) + 1) % 6);
    updateCommutation();
}

void BLDCDriver::updateCommutation() {
    // Standard 6-step commutation sequence
    switch (currentStep) {
        case CommutationStep::STEP1: // A-B
            phaseA.setPWM(motorSpeed);
            phaseB.setPWM(0);
            phaseC.disableOutput();
            break;
            
        case CommutationStep::STEP2: // A-C
            phaseA.setPWM(motorSpeed);
            phaseB.disableOutput();
            phaseC.setPWM(0);
            break;
            
        case CommutationStep::STEP3: // B-C
            phaseA.disableOutput();
            phaseB.setPWM(motorSpeed);
            phaseC.setPWM(0);
            break;
            
        case CommutationStep::STEP4: // B-A
            phaseA.setPWM(0);
            phaseB.setPWM(motorSpeed);
            phaseC.disableOutput();
            break;
            
        case CommutationStep::STEP5: // C-A
            phaseA.setPWM(0);
            phaseB.disableOutput();
            phaseC.setPWM(motorSpeed);
            break;
            
        case CommutationStep::STEP6: // C-B
            phaseA.disableOutput();
            phaseB.setPWM(0);
            phaseC.setPWM(motorSpeed);
            break;
    }
} 