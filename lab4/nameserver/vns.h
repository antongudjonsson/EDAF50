#ifndef VNS_H
#define VNS_H
#include "nameserverinterface.h"
#include <vector>
#include <string>

using namespace std;

class VNS : public NameServerInterface 
{
public:
    void insert(const HostName& host, const IPAddress& ip);
    bool remove(const HostName& host);
    IPAddress lookup(const HostName& host) const;

private:
    vector<pair<string, IPAddress>> dns;
};

#endif