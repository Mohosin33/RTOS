// Solution: Assign a higher priority number to the critical task.
// FreeRTOS will preempt the low priority task to run the critical one instantly.
void lowPriorityTask(void *pvParameters) {
  while(1) {
    Serial.println("Doing non-critical background math...");
    for(volatile int i=0; i<5000000; i++); 
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void highPriorityTask(void *pvParameters) {
  while(1) {
    Serial.println("CRITICAL: Reading Sensor INSTANTLY!");
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Runs exactly every 1 second
  }
}

void setup() {
  Serial.begin(115200);
  // Priority 1 (Low) vs Priority 2 (High)
  xTaskCreate(lowPriorityTask, "Low", 2048, NULL, 1, NULL);
  xTaskCreate(highPriorityTask, "High", 2048, NULL, 2, NULL);
}

void loop() {}
