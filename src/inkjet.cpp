#include "inkjet.h"
#include "pin.h"
#include "config.h"
#include <Arduino.h>

long lastPulse = 0;
uint16_t strip_buffer = 4096;

const uint8_t NOZZLE_PIN[12] = {
    INK_PIN_0, INK_PIN_1, INK_PIN_2, INK_PIN_3,
    INK_PIN_4, INK_PIN_5, INK_PIN_6, INK_PIN_7,
    INK_PIN_8, INK_PIN_9, INK_PIN_10, INK_PIN_11
};

void hpc6602_init(){
  
    // Initialize all nozzle pins as outputs
    for (byte n = 0; n < 12; n++) {
        pinMode(NOZZLE_PIN[n], OUTPUT);
        digitalWriteFast(NOZZLE_PIN[n], LOW);  // Set all nozzles to LOW initially
    }

}

void nozzle_trigger(const uint16_t &strip_code){
    if (micros() - lastPulse >= DEATH_PULSE_RATE && strip_code < 4096) {
        // Fire all nozzles corresponding to bits set in strip_code

        digitalWriteFast(13, HIGH); // Optional: Set a debug pin high to indicate firing
        for (byte n = 0; n < 12; n++) {
          if (strip_code & (1 << n)) {
            digitalWriteFast(NOZZLE_PIN[n], HIGH);  // Fire this nozzle
            delayMicroseconds(6);  // Pulse duration
            digitalWriteFast(NOZZLE_PIN[n], LOW);
            delayNanoseconds(500);  // Pulse duration
          }
        }
    
    
        lastPulse = micros();
      }
}

void nozzle_trigger_individual(const uint8_t &nozzle_code){
  if (micros() - lastPulse >= DEATH_PULSE_RATE && nozzle_code < 12) {
      // Fire all nozzles corresponding to bits set in strip_code
      digitalWriteFast(13, HIGH); // Optional: Set a debug pin high to indicate firing

      if (nozzle_code >= 0 && nozzle_code < 12) {
        digitalWriteFast(NOZZLE_PIN[nozzle_code], HIGH);  // Fire this nozzle
        delayMicroseconds(6);  // Pulse duration
        digitalWriteFast(NOZZLE_PIN[nozzle_code], LOW);
        delayNanoseconds(500);  // Pulse duration
      }
    
      digitalWriteFast(13, LOW); // Optional: Set a debug pin high to indicate firing

      lastPulse = micros();
    }
}