#include "hns.h"
#include <string>
#include <algorithm>

HNS::HNS(size_t size) : size(size), hmap(size) {}

void HNS::insert(const HostName& host, const IPAddress& ip){
    size_t hi = hash<string>{}(host) % size;
    hmap[hi].push_back(make_pair(host, ip));
}

bool HNS::remove(const HostName& host){
    size_t hi = hash<string>{}(host) % size;
    auto it = find_if(hmap[hi].begin(), hmap[hi].end(), [host](const pair<string, IPAddress> p){ return host == p.first;});
    if(it == hmap[hi].end()){
        return false;
    }else{
        hmap[hi].erase(it);
        return true;
    }
}

IPAddress HNS::lookup(const HostName& host) const{
    size_t hi = hash<string>{}(host) % size;
    auto it = find_if(hmap[hi].begin(), hmap[hi].end(), [host](const pair<string, IPAddress> p){ return host == p.first;});
    if(it == hmap[hi].end()){
        return NON_EXISTING_ADDRESS;
    }else{
        return it->second;
    }
}