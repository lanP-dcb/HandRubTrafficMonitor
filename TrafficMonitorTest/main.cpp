#include <QApplication>
#include "processclass.h"

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

#define MAX_INTERFACE_LEN 16
using namespace std;

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


Flow getNetworkStats(const char *interface) {
    FILE *file = fopen("/proc/net/dev", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    Flow m_flow;
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, interface) != NULL) {
            sscanf(line + strcspn(line, ":"),
                   ":%llu %*u %*u %*u %*u %*u %*u %*u %*u %llu",
                   &m_flow.dn, &m_flow.up);
            break;
        }
    }
    return m_flow;
    fclose(file);
}

list<string> GetAllNetWorkInterface()
{
    list<string> m_list;
    struct if_nameindex *if_ni, *i;
    if_ni = if_nameindex();
    if (if_ni == NULL) {
        perror("if_nameindex");
        exit(EXIT_FAILURE);
    }

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket error");
        return m_list;
    }
    char tmp[14];
    struct ifreq ifr;
    for (i = if_ni; !(i->if_index == 0 && i->if_name == NULL); i++) {
        strcpy(ifr.ifr_name, i->if_name);
        if (ioctl(fd, SIOCGIFFLAGS, &ifr) < 0) {
            perror("ioctl error");
            close(fd);
            return m_list;
        }
        // 检查是否是回环接口
        if ((ifr.ifr_flags & IFF_LOOPBACK) == 0) {
            m_list.insert(m_list.end(), string(i->if_name));
        }
    }
    close(fd);
    return m_list;
}

void GetNetWorkInterfaceInfo()
{

}

int get_addr(const char* interface,unsigned char *addr, int flag){
    int sockfd = 0;
    struct sockaddr_in *sin;
    struct ifreq ifr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error!\n");
        return false;
    }

    memset(&ifr, 0, sizeof(ifr));
    snprintf(ifr.ifr_name, (sizeof(ifr.ifr_name) - 1), "%s", interface);

    if (ioctl(sockfd, flag, &ifr) < 0 ) {
        perror("ioctl error!\n");
        close(sockfd);
        return false;
    }
    close(sockfd);

    if (SIOCGIFHWADDR == flag) {
        memcpy((void *)addr, (const void *)&ifr.ifr_ifru.ifru_hwaddr.sa_data, 6);
        snprintf((char*)addr,18,"%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x",
                 addr[0],addr[1],addr[2],addr[3],addr[4],addr[5]);
//        printf("%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x\n", addr[0],addr[1],addr[2],addr[3],addr[4],addr[5]);
    } else {
        sin = (struct sockaddr_in *)&ifr.ifr_addr;
        snprintf((char *)addr, 16, "%s", inet_ntoa(sin->sin_addr));
    }
    return true;
}

int get_ip(const char *interface, unsigned char *ip){
    return get_addr(interface,ip,SIOCGIFADDR);
}

int get_ip_netmask(const char *interface, unsigned char *ip){
    return get_addr(interface, ip, SIOCGIFNETMASK);
}

int get_ip_broadcast(const char *interface, unsigned char *ip){
    return get_addr(interface, ip, SIOCGIFBRDADDR);
}

int get_mac(const char *interface, unsigned char *addr){
    return get_addr(interface, addr, SIOCGIFHWADDR);
}

int get_ipv6(const char *interface,unsigned char *addr){
    return 0;
}


int main(int argc, char *argv[])
{
    list<string> list = GetAllNetWorkInterface();
    foreach (string s, list) {
        printf("%s\n",s.c_str());
        Flow flow_1 = getNetworkStats(s.data());
        sleep(1);
        Flow flow_2 = getNetworkStats(s.data());
        printf("up:%lld\n",(flow_2-flow_1).up);
        printf("dn:%lld\n",(flow_2-flow_1).dn);
        char info_temp[20];
        memset(info_temp,0,20);
        get_ip(s.c_str(),(unsigned char*)info_temp);
        printf("%s\n",info_temp);
        memset(info_temp,0,20);
        get_ip_netmask(s.c_str(),(unsigned char*)info_temp);
        printf("%s\n",info_temp);
        get_ip_broadcast(s.c_str(),(unsigned char*)info_temp);
        printf("%s\n",info_temp);

        get_mac(s.c_str(),(unsigned char*)info_temp);
        printf("%s\n",info_temp);
        int ret = get_ipv6(s.c_str(),(unsigned char*)info_temp);
        printf("%d\n",ret);
    }

//    QApplication a(argc, argv);
//    ProcessClass process;
//    return a.exec();
}
