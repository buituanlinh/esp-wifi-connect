#ifndef _SSID_MANAGER_H_
#define _SSID_MANAGER_H_

#include <string>
#include <vector>

struct SsidItem
{
    std::string ssid;
    std::string password;
};

class SsidManager
{
public:
    static SsidManager &GetInstance();

    void AddSsid(const std::string &ssid, const std::string &password);
    void RemoveSsid(int index);
    void SetDefaultSsid(int index);
    void Clear();
    const std::vector<SsidItem> &GetSsidList() const;

private:
    SsidManager();
    ~SsidManager();

    void LoadFromNvs();
    void SaveToNvs();

    std::vector<SsidItem> ssid_list_;
};

#endif // _SSID_MANAGER_H_
