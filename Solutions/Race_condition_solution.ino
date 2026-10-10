// Solution: Use a Mutex to "lock" the variable. 
// Only one task can modify it at a time.
SemaphoreHandle_t mutex;
int shared_counter = 0;

void incrementTask(void *pvParameters) {
  for(int i = 0; i < 100000; i++) {
    // Take the mutex before modifying (Wait indefinitely if someone else has it)
    if(xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
      int temp = shared_counter;
      temp = temp + 1;
      shared_counter = temp;
      xSemaphoreGive(mutex); // Give it back
    }
  }
  vTaskDelete(NULL);
}

void setup() {
  Serial.begin(115200);
  mutex = xSemaphoreCreateMutex();
  
  xTaskCreate(incrementTask, "Task1", 2048, NULL, 1, NULL);
  xTaskCreate(incrementTask, "Task2", 2048, NULL, 1, NULL);
}

void loop() {
  Serial.print("Protected counter (Will safely reach 200000): ");
  Serial.println(shared_counter);
  delay(1000);
}
