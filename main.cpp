//
// Created by he on 23-6-29.
//
#include "IpFind.h"

// mysql connection header file
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_driver.h>


vector<string> split(const string &str,const char delimiter) {
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

unsigned int parse_ip_to_int(const string &network_ip) {
    vector<string> ip_input= split(network_ip,'.');
    unsigned int result=0;
    for(auto &str:ip_input){
        result=(result<<8)+ stoi(str);
    }
    return result;
}
int main(int argc,char* argv[]){
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "admin_he", "admin_he_123456");
        con->setSchema("Ip_informations");
    } catch (sql::SQLException &e) {
        // Handle the exception
        cout<<e.getErrorCode()<<e.what()<<endl;
    }

    sql::Statement *stmt,*tmp;
    sql::ResultSet *res;

    stmt = con->createStatement();
    while(1) {
        string input;
        cin>>input;
        unsigned int number= parse_ip_to_int(input);
        string search = "SELECT * FROM `GeoLite2-City-Blocks-China-IPv4` LEFT JOIN `GeoLite2-City-Locations-China-en` "
                        "ON `GeoLite2-City-Locations-China-en`.`geoname_id`=`GeoLite2-City-Blocks-China-IPv4`.`geoname_id`"
                        "WHERE `GeoLite2-City-Blocks-China-IPv4`.`network_start`<="+ to_string(number)+" AND "+
                        "`GeoLite2-City-Blocks-China-IPv4`.`network_end`>="+to_string(number);
        res = stmt->executeQuery(search);
        while (res->next()) {
        // Process the result
            string country_name=res->getString("country_name");
            string subdivision_1_name=res->getString("subdivision_1_name");
            string city_name=res->getString("city_name");
            string latitude=res->getString("latitude");
            string longitude=res->getString("longitude");
            cout<<"country_name: "<<country_name<<endl;
            cout<<"capitals_name: "<<subdivision_1_name<<endl;
            cout<<"city_name: "<<city_name<<endl;
            cout<<"latitude: "<<latitude<<endl;
            cout<<"longitude: "<<longitude<<endl;
        }
        cout<<"finish "<<endl;
    }
//    res = stmt->executeQuery("SELECT * FROM `GeoLite2-City-Blocks-China-IPv4`");
//
//    vector<string> results;
//    while (res->next()) {
//        // Process the result
//        string network=res->getString("network");
//        results.push_back(network);
//    }
//    int i=0;
//    for(auto &network: results){
//        tmp=con->createStatement();
//        vector<string> networks= split(network,'/');
//        int bit= stoi(networks[1]);
//        bit=32-bit;
//        int value=(1<<bit)-1;
//        unsigned network_start= parse_ip_to_int(networks[0]);
//        unsigned network_end=network_start|value;
//
//        cout<<network_start<<" "<<network_end<<" "<<i<<endl;
//        i++;
//        string update_word="UPDATE  `GeoLite2-City-Blocks-China-IPv4`  SET  `network_start`="+ to_string(network_start)
//                           +","+"`network_end`="+to_string(network_end)+" WHERE `network`= "+"\""+network+"\"";
//        tmp->executeUpdate(update_word);
//    }

    delete res;
    delete stmt;
    delete tmp;

    con->close();
    delete con;


    return 0;
}
