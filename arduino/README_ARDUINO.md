This folder contains a scaffold to package `esp-wifi-connect` as an Arduino/PlatformIO library.

What is included:

- `library.properties` - Arduino library metadata
- `platformio.ini` - example PlatformIO project config for `framework = arduino`
- `src/include/` - copies of public header files from the component (API surface)
- `examples/Basic/Basic.ino` - minimal example sketch showing usage

Next steps to make it buildable under Arduino/PlatformIO:

1. Port or reimplement the C++ `.cc` files to `arduino/src/` (implementation). Many files rely on ESP-IDF APIs (`esp_http_server`, `esp_event`, `nvs_flash`, etc.) which need Arduino-core compatible replacements or compatibility wrappers.
2. Move assets (HTML) to PROGMEM or LittleFS/Spiffs and adapt the code to serve them.
3. Test build under PlatformIO and iterate on missing APIs / includes.

To test the example with PlatformIO, run in the `arduino` folder:

```ini
platformio run -e esp32dev
```
