/* Basic example for esp-wifi-connect (Arduino/PlatformIO scaffold)
 * Note: This is an example interface only. Implementations must be ported
 * into `arduino/src/` before the sketch can compile.
 */

#include <Arduino.h>
#include "wifi_manager.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("esp-wifi-connect Arduino scaffold example");

  // This shows intended API usage. The actual implementation must be
  // present in the library for this to link.
  auto& wifi = WifiManager::GetInstance();
  WifiManagerConfig cfg;
  cfg.ssid_prefix = "ESP32-Example";
  cfg.language = "en-US";
  wifi.Initialize(cfg);
  wifi.StartConfigAp();
}

void loop() {
  delay(1000);
}
