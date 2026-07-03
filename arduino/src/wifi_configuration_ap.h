/* Copied public header for Arduino scaffold. Implementation must be provided in arduino/src/ */
#ifndef _WIFI_CONFIGURATION_AP_H_
#define _WIFI_CONFIGURATION_AP_H_

#include <string>
#include <vector>
#include <mutex>
#include <memory>
#include <functional>

class DnsServer;

class WifiConfigurationAp
{
public:
    WifiConfigurationAp();
    ~WifiConfigurationAp();

    WifiConfigurationAp(const WifiConfigurationAp &) = delete;
    WifiConfigurationAp &operator=(const WifiConfigurationAp &) = delete;

    void SetSsidPrefix(const std::string &&ssid_prefix);
    void SetSsidPrefix(const std::string &ssid_prefix);
    void SetLanguage(const std::string &&language);
    void SetLanguage(const std::string &language);
    void SetShowOtaConfig(bool show);
    void SetShowSleepConfig(bool show);
    void Start();
    void Stop();
    void StartSmartConfig();
    bool ConnectToWifi(const std::string &ssid, const std::string &password);
    void Save(const std::string &ssid, const std::string &password);
    std::vector<std::string> GetAccessPoints();
    std::string GetSsid();
    std::string GetWebServerUrl();

    void OnExitRequested(std::function<void()> callback);

private:
    std::mutex mutex_;
    std::unique_ptr<DnsServer> dns_server_;
    std::string ssid_prefix_;
    std::string language_;
    bool is_connecting_ = false;
    bool show_ota_config_ = false;
    bool show_sleep_config_ = false;
    std::vector<std::string> ap_records_;
    std::function<void()> on_exit_requested_;
};

#endif // _WIFI_CONFIGURATION_AP_H_
