// Problem: Sequential execution ignores urgency.
// The critical task is delayed by the non-critical task.
void setup() {
  Serial.begin(115200);
}

void loop() {
  // Low priority heavy task
  Serial.println("Doing non-critical background math...");
  for(volatile int i=0; i<5000000; i++); 

  // High priority critical task (Delayed!)
  Serial.println("CRITICAL: Reading Sensor!");
  delay(100); 
}
