#ifndef LINUXNETINFO_H
#define LINUXNETINFO_H

#include "common/NetInfoBase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <net/if.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <net/route.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ctype.h>
#include <fcntl.h>
#if defined(__GLIBC__) && __GLIBC__ >=2 && __GLIBC_MINOR__ >= 1
#include <netpacket/packet.h>
#include <net/ethernet.h>
#else
#include <sys/types.h>
#include <netinet/if_ether.h>
#endif


class LinuxNetInfo : public NetInfoBase
{
public:
    LinuxNetInfo();
    ~LinuxNetInfo();

    const list<string>& GetAllNetWorkInterface() override;

    Flow GetFlow(const string& interface) override ;

    Flow FlowGetAllNetWorkFlow() override;

    void GetNetWorkInterfaceInfo() override;

private:

    int get_addr(const char* interface,unsigned char *addr, int flag);

    int get_ip(const char *interface, unsigned char *ip); // 16

    int get_ip_netmask(const char *interface, unsigned char *ip); // 16

    int get_ip_broadcast(const char *interface, unsigned char *ip);

    int get_mac(const char *interface, unsigned char *addr); // 6


    list<string> m_list;
    FILE* file;
    Flow m_flow;
};

#endif // LINUXNETINFO_H
