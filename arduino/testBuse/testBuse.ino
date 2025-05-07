

int debug_nozzle = 11;

void setup() {
  pinMode(3, OUTPUT); //A
  pinMode(4, OUTPUT); //B
  pinMode(5, OUTPUT); //C
  pinMode(6, OUTPUT); //D
  pinMode(7, OUTPUT); //D

    // put your main code here, to run repeatedly:
    bool A = debug_nozzle & (1 << 0); // Set A based on the bit 0 of debug_nozzle
    bool B = debug_nozzle & (1 << 1); // Set B based on the bit 1 of debug_nozzle
    bool C = debug_nozzle & (1 << 2); // Set C based on the bit 2 of debug_nozzle
    bool D = debug_nozzle & (1 << 3); // Set D based on the bit 3 of debug_nozzle
    
    digitalWrite(3, A ? HIGH : LOW); // Write A to pin 3
    digitalWrite(4, B ? HIGH : LOW); // Write B to pin 4
    digitalWrite(5, C ? HIGH : LOW); // Write C to pin 5
    digitalWrite(6, D ? HIGH : LOW); // Write D to pin 6
}

void loop() {
  delay(1000);
  digitalWrite(7, HIGH); //Pulse
  delay(1);
  digitalWrite(7, LOW); //Pulse
}
