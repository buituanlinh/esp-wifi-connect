#include "wifi_configuration_ap.h"
#include "dns_server.h"
#include "ssid_manager.h"
#include <WiFi.h>
#include <WebServer.h>
#include "assets.h"

static WebServer *server = nullptr;

WifiConfigurationAp::WifiConfigurationAp() {}
WifiConfigurationAp::~WifiConfigurationAp() { Stop(); }

void WifiConfigurationAp::SetSsidPrefix(const std::string &&ssid_prefix) { ssid_prefix_ = ssid_prefix; }
void WifiConfigurationAp::SetSsidPrefix(const std::string &ssid_prefix) { ssid_prefix_ = ssid_prefix; }
void WifiConfigurationAp::SetLanguage(const std::string &&language) { language_ = language; }
void WifiConfigurationAp::SetLanguage(const std::string &language) { language_ = language; }
void WifiConfigurationAp::SetShowOtaConfig(bool show) { show_ota_config_ = show; }
void WifiConfigurationAp::SetShowSleepConfig(bool show) { show_sleep_config_ = show; }

void WifiConfigurationAp::Start()
{
    std::string ssid = ssid_prefix_ + "-Config";
    WiFi.softAP(ssid.c_str());
    if (!server)
        server = new WebServer(80);
    server->on("/", []()
               { server->send_P(200, "text/html", wifi_configuration_html); });
    server->on("/save", [this]()
               {
        String ssid = server->arg("ssid");
        String pw = server->arg("pw");
        if (ssid.length()) {
            SsidManager::GetInstance().AddSsid(std::string(ssid.c_str()), std::string(pw.c_str()));
            server->send_P(200, "text/html", wifi_configuration_done_html);
            if (on_exit_requested_) on_exit_requested_();
        } else {
            server->send(400, "text/plain", "missing ssid");
        } });
    server->begin();
}

void WifiConfigurationAp::Stop()
{
    if (server)
    {
        server->stop();
        delete server;
        server = nullptr;
    }
    WiFi.softAPdisconnect(true);
}

void WifiConfigurationAp::StartSmartConfig() {}

bool WifiConfigurationAp::ConnectToWifi(const std::string &ssid, const std::string &password)
{
    WiFi.begin(ssid.c_str(), password.c_str());
    return true;
}

void WifiConfigurationAp::Save(const std::string &ssid, const std::string &password)
{
    SsidManager::GetInstance().AddSsid(ssid, password);
}

std::vector<std::string> WifiConfigurationAp::GetAccessPoints() { return ap_records_; }

std::string WifiConfigurationAp::GetSsid() { return ssid_prefix_ + "-Config"; }

std::string WifiConfigurationAp::GetWebServerUrl() { return std::string("http://") + WiFi.softAPIP().toString().c_str(); }

void WifiConfigurationAp::OnExitRequested(std::function<void()> callback) { on_exit_requested_ = callback; }
