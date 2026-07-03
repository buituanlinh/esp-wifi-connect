#include <Arduino.h>
#include "assets.h"

// Auto-generated embed of wifi_configuration.html (truncated for scaffold)
const char wifi_configuration_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html><head><meta charset="utf-8"><title>WiFi Config</title></head><body>
<h1>ESP WiFi Config (scaffold)</h1>
<form action="/save" method="post">SSID: <input name="ssid"><br>Password: <input name="pw"><br><input type="submit" value="Save"></form>
</body></html>
)rawliteral";

// Simple done page
const char wifi_configuration_done_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html><body><h1>Configuration Saved</h1><p>Close this page.</p></body></html>
)rawliteral";
