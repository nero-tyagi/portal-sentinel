#ifndef SENTINEL_H
#define SENTINEL_H

#include <Arduino.h>

// CONSTANTS ____________________________________________________

enum class SentinelStatus {
    STANDBY,
    BUSY,
    PAIRING,
    ARMED,
    ALARM,
    ERROR
};

struct Sentinel {
    static constexpr uint16_t RADIO_BITRATE = 2000; // Must exactly match Guard's RadioHead bitrate and its TX pin configuration.

    static constexpr uint8_t RX_PIN = 2; // receiver's data pin
    static constexpr uint8_t CS_PIN = 13; // receiver's switch pin
    static constexpr uint8_t BZ_PIN = 8; // buzzer's pin
    static unsigned long HEARTBEAT_INT;

    static SentinelStatus status;
};

#endif
