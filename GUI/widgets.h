//
// Created by adam5 on 05.06.2020.
//
#ifndef TOOLS_WIDGETS_H
#define TOOLS_WIDGETS_H
#include <gtk/gtk.h>

extern GtkNotebook * notebook;

extern GtkLabel * lookup_ip_res;
extern GtkLabel * lookup_dns_res;
extern GtkWidget * lookup_resGrid;
extern GtkWidget * lookup_err;
extern GtkEntry * lookup_entry;

extern GtkLabel * rlookup_ip_res;
extern GtkLabel * rlookup_dns_res;
extern GtkWidget * rlookup_resGrid;
extern GtkWidget * rlookup_err;
extern GtkEntry * rlookup_entry;

extern GtkEntry *scan_entry;
extern GtkEntry *scan_port1_entry;
extern GtkEntry *scan_port2_entry;
extern GtkTextView *scan_res_text;
extern GtkWidget *scan_res_win;
extern GtkWidget * scan_err;


#endif //TOOLS_WIDGETS_H
