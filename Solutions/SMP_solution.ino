// Solution: Assign tasks to different ESP32 cores (Core 0 and Core 1).
// Task B will run uninterrupted even while Task A is blocking.
void taskA(void *pvParameters) {
  while(1) {
    Serial.println("Task A (Core 0) starting 3s workload...");
    vTaskDelay(3000 / portTICK_PERIOD_MS); 
    Serial.println("Task A finished.");
  }
}

void taskB(void *pvParameters) {
  while(1) {
    Serial.println("Task B (Core 1) running smoothly...");
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreatePinnedToCore(taskA, "TaskA", 2048, NULL, 1, NULL, 0); // Core 0
  xTaskCreatePinnedToCore(taskB, "TaskB", 2048, NULL, 1, NULL, 1); // Core 1
}

void loop() {}
