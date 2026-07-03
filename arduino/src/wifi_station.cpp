#include "wifi_station.h"
#include "ssid_manager.h"
#include <WiFi.h>

WifiStation::WifiStation() {}
WifiStation::~WifiStation() { Stop(); }

void WifiStation::AddAuth(const std::string &&ssid, const std::string &&password) {
    SsidManager::GetInstance().AddSsid(ssid, password);
}

void WifiStation::Start() {
    auto& ssids = SsidManager::GetInstance().GetSsidList();
    if (ssids.empty()) return;
    // Try first saved ssid
    const auto& s = ssids.front();
    WiFi.begin(s.ssid.c_str(), s.password.c_str());
}

void WifiStation::Stop() {
    WiFi.disconnect(true);
}

bool WifiStation::IsConnected() {
    return WiFi.status() == WL_CONNECTED;
}

bool WifiStation::WaitForConnected(int timeout_ms) {
    unsigned long start = millis();
    while (millis() - start < (unsigned long)timeout_ms) {
        if (IsConnected()) return true;
        delay(100);
    }
    return false;
}

int8_t WifiStation::GetRssi() {
    return WiFi.RSSI();
}

std::string WifiStation::GetSsid() const {
    return std::string(WiFi.SSID().c_str());
}

std::string WifiStation::GetIpAddress() const {
    return WiFi.localIP().toString().c_str();
}

uint8_t WifiStation::GetChannel() {
    return WiFi.channel();
}

void WifiStation::SetPowerSaveLevel(WifiPowerSaveLevel level) {
    // Arduino WiFi has limited power save control; no-op for now
}

void WifiStation::OnConnect(std::function<void(const std::string& ssid)> on_connect) {}
void WifiStation::OnConnected(std::function<void(const std::string& ssid)> on_connected) {}
void WifiStation::OnDisconnected(std::function<void(int reason)> on_disconnected) {}
void WifiStation::OnScanBegin(std::function<void()> on_scan_begin) {}
void WifiStation::SetScanIntervalRange(int min_interval_seconds, int max_interval_seconds) {}
void WifiStation::SetFailureRetryCnt(uint8_t cnt) {}
