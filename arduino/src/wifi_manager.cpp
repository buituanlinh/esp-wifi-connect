#include "wifi_manager.h"
#include "ssid_manager.h"
#include "wifi_station.h"
#include "wifi_configuration_ap.h"
#include <WiFi.h>

WifiManager &WifiManager::GetInstance()
{
    static WifiManager instance;
    return instance;
}

WifiManager::WifiManager() {}
WifiManager::~WifiManager()
{
    StopStation();
    StopConfigAp();
}

bool WifiManager::Initialize(const WifiManagerConfig &config)
{
    std::lock_guard<std::mutex> lock(mutex_);
    config_ = config;
    station_.reset(new WifiStation());
    config_ap_.reset(new WifiConfigurationAp());
    initialized_ = true;
    return true;
}

bool WifiManager::IsInitialized() const { return initialized_; }

void WifiManager::StartStation()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!initialized_)
        return;
    if (!station_)
        station_.reset(new WifiStation());
    station_->Start();
    station_active_ = true;
}

void WifiManager::StopStation()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (station_)
        station_->Stop();
    station_active_ = false;
}

bool WifiManager::IsConnected() const { return station_ && station_->IsConnected(); }

std::string WifiManager::GetSsid() const { return station_ ? station_->GetSsid() : std::string(); }
std::string WifiManager::GetIpAddress() const { return station_ ? station_->GetIpAddress() : std::string(); }
int WifiManager::GetRssi() const { return station_ ? station_->GetRssi() : 0; }
int WifiManager::GetChannel() const { return station_ ? station_->GetChannel() : 0; }
std::string WifiManager::GetMacAddress() const { return WiFi.macAddress().c_str(); }

void WifiManager::StartConfigAp()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!initialized_)
        return;
    if (!config_ap_)
        config_ap_.reset(new WifiConfigurationAp());
    config_ap_->SetSsidPrefix(config_.ssid_prefix);
    config_ap_->SetLanguage(config_.language);
    config_ap_->Start();
    config_mode_active_ = true;
}

void WifiManager::StopConfigAp()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (config_ap_)
        config_ap_->Stop();
    config_mode_active_ = false;
}

bool WifiManager::IsConfigMode() const { return config_ap_ && config_mode_active_; }
std::string WifiManager::GetApSsid() const { return config_ap_ ? config_ap_->GetSsid() : std::string(); }
std::string WifiManager::GetApWebUrl() const { return config_ap_ ? config_ap_->GetWebServerUrl() : std::string(); }

void WifiManager::SetPowerSaveLevel(WifiPowerSaveLevel level)
{
    if (station_)
        station_->SetPowerSaveLevel(level);
}

void WifiManager::SetEventCallback(std::function<void(WifiEvent, const std::string &)> callback)
{
    std::lock_guard<std::mutex> lock(mutex_);
    event_callback_ = callback;
}
