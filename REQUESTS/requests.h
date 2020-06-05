//
// Created by adam5 on 03.06.2020.
//

#ifndef TOOLS_REQUESTS_H
#define TOOLS_REQUESTS_H

struct hostinfo{
    char* host_name;
    char* ip_addr;
};


struct hostinfo* dnslookup(const char*);
struct hostinfo* reversednslookup(const char *);
int portscan(const char *,int,int,int*);




#endif //TOOLS_REQUESTS_H
