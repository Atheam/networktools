#include <stdio.h>
#include "requests.h"
#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>




//if no errors occur ping returns pointer to icmpReplyInfo structure otherwise returns NULL
struct icmpReplyInfo* ping(const char *name){

    HANDLE hIcmpFile;
    unsigned long ipaddr;
    int return_value;
    char SendData[32] = "Data Buffer";

    if((ipaddr = inet_addr(name)) == INADDR_NONE){

        struct hostent * host;

        WSADATA wsaData;
        WORD wVersionRequested = MAKEWORD(2, 2);
        WSAStartup(wVersionRequested,&wsaData);

        if((host = gethostbyname(name)) != NULL){


            struct in_addr addr;
            addr = *(struct in_addr *) host->h_addr_list[0];
            ipaddr = inet_addr(inet_ntoa(addr));
        }
        else{
            return NULL;
        }
    }

    LPVOID ReplyBuffer;
    DWORD ReplySize;

    hIcmpFile = IcmpCreateFile();



    if (hIcmpFile == INVALID_HANDLE_VALUE) {
        return NULL;
    }

    ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData);
    ReplyBuffer = malloc(ReplySize);
    return_value = IcmpSendEcho(hIcmpFile, ipaddr, SendData, sizeof(SendData),
                                NULL, ReplyBuffer, ReplySize, 1000);

    if(return_value != 0){

        struct icmpReplyInfo * replyInfo = malloc(sizeof(struct icmpReplyInfo));
        PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;
        struct in_addr ReplyAddr;

        ReplyAddr.S_un.S_addr = pEchoReply -> Address;
        replyInfo->address = inet_ntoa(ReplyAddr);
        replyInfo->status = pEchoReply ->Status;
        replyInfo->dataSize = pEchoReply ->DataSize;
        replyInfo->time = pEchoReply ->RoundTripTime;

        return replyInfo;
    }
    else{
        return NULL;
    }

}


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


    if(inet_addr(ipaddr) != INADDR_NONE){

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
    time_out.tv_usec = 200000;
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