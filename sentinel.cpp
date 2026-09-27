#include "sentinel.h"

SentinelStatus Sentinel::status = SentinelStatus::STANDBY;
unsigned long Sentinel::HEARTBEAT_INT = 120000UL;
