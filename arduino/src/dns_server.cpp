#include "dns_server.h"

DnsServer::DnsServer() {}
DnsServer::~DnsServer() { Stop(); }

void DnsServer::Start(esp_ip4_addr_t gateway) {
    gateway_ = gateway;
}

void DnsServer::Stop() {}

void DnsServer::Run() {}
