#include <RH_ASK.h>
#include <SPI.h>  // RadioHead requires this include.

// Must exactly match Guard's RadioHead bitrate and its TX pin configuration.
constexpr uint16_t RADIO_BITRATE = 2000;
constexpr uint8_t RX_PIN = 2;

// bitrate, receive pin, unused transmit pin, unused PTT pin
RH_ASK radio(RADIO_BITRATE, RX_PIN, 3, 4);

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("Serial is working.");

  if (!radio.init()) {
    Serial.println("SRX882 / RadioHead initialization failed.");
    while (true) {
    } 
  }

  Serial.println("Sentinel ready. Waiting for Guard IDs...");
}

void loop() {
  // Extra byte allows us to add a string terminator safely.
  uint8_t received[RH_ASK_MAX_MESSAGE_LEN + 1];
  uint8_t receivedLength = RH_ASK_MAX_MESSAGE_LEN;

  while(true) {
    // True only when RadioHead detects a complete, valid packet.
    if (radio.recv(received, &receivedLength)) {
      received[receivedLength] = '\0';

      Serial.print("Received Guard ID: ");
      Serial.println((char *)received);
    }
  }
}