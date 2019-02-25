#include "mns.h"
#include <map>

using namespace std;

void MNS::insert(const HostName& host,const IPAddress& ip){
    dns.insert(make_pair(host, ip));
}

bool MNS::remove(const HostName& host){
    auto it = dns.find(host);
    if(it == dns.end()){
        return false;
    }else{
        dns.erase(it);
        return true;
    }
}

IPAddress MNS::lookup(const HostName& host) const{
    auto it = dns.find(host);
    if(it == dns.end()){
        return NON_EXISTING_ADDRESS;
    }else{
        return dns.at(it->first);
    }
}
