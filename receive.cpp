#include "receive.h"
#include "message.h"
#include "ArduinoJson.h"

Message unwrapMessage(const char* message) {
  Serial.println(message);
  JsonDocument doc;

  DeserializationError err = deserializeJson(doc, message);

  if (!err) {
    int type = doc["type"];
    const char* id = doc["id"];
    const char* text = doc["msg"];

    MessageType msgType = static_cast<MessageType>(type);
    DeviceID deviceID(id);
    Message message(msgType, deviceID, text);
    return message;
  }

  return Message(MessageType::ERROR);
}
