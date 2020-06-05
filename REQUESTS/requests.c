#include <stdio.h>
#include <winsock2.h>
#include "requests.h"



//port info is returned as a function argument array, 0 value in array means port closed 1 means port open
//if no error occurs, portscan returns 0, otherwise portscan returns 1
int portscan(const char *ipaddr, int from, int to,int *tab){

    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSAStartup(wVersionRequested,&wsaData);
    if(to < from){
        return 1;
    }
    if(to < 0 || from > 65535){
        return 1;
    }

    struct sockaddr_in client;
    client.sin_family = AF_INET;
    SOCKET sock;
    struct hostent *host;


    if(isdigit(ipaddr[0])){

        client.sin_addr.s_addr = inet_addr(ipaddr);
    }
    else if((host = gethostbyname(ipaddr)) != NULL){
        struct in_addr addr;
        addr = *(struct in_addr *) host->h_addr_list[0];
        client.sin_addr.s_addr = inet_addr(inet_ntoa(addr));

    }
    else{
        return 1;
    }

    struct timeval time_out;
    time_out.tv_sec = 0;
    time_out.tv_usec = 300000;
    unsigned long iMode = 1;


    for(int i = from; i<=to;i++) {
        sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

        ioctlsocket(sock,FIONBIO,&iMode);


        client.sin_port = htons(i);
        connect(sock, (SOCKADDR *) &client, sizeof(client));


        fd_set setW, setE;

        FD_ZERO(&setW);
        FD_SET(sock, &setW);
        FD_ZERO(&setE);
        FD_SET(sock, &setE);

        select(0, NULL, &setW, &setE, &time_out);
        if (FD_ISSET(sock, &setW)) {
            tab[i-from] = 1;

        }
        else if (FD_ISSET(sock, &setE))
        {
            tab[i-from] = 0;

        }
        else {
            tab[i-from] = 0;

        }
        closesocket(sock);
    }
    return 0;

}

//if no error occurs reversednslookup returns hostinfo struct otherwise it returns NULL pointer
struct hostinfo* reversednslookup(const char *ipaddr){
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSAStartup(wVersionRequested,&wsaData);
    struct in_addr addr;
    addr.s_addr = inet_addr(ipaddr);
    struct hostent *host = gethostbyaddr( (char *) &addr,4, AF_INET);
    if(host == NULL){
        return NULL;
    }
    struct hostinfo* hinfo = malloc(sizeof(struct hostinfo));

    addr = *(struct in_addr *) host->h_addr_list[0];
    hinfo->host_name = host->h_name;
    hinfo->ip_addr = inet_ntoa(addr);

    return hinfo;
}

//if no error occurs dnslookup returns hostinfo struct otherwise it returns NULL pointer
struct hostinfo* dnslookup(const char * name){
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSAStartup(wVersionRequested,&wsaData);
    struct hostent *host = gethostbyname(name);
    if(host == NULL){
        return NULL;
    }
    struct in_addr addr;
    struct hostinfo *hinfo = malloc(sizeof(struct hostinfo));
    addr =  *(struct in_addr *) host->h_addr_list[0];

    hinfo->host_name = host->h_name;
    hinfo->ip_addr = inet_ntoa(addr);
    return hinfo;
}