#include "linuxnetinfo.h"

LinuxNetInfo::LinuxNetInfo()
{
    file = fopen("/proc/net/dev", "r");
    if (file == NULL) {
        exit(1);
    }
}

LinuxNetInfo::~LinuxNetInfo()
{
    if (file != NULL)
        fclose(file);
}

const list<string> &LinuxNetInfo::GetAllNetWorkInterface()
{
    m_list.clear();
    struct if_nameindex *if_ni, *i;
    if_ni = if_nameindex();
    if (if_ni == NULL) {
        perror("if_nameindex");
        return m_list;
    }
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket error");
        return m_list;
    }
    struct ifreq ifr;
    for (i = if_ni; !(i->if_index == 0 && i->if_name == NULL); i++) {
        strcpy(ifr.ifr_name, i->if_name);
        if (ioctl(fd, SIOCGIFFLAGS, &ifr) < 0) {
            perror("ioctl error");
            close(fd);
            if_freenameindex(if_ni);
            return m_list;
        }
        if ((ifr.ifr_flags & IFF_LOOPBACK) == 0) {
            m_list.insert(m_list.end(), string(i->if_name));
        }
    }
    close(fd);
    if_freenameindex(if_ni);
    return m_list;
}

Flow LinuxNetInfo::GetFlow(const string &interface)
{
    m_flow = Flow();
    if (file == NULL) {
        return m_flow;
    }
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, interface.data()) != NULL) {
            sscanf(line + strcspn(line, ":"),
                   ":%llu %*u %*u %*u %*u %*u %*u %*u %*u %llu",
                   &m_flow.dn, &m_flow.up);
            break;
        }
    }
    return m_flow;
}

Flow LinuxNetInfo::FlowGetAllNetWorkFlow()
{

}

void LinuxNetInfo::GetNetWorkInterfaceInfo()
{

}

int LinuxNetInfo::get_addr(const char *interface, unsigned char *addr, int flag)
{
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
    } else {
        sin = (struct sockaddr_in *)&ifr.ifr_addr;
        snprintf((char *)addr, IP_LENGTH, "%s", inet_ntoa(sin->sin_addr));
    }
    return true;
}

int LinuxNetInfo::get_ip(const char *interface, unsigned char *ip)
{
    return get_addr(interface,ip,SIOCGIFADDR);
}

int LinuxNetInfo::get_ip_netmask(const char *interface, unsigned char *ip)
{
    return get_addr(interface, ip, SIOCGIFNETMASK);
}

int LinuxNetInfo::get_ip_broadcast(const char *interface, unsigned char *ip)
{
    return get_addr(interface, ip, SIOCGIFBRDADDR);
}

int LinuxNetInfo::get_mac(const char *interface, unsigned char *addr)
{
    return get_addr(interface, addr, SIOCGIFHWADDR);
}

