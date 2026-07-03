/* Copied public header for Arduino scaffold. Implementation must be provided in arduino/src/ */

#ifndef _WIFI_MANAGER_H_
#define _WIFI_MANAGER_H_

#include <string>
#include <memory>
#include <functional>
#include <mutex>

#include "wifi_station.h"

class WifiStation;
class WifiConfigurationAp;

enum class WifiEvent
{
    Scanning,
    Connecting,
    Connected,
    Disconnected,
    ConfigModeEnter,
    ConfigModeExit,
};

struct WifiManagerConfig
{
    std::string ssid_prefix = "ESP32";
    std::string language = "zh-CN";
    int station_scan_min_interval_seconds = 10;
    int station_scan_max_interval_seconds = 300;
    uint8_t station_failure_retry_cnt = 3;
    bool show_ota_config = false;
    bool show_sleep_config = false;
};

class WifiManager
{
public:
    static WifiManager &GetInstance();

    bool Initialize(const WifiManagerConfig &config = WifiManagerConfig{});
    bool IsInitialized() const;

    void StartStation();
    void StopStation();

    bool IsConnected() const;
    std::string GetSsid() const;
    std::string GetIpAddress() const;
    int GetRssi() const;
    int GetChannel() const;
    std::string GetMacAddress() const;

    void StartConfigAp();
    void StopConfigAp();

    bool IsConfigMode() const;
    std::string GetApSsid() const;
    std::string GetApWebUrl() const;

    void SetPowerSaveLevel(WifiPowerSaveLevel level);

    void SetEventCallback(std::function<void(WifiEvent, const std::string &)> callback);

    const WifiManagerConfig &GetConfig() const { return config_; }

    WifiManager(const WifiManager &) = delete;
    WifiManager &operator=(const WifiManager &) = delete;

private:
    WifiManager();
    ~WifiManager();

    WifiManagerConfig config_;
    std::unique_ptr<WifiStation> station_;
    std::unique_ptr<WifiConfigurationAp> config_ap_;
    mutable std::mutex mutex_;
    bool initialized_ = false;
    bool station_active_ = false;
    bool config_mode_active_ = false;
    std::function<void(WifiEvent, const std::string &)> event_callback_;
    mutable std::string mac_address_;
};

#endif // _WIFI_MANAGER_H_
