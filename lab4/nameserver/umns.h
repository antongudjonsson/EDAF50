#ifndef UMNS_H
#define UMNS_H
#include "nameserverinterface.h"
#include <unordered_map>

using namespace std;

class UMNS : public NameServerInterface 
{
public:
    void insert(const HostName& host, const IPAddress& ip);
    bool remove(const HostName& host);
    IPAddress lookup(const HostName& host) const;

private:
    unordered_map<string, IPAddress> dns;
};

#endif