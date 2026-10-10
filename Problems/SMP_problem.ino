// Problem: Single-thread blocking. 
// Task B cannot run until Task A finishes its heavy blocking delay.
void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("Task A starting (Simulating heavy 3s workload)...");
  delay(3000); // Blocks the entire core
  Serial.println("Task A finished.");

  Serial.println("Task B running...");
  delay(500); 
}
