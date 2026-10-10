// Problem: Two FreeRTOS tasks modifying the same variable without protection.
// Run this on ESP32. The final count will be unpredictable.
int shared_counter = 0;

void incrementTask(void *pvParameters) {
  for(int i = 0; i < 100000; i++) {
    int temp = shared_counter;
    temp = temp + 1;
    shared_counter = temp;
  }
  vTaskDelete(NULL);
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(incrementTask, "Task1", 2048, NULL, 1, NULL);
  xTaskCreate(incrementTask, "Task2", 2048, NULL, 1, NULL);
}

void loop() {
  Serial.print("Current counter (Expected 200000 eventually, but will be wrong): ");
  Serial.println(shared_counter);
  delay(1000);
}
