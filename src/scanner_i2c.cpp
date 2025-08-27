#include <Arduino.h>
#include <Wire.h>

void setup() {
  Wire.setSDA(PB7); // Sostituisci con il tuo pin SDA
  Wire.setSCL(PB6); // Sostituisci con il tuo pin SCL
  Wire.begin();
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Serial.println("\nI2C Scanner");
}

void loop() {
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("Dispositivo I2C trovato all'indirizzo 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    } else if (error == 4) {
      Serial.print("Errore sconosciuto all'indirizzo 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("Nessun dispositivo I2C trovato");
  } else {
    Serial.println("... fatto.");
  }
  delay(5000); // Attendi 5 secondi prima di scansionare di nuovo
}