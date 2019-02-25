#ifndef HNS_H
#define HNS_H
#include "nameserverinterface.h"
#include <vector>

using namespace std;

class HNS : public NameServerInterface 
{
public:
    HNS(size_t size);
    void insert(const HostName& host, const IPAddress& ip);
    bool remove(const HostName& host);
    IPAddress lookup(const HostName& host) const;

private:
    size_t size;
    vector<vector<pair<string,IPAddress>>> hmap;
};

#endif