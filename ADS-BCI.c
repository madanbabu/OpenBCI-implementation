#include <ADS1299.h>

// Initialize ADS1299 object
ADS1299 ADS;

// Pin assignments
const int CS_PIN = 10;    // Chip select pin
const int DRDY_PIN = 9;   // Data ready pin
const int SCK_PIN = 13;   // SPI clock pin
const int MISO_PIN = 12; // SPI master input slave output pin
const int MOSI_PIN = 11; // SPI master out slave in pin

void setup() {
  Serial.begin(115200);
  Serial.println("ADS1299 Bridge Started!");

  // Configure pins as outputs
  pinMode(CS_PIN, OUTPUT);
  pinMode(DRDY_PIN, INPUT);

  // Initialize ADS1299
  ADS.setup(DRDY_PIN, CS_PIN);
  
  // Reset the device
  ADS.RESET();

  // Configure device settings
  ADS.WREG(CONFIG1, 0x1101); // Enable PGA x16, SPI mode, 250Hz sample rate
  ADS.WREG(CONFIG2, 0x0000);
  ADS.WREG(CONFIG3, 0x0000);
  
  // Start data conversions
  ADS.START();
}

void loop() {
  // Read data from all channels
  uint16_t* data = new uint16_t[8]; // Allocate memory for 8 channels

  // Read data from each channel
  for (int i = 0; i < 8; i++) {
    ADS.updateData(data[i]);
  }

  // Print data
  Serial.print("Channel Data: ");
  for (int i = 0; i < 8; i++) {
    Serial.print(data[i], HEX);
    if (i < 7) Serial.print(", ");
  }
  Serial.println();

  delay(100); // Wait for next sample
}
