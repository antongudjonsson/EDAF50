#ifndef VSN_H
#define VSN_H
#include "nameserverinterface.h"
#include <map>

using namespace std;

class MNS : public NameServerInterface 
{
public:
    void insert(const HostName& host, const IPAddress& ip);
    bool remove(const HostName& host);
    IPAddress lookup(const HostName& host) const;

private:
    map<string, IPAddress> dns;
};

#endif