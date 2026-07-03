#include "ssid_manager.h"
#include <Preferences.h>

SsidManager& SsidManager::GetInstance() {
    static SsidManager instance;
    return instance;
}

SsidManager::SsidManager() {
    LoadFromNvs();
}

SsidManager::~SsidManager() {
    SaveToNvs();
}

void SsidManager::AddSsid(const std::string& ssid, const std::string& password) {
    SsidItem item{ssid, password};
    ssid_list_.push_back(item);
    SaveToNvs();
}

void SsidManager::RemoveSsid(int index) {
    if (index >= 0 && index < (int)ssid_list_.size()) {
        ssid_list_.erase(ssid_list_.begin() + index);
        SaveToNvs();
    }
}

void SsidManager::SetDefaultSsid(int index) {
    if (index > 0 && index < (int)ssid_list_.size()) {
        auto it = ssid_list_.begin() + index;
        auto item = *it;
        ssid_list_.erase(it);
        ssid_list_.insert(ssid_list_.begin(), item);
        SaveToNvs();
    }
}

void SsidManager::Clear() {
    ssid_list_.clear();
    SaveToNvs();
}

const std::vector<SsidItem>& SsidManager::GetSsidList() const {
    return ssid_list_;
}

void SsidManager::LoadFromNvs() {
    Preferences prefs;
    if (!prefs.begin("wifi", true)) return;
    int count = prefs.getInt("count", 0);
    ssid_list_.clear();
    for (int i = 0; i < count; ++i) {
        String keyS = String("s") + i;
        String keyP = String("p") + i;
        String s = prefs.getString(keyS.c_str(), "");
        String p = prefs.getString(keyP.c_str(), "");
        if (s.length()) ssid_list_.push_back(SsidItem{std::string(s.c_str()), std::string(p.c_str())});
    }
    prefs.end();
}

void SsidManager::SaveToNvs() {
    Preferences prefs;
    if (!prefs.begin("wifi", false)) return;
    prefs.putInt("count", (int)ssid_list_.size());
    for (int i = 0; i < (int)ssid_list_.size(); ++i) {
        String keyS = String("s") + i;
        String keyP = String("p") + i;
        prefs.putString(keyS.c_str(), ssid_list_[i].ssid.c_str());
        prefs.putString(keyP.c_str(), ssid_list_[i].password.c_str());
    }
    prefs.end();
}
