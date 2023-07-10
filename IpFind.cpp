//
// Created by he on 23-6-29.
//

#include "IpFind.h"


void IpFind::read_files(const string block_file,const string location_path) {
    ifstream file(block_file,ios::in);
    string line,value;
    if(file.is_open()){
        int i=0;
        while(getline(file,line)){
            if(i==0){
                i++;
                continue;
            }
            vector<string> row= split(line,',');
            add_ip_info(row);
            i++;
        }
    }
    else{
        cout<<"can not open block_file"<<endl;
    }

    ifstream files(location_path,ios::in);
    if(files.is_open()){
        int i=0;
        while(getline(files,line)){
            if(i==0){
                i++;
                continue;
            }
            vector<string> row= split(line,',');
            try{
                int geography_id=stoi(row[0]);
                if(geometryIdMap.find(geography_id)!=geometryIdMap.end()){
                    auto indexs=geometryIdMap[geography_id];
                    for(int j=0;j<indexs.size() ;++j){
                        ip_infos[indexs[j]].country_name=row[5];
                        ip_infos[indexs[j]].capitals_name =row[7];
                        ip_infos[indexs[j]].city_name =row[10];
                    }

                }
            }catch(exception& e) {
                cout<<e.what()<<" "<<row[0]<<endl;

            }
            i++;
        }
    }
    else{
        cout<<"can not open Location_file"<<endl;
    }

}

void IpFind::add_ip_info(vector<string> &row){
    IpInfo info;
    info.network=row[0];
    info.geography_id=stoi(row[1]);
    try{
        info.latitude=stod(row[7]);
    }catch(exception& e) {
        cout<<e.what()<<row[7]<<endl;
    }

    try{
        info.longitude=stod(row[8]);
    }catch(exception& e) {
        cout<<e.what()<<row[8]<<endl;
    }

    try{
        info.accuracy_radius=stod(row[9]);
    }catch(exception& e) {
        cout<<e.what()<<row[9]<<endl;
    }

    vector<string> networks= split(row[0],'/');
    int bit= stoi(networks[1]);
    bit=32-bit;
    int value=(1<<bit)-1;
    info.network_start= parse_ip_to_int(networks[0]);
    info.network_end=info.network_start|value;

    ip_infos.push_back(info);

    geometryIdMap[info.geography_id].push_back(ip_infos.size()-1);

}

void IpFind::search(const string &ip_addr) {
    unsigned int ip_number= parse_ip_to_int(ip_addr);
    bool isIn=false;
    for(int i=0;i<ip_infos.size();++i){
        if(ip_number>=ip_infos[i].network_start && ip_number<=ip_infos[i].network_end){
            cout<<"country_name: "<<ip_infos[i].country_name<<endl;
            cout<<"capitals_name: "<<ip_infos[i].capitals_name<<endl;
            cout<<"city_name: "<<ip_infos[i].city_name<<endl;
            cout<<"latitude: "<<ip_infos[i].latitude<<endl;
            cout<<"longitude: "<<ip_infos[i].longitude<<endl;

            isIn=true;
            break;
        }
    }
    if(!isIn){
        cout<<"ip_addr information is not find"<<endl;
    }
}

unsigned int IpFind::parse_ip_to_int(const string &network_ip) {
    vector<string> ip_input= split(network_ip,'.');
    unsigned int result=0;
    for(auto &str:ip_input){
        result=(result<<8)+ stoi(str);
    }
    return result;

}

vector<string> IpFind::split(const string &str,const char delimiter) {
    vector<string> result;
    int i=0;
    string ele;
    while(i<str.size()){
        if(str[i]==delimiter){
            result.push_back(ele);
            ele="";
        }
        else{
            ele+=str[i];
        }
        i++;
    }
    if(ele!=""){
        result.push_back(ele);
    }
    return result;
}
