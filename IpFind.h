//
// Created by he on 23-6-29.
//

#ifndef IP_LOOKUP_IPFIND_H
#define IP_LOOKUP_IPFIND_H

#include "IpInfo.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <vector>
#include <unordered_map>

using namespace std;

class IpFind {
private:
    vector<IpInfo> ip_infos;

    // 存储geometryId和ip_infos元素中geometryId对应的元素下标
    unordered_map<int,vector<int>> geometryIdMap;

    // 将csv中的每一行数据存储
    void add_ip_info(vector<string> &row);

    // 将string ip 转换为unsigned int
    unsigned int parse_ip_to_int(const string &network_ip);

    vector<string> split(const string& str,const char delimiter);
public:
    void read_files(const string block_file,const string location_path);

    void search(const string& ip_addr);
};


#endif //IP_LOOKUP_IPFIND_H
