# esp-wifi-connect Arduino Library

This folder is an Arduino/PlatformIO library scaffold for `esp-wifi-connect`.
It contains the library metadata, public headers, implementation stubs, and a basic example sketch.

## Folder structure

- `library.properties` - Arduino library metadata
- `src/` - Arduino library implementation files
- `src/include/` - public headers exposed to sketches
- `examples/Basic/Basic.ino` - example Arduino sketch
- `platformio.ini` - PlatformIO example project config

## Deploy to Arduino IDE

### Option 1: Install as a library folder

1. Copy the entire `arduino/` folder into your Arduino libraries directory:
   - Windows: `Documents/Arduino/libraries/esp-wifi-connect`
   - macOS: `~/Documents/Arduino/libraries/esp-wifi-connect`
   - Linux: `~/Arduino/libraries/esp-wifi-connect`
2. Restart Arduino IDE.
3. Open the example from: `File > Examples > esp-wifi-connect > Basic`.

### Option 2: Use the library from a local sketch folder

1. Create a sketch in your Arduino workspace.
2. Copy the `arduino/src/` implementation files and `arduino/src/include/` headers into your sketch or library folder.
3. Make sure `library.properties` stays in the library root if using Arduino library packaging.

## Example usage in `Basic.ino`

```cpp
#include <Arduino.h>
#include "wifi_manager.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("esp-wifi-connect Arduino scaffold example");

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
```

## Notes

- `library.properties` defines the Arduino library metadata used by the IDE.
- The example sketch is intentionally minimal and demonstrates the public API.
- If the Arduino IDE reports missing symbols or headers, make sure the library folder is installed correctly and that the implementation files are present in `arduino/src/`.
- For PlatformIO testing, run from the `arduino` folder:

```bash
platformio run -e esp32dev
```

## Current status

This repository currently holds an Arduino scaffold. Some ESP-IDF-specific features may require additional porting to work fully under Arduino.
