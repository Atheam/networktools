//
// Created by adam5 on 05.06.2020.
//
#include "../REQUESTS/requests.h"
#include <string.h>
#include <stdlib.h>
#include "handlers.h"
#include "widgets.h"
#include <unistd.h>

G_MODULE_EXPORT void on_btn_tab1_clicked(GtkButton* b){
    gtk_notebook_set_current_page(notebook,0);
}
G_MODULE_EXPORT void on_btn_tab2_clicked(GtkButton* b){
    gtk_notebook_set_current_page(notebook,1);
}
G_MODULE_EXPORT void on_btn_tab3_clicked(GtkButton* b){
    gtk_notebook_set_current_page(notebook,2);
}
G_MODULE_EXPORT void on_btn_tab4_clicked(GtkButton* b){
    gtk_notebook_set_current_page(notebook,3);
}

G_MODULE_EXPORT void on_lookup_btn_clicked(GtkButton* b){
    const char * domain = gtk_entry_get_text(lookup_entry);
    struct hostinfo *host = dnslookup(domain);
    if(host == NULL){
        gtk_widget_hide(lookup_resGrid);
        gtk_widget_show(lookup_err);
    }
    else{
        gtk_widget_hide(lookup_err);
        gtk_widget_show(lookup_resGrid);
        gtk_label_set_text(lookup_ip_res,host->ip_addr);
        gtk_label_set_text(lookup_dns_res,host->host_name);
    }
    free(host);

}
G_MODULE_EXPORT void on_rlookup_btn1_clicked(GtkButton *b){
    const char * addr = gtk_entry_get_text(rlookup_entry);
    struct hostinfo* host = reversednslookup(addr);
    if(host == NULL){
        gtk_widget_hide(rlookup_resGrid);
        gtk_widget_show(rlookup_err);
    }
    else{
        gtk_widget_hide(rlookup_err);
        gtk_widget_show(rlookup_resGrid);
        gtk_label_set_text(rlookup_ip_res,host->ip_addr);
        gtk_label_set_text(rlookup_dns_res,host->host_name);
    }
    free(host);
}

G_MODULE_EXPORT void on_scan_btn_clicked(GtkButton *b){
    const char* name = gtk_entry_get_text(scan_entry);
    const char* port_start = gtk_entry_get_text(scan_port1_entry);
    const char* port_end = gtk_entry_get_text(scan_port2_entry);

    int start = atoi(port_start);
    int end = atoi(port_end);
    int size = end-start+1;
    int tab[size];

    gtk_widget_hide(scan_res_win);
    gtk_widget_hide(scan_err);


    int error = portscan(name,start,end,tab);

    if(error == 1){
        gtk_widget_show(scan_err);

    }
    else {

        GtkTextBuffer *buffer = gtk_text_buffer_new(NULL);
        gtk_text_view_set_buffer(scan_res_text,buffer);

        GtkTextIter end_iter;
        gtk_text_buffer_get_end_iter(buffer,&end_iter);

        for (int i = 0; i < size; i++) {
            int num = start + i;
            char text[30];
            char *status;


            if (tab[i] == 1) {
                status = "opened\n";
            } else {
                status = "closed\n";
            }

            sprintf(text, "Port number: %d status: %s", num, status);


            gtk_text_buffer_insert(buffer, &end_iter, text, strlen(text));

        }

        gtk_widget_show(scan_res_win);

    }

}

G_MODULE_EXPORT void on_ping_btn_clicked(GtkButton* b){
    const char * name = gtk_entry_get_text(ping_entry);

    GtkTextBuffer *buffer = gtk_text_buffer_new(NULL);
    gtk_text_view_set_buffer(ping_res_text,buffer);
    GtkTextIter end_iter;
    gtk_text_buffer_get_end_iter(buffer,&end_iter);




    int counter = 0;
    int numOfRequests = 4;


    for(int i = 0;i<numOfRequests;i++){

    struct icmpReplyInfo * reply = ping(name);
    if(reply == NULL){
        gtk_widget_show(ping_err);
        gtk_widget_hide(ping_res_win);
        return;
    }


    else{
        char text[128];

        if(reply->status == 0) {
            sprintf(text, "Reply from %s: bytes=%d time=%dms\n", reply->address, reply->dataSize, reply->time);
            gtk_text_buffer_insert(buffer, &end_iter, text, strlen(text));
            usleep(500000);
            counter++;
        }
        else{
            sprintf(text, "Reply from %s: Destination host unreachable or request timed out\n", reply->address);
            gtk_text_buffer_insert(buffer, &end_iter, text, strlen(text));
            usleep(500000);
        }
        }
    }

    char text[128];
    int packetLoss;
    if(numOfRequests != 0){
        packetLoss = 100 - ((100/numOfRequests) * counter);
    }
    else packetLoss = 0;
    sprintf(text,"\n\nPackets sent: %d\nPackets Received: %d\nPackets lost: %d (%d%% loss)",numOfRequests,counter,numOfRequests-counter,packetLoss);
    gtk_text_buffer_insert(buffer, &end_iter, text, strlen(text));

    gtk_widget_hide(ping_err);
    gtk_widget_show(ping_res_win);


}


