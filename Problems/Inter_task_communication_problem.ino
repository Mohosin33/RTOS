// Problem: Polling global variables wastes CPU.
bool dataReady = false;
int sensorData = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Simulating sensor reading every 2 seconds
  if (millis() % 2000 == 0 && !dataReady) {
    sensorData = random(10, 50);
    dataReady = true;
    delay(1); // Prevent rapid firing in the same millisecond
  }

  // CPU constantly spins checking this flag (Polling)
  if (dataReady) {
    Serial.print("Processed Data: ");
    Serial.println(sensorData);
    dataReady = false;
  }
}
