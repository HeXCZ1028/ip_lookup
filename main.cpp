//
// Created by he on 23-6-29.
//
#include "IpFind.h"
int main(int argc,char* argv[]){

    string block_file,location_file;
    if(argc==1){
        block_file=("../utility/GeoLite2-City-Blocks-China-IPv4.csv");
        location_file=("../utility/GeoLite2-City-Locations-China-en.csv");
    }
    else if(argc==3){
        block_file=argv[1];
        location_file=argv[2];
    }
    else{
        cout<<"Argument is error"<<endl;
        return 0;
    }
    IpFind ipFind;
    ipFind.read_files(block_file,location_file);

    string ip_addr;
    cout<<"please input ip addr "<<endl;
    while(1){
        cin>>ip_addr;
        ipFind.search(ip_addr);
    }
    return 0;
}
