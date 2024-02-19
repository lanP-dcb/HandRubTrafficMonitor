#ifndef NETINFOBASE_H
#define NETINFOBASE_H

#include <iostream>
#include <list>

using namespace std;

#define IP_LENGTH 16

struct Flow{
    unsigned long long dn;
    unsigned long long up;
    Flow():dn(0),up(0){};
    Flow(const Flow& other):dn(other.dn),up(other.up){};
    const Flow operator=(const Flow& p){
        dn = p.dn;  up = p.up;
        return *this;
    }
    const Flow operator+(const Flow& p){
        Flow temp;
        temp.dn = dn + p.dn;
        temp.up = up + p.up;
        return temp;
    }
    const Flow operator-(const Flow& p){
        Flow temp;
        temp.dn = dn - p.dn;
        temp.up = up - p.up;
        return temp;
    }
};

class NetInfoBase{

public:
    NetInfoBase(){};

    /**
     * @brief GetAllNetWorkInterface 获取所有网络接口，不包括本地环回
     * @return 网络接口名称列表
     */
    virtual const list<string>& GetAllNetWorkInterface() = 0;

    /**
     * @brief GetSpeed  获取指定网络接口当前的上下行流量统计
     * @param interface 网络接口名称
     * @return
     */
    virtual Flow GetFlow(const string& interface) = 0;

    /**
     * @brief GetSpeed  所有网络接口当前的上下行流量统计，不包括本地环回
     * @return
     */
    virtual Flow FlowGetAllNetWorkFlow() = 0;


    /**
     * @brief GetNetWorkInterfaceInfo
     */
    virtual void GetNetWorkInterfaceInfo() = 0;

};

#endif // NETINFOBASE_H
