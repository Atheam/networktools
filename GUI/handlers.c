//
// Created by adam5 on 05.06.2020.
//
#include "../REQUESTS/requests.h"
#include <string.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include "handlers.h"
#include "widgets.h"

G_MODULE_EXPORT void on_btn_tab1_clicked(GtkButton* b){
    gtk_notebook_set_current_page(notebook,0);
}
G_MODULE_EXPORT void on_btn_tab2_clicked(GtkButton* b){
    gtk_notebook_set_current_page(notebook,1);
}
G_MODULE_EXPORT void on_btn_tab3_clicked(GtkButton* b){
    gtk_notebook_set_current_page(notebook,2);
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

        GtkTextIter *end_iter;
        gtk_text_buffer_get_end_iter(buffer,end_iter);

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


            gtk_text_buffer_insert(buffer, end_iter, text, strlen(text));

        }

        gtk_widget_show(scan_res_win);

    }


}


