//
// Created by he on 23-6-29.
//

#ifndef IP_LOOKUP_IPINFO_H
#define IP_LOOKUP_IPINFO_H
#include <string>
using namespace std;
class IpInfo {
public:
    string network;
    int geography_id;
    double latitude;
    double longitude;
    double accuracy_radius;
    string country_name;
    string capitals_name;
    string city_name;

    // 网络ip转换为整数后的起始值(双闭区间)
    unsigned int network_start;
    unsigned int network_end;;

};


#endif //IP_LOOKUP_IPINFO_H
