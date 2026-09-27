#ifndef RECEIVE_H
#define RECEIVE_H

#include <Arduino.h>
#include <RH_ASK.h> // RadioHead – radio transceiver library
#include "message.h"

Message unwrapMessage(const char* message);

#endif