#include <Arduino.h>
#include "inkjet.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Inkjet Printer Test");
  // Initialize the nozzle pins 
  hpc6602_init();

    pinMode(3, INPUT_PULLUP); // Set A as input with pull-up resistor
    pinMode(4, INPUT_PULLUP); // Set A as input with pull-up resistor
    pinMode(5, INPUT_PULLUP); // Set A as input with pull-up resistor
    pinMode(6, INPUT_PULLUP); // Set A as input with pull-up resistor
    pinMode(7, INPUT_PULLUP); // Set A as input with pull-up resistor

  pinMode(13, OUTPUT); // Optional: Set a debug pin for indication
  Serial.println("Nozzle pins initialized.");
}

void loop() {

    bool P = digitalReadFast(7);
    static bool lock = false;
    if(P == HIGH && !lock) {
        //nozzle_trigger(0xFFF); // Example: Trigger all nozzles
        bool A = digitalReadFast(3);
        bool B = digitalReadFast(4);
        bool C = digitalReadFast(5);
        bool D = digitalReadFast(6);

        // Multiplexing the nozzles
        int nozzle_code = 0;
        if(A) nozzle_code |= (1 << 0); // Set bit 0 if A is HIGH
        if(B) nozzle_code |= (1 << 1); // Set bit 1 if B is HIGH
        if(C) nozzle_code |= (1 << 2); // Set bit 2 if C is HIGH
        if(D) nozzle_code |= (1 << 3); // Set bit 3 if D is HIGH
        
        nozzle_trigger_individual(nozzle_code); // Trigger the nozzles based on the multiplexing
        lock = true; // Set lock to true to prevent re-triggering
        Serial.println("Triggering nozzles with code: " + String(nozzle_code, BIN)); // Print in binary forma
        Serial.println("Triggering nozzles with code: " + String(nozzle_code)); // Print in binary forma

    } else if(P == LOW) {
        if(lock)
            lock = false; // Reset lock to allow re-triggering
    }

    //delay(100);
/*
  //Gather Serial command for nozzle trigger (input a numbler from 0 - 4095> to trigger the nozzles during one second)
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n'); // Read until newline

        if(input.startsWith("M")){
            //Serial.flush(); // Flush the serial buffer if 'M' is received
            Serial.write(0);
            return;
        }

        int strip_code = input.toInt(); // Convert to integer
        

        if (strip_code >= 0 && strip_code < 4096) {
            Serial.print("Triggering nozzles with code: ");
            Serial.println(strip_code, BIN); // Print in binary format
            //digitalWriteFast(13, HIGH); // Optional: Set a debug pin high to indicate firing
            long now = millis();
            while (millis() - now < 1000) { // Trigger for 1 second
                nozzle_trigger(strip_code); // Trigger the nozzles
                delayMicroseconds(1000); // Small delay to avoid overwhelming the system
            }
            //digitalWriteFast(13, LOW); // Optional: Set a debug pin low to indicate firing
            Serial.println("Done triggering nozzles.");
        } else {
            Serial.println("Invalid code. Please enter a number between 0 and 4095.");
        }
    }

    // Add a small delay to avoid overwhelming the serial buffer
    delay(100);
    */
}