#include <RH_ASK.h>
#include <SPI.h>  // RadioHead requires this include.
#include "receive.h"

// bitrate, receive pin, unused transmit pin, unused PTT pin
RH_ASK radio(Sentinel::RADIO_BITRATE, Sentinel::RX_PIN, 3, 4);

void setup() {
  Serial.begin(115200);

  if (!radio.init()) {
    while (true) {
        Sentinel::status = SentinelStatus::ERROR;
    }
  }

  // Turning on the CS pin of the RX
  pinMode(Sentinel::CS_PIN, OUTPUT);
  digitalWrite(Sentinel::CS_PIN, HIGH);
}

void loop() {
  // Extra byte allows us to add a string terminator safely.
  uint8_t received[RH_ASK_MAX_MESSAGE_LEN + 1];

  while(true) {
    uint8_t receivedLength = RH_ASK_MAX_MESSAGE_LEN;

    // True only when RadioHead detects a complete, valid packet.
    if (radio.recv(received, &receivedLength)) {
      received[receivedLength] = '\0'; // closing the string

      Message transmission;
      transmission = unwrapMessage(reinterpret_cast<const char*>(received));

      if (transmission.getType() == MessageType::ALARMON) {
        Sentinel::status = SentinelStatus::ALARM;
        digitalWrite(Sentinel::BZ_PIN, HIGH);
      } else if (transmission.getType() == MessageType::ALARMOFF) {
        Sentinel::status = SentinelStatus::ARMED;
        digitalWrite(Sentinel::BZ_PIN, LOW);
      } else if (transmission.getType() == MessageType::HEARTBEAT) {
        Sentinel::status = SentinelStatus::ARMED;
        digitalWrite(Sentinel::BZ_PIN, LOW);
      };
    }
  }
}
