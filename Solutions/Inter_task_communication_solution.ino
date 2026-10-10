// Solution: Use a Queue. 
// The receiving task goes to sleep (0 CPU usage) until data arrives.
QueueHandle_t dataQueue;

void sensorTask(void *pvParameters) {
  while(1) {
    int sensorData = random(10, 50);
    // Send data to the back of the queue
    xQueueSend(dataQueue, &sensorData, portMAX_DELAY);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void processingTask(void *pvParameters) {
  int receivedData;
  while(1) {
    // Task blocks here efficiently until data is available in the queue
    if(xQueueReceive(dataQueue, &receivedData, portMAX_DELAY) == pdTRUE) {
      Serial.print("Processed Data via Queue: ");
      Serial.println(receivedData);
    }
  }
}

void setup() {
  Serial.begin(115200);
  // Create a queue that can hold 5 integers
  dataQueue = xQueueCreate(5, sizeof(int));
  
  xTaskCreate(sensorTask, "Sensor", 2048, NULL, 1, NULL);
  xTaskCreate(processingTask, "Processor", 2048, NULL, 1, NULL);
}

void loop() {}
