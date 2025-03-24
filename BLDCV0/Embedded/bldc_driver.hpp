#ifndef BLDC_DRIVER_HPP
#define BLDC_DRIVER_HPP

#include <cstdint>

class Phase {
private:
    const uint8_t hinPin;     // PWM pin for high-side
    const uint8_t sdPin;      // Shutdown pin (active low)
    const uint8_t currentPin; // Current sense ADC pin
    uint16_t pwmDuty;        // Current PWM duty cycle
    uint16_t current;        // Current sense value

public:
    Phase(uint8_t hin, uint8_t sd, uint8_t cur);
    void setPWM(uint16_t duty);
    void enableOutput();
    void disableOutput();
    void shutdown();
    void release();
    uint16_t readCurrent();
    uint16_t getCurrentValue() const { return current; }
};

class BLDCDriver {
public:
    enum class CommutationStep {
        STEP1, STEP2, STEP3, STEP4, STEP5, STEP6
    };

    struct PhaseCurrent {
        uint16_t phaseA;
        uint16_t phaseB;
        uint16_t phaseC;
    };

private:
    Phase phaseA;
    Phase phaseB;
    Phase phaseC;
    CommutationStep currentStep;
    uint16_t motorSpeed;     // Current motor speed (PWM duty cycle)
    bool isRunning;
    uint16_t overcurrentThreshold;

    void initADC();
    void initPWM();
    void updateCommutation();

public:
    BLDCDriver(uint8_t hinA, uint8_t sdA, uint8_t curA,
               uint8_t hinB, uint8_t sdB, uint8_t curB,
               uint8_t hinC, uint8_t sdC, uint8_t curC);
    
    void begin();
    void setSpeed(uint16_t speed);
    void start();
    void stop();
    void commutate();
    PhaseCurrent getCurrents();
    bool isOverCurrent();
    void setOvercurrentThreshold(uint16_t threshold);
};

#endif // BLDC_DRIVER_HPP 