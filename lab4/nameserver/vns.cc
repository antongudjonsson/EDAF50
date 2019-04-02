#include "vns.h"
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>
#include <iterator>

using namespace std;
using std::cout;
using std::endl;


void VNS::insert(const HostName& host, const IPAddress& ip){
    dns.push_back(make_pair(host, ip));
}

bool VNS::remove(const HostName& host){
    auto it = find_if(dns.begin(), dns.end(), [host](const pair<string, IPAddress>& p){return p.first == host;});
    if(it == dns.end()){
        return false;
    }else{
        //int index = distance(dns.begin(), it);
        dns.erase(it);
        return true;
    }
}

IPAddress VNS::lookup(const HostName& host) const{
    auto it = find_if(dns.begin(), dns.end(), [host](const pair<string, IPAddress>& p){return p.first == host;});
    if(it == dns.end()){
        return NON_EXISTING_ADDRESS;
    }else{
        int index = distance(dns.begin(), it);
        return dns[index].second;
    }
}