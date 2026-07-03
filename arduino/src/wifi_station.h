/* Copied public header for Arduino scaffold. Implementation must be provided in arduino/src/ */

#ifndef _WIFI_STATION_H_
#define _WIFI_STATION_H_

#include <string>
#include <vector>
#include <functional>

enum class WifiPowerSaveLevel
{
    LOW_POWER,
    BALANCED,
    PERFORMANCE,
};

struct WifiApRecord
{
    std::string ssid;
    std::string password;
    int channel;
    int authmode;
    uint8_t bssid[6];
};

class WifiStation
{
public:
    WifiStation();
    ~WifiStation();

    WifiStation(const WifiStation &) = delete;
    WifiStation &operator=(const WifiStation &) = delete;

    void AddAuth(const std::string &&ssid, const std::string &&password);
    void Start();
    void Stop();
    bool IsConnected();
    bool WaitForConnected(int timeout_ms = 10000);
    int8_t GetRssi();
    std::string GetSsid() const;
    std::string GetIpAddress() const;
    uint8_t GetChannel();
    void SetPowerSaveLevel(WifiPowerSaveLevel level);

    void OnConnect(std::function<void(const std::string &ssid)> on_connect);
    void OnConnected(std::function<void(const std::string &ssid)> on_connected);
    void OnDisconnected(std::function<void(int reason)> on_disconnected);
    void OnScanBegin(std::function<void()> on_scan_begin);
    void SetScanIntervalRange(int min_interval_seconds, int max_interval_seconds);
    void SetFailureRetryCnt(uint8_t cnt);
};

#endif // _WIFI_STATION_H_
