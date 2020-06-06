//
// Created by adam5 on 05.06.2020.
//

#include "widgets.h"
GtkNotebook * notebook;

GtkLabel * lookup_ip_res;
GtkLabel * lookup_dns_res;
GtkWidget * lookup_resGrid;
GtkWidget * lookup_err;
GtkEntry * lookup_entry;

GtkLabel * rlookup_ip_res;
GtkLabel * rlookup_dns_res;
GtkWidget * rlookup_resGrid;
GtkWidget * rlookup_err;
GtkEntry * rlookup_entry;

GtkEntry *scan_entry;
GtkEntry *scan_port1_entry;
GtkEntry *scan_port2_entry;
GtkTextView *scan_res_text;
GtkWidget *scan_res_win;
GtkWidget * scan_err;

GtkEntry * ping_entry;
GtkTextView *ping_res_text;
GtkWidget *ping_res_win;
GtkWidget *ping_err;
