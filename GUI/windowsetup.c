#include "widgets.h"


const char * GLADE_PATH = "glade\\glade_gui.glade";
const char * CSS_PATH = "glade\\style.css";

int windowsetup(int argc, char **argv) {

    GtkWidget *window;
    GtkBuilder *builder;

    gtk_init(&argc,&argv);
    builder = gtk_builder_new_from_file(GLADE_PATH);
    window = GTK_WIDGET(gtk_builder_get_object(builder,"main_window"));
    lookup_resGrid = GTK_WIDGET(gtk_builder_get_object(builder,"lookup_resGrid"));
    rlookup_resGrid = GTK_WIDGET(gtk_builder_get_object(builder,"rlookup_resGrid"));
    gtk_widget_set_name(lookup_resGrid,"lookup_resGrid");
    gtk_widget_set_name(rlookup_resGrid,"rlookup_resGrid");

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider,CSS_PATH,NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);


    gtk_builder_connect_signals(builder,NULL);


    notebook = (GtkNotebook*) GTK_WIDGET(gtk_builder_get_object(builder,"notebook"));
    lookup_ip_res = (GtkLabel*) GTK_WIDGET(gtk_builder_get_object(builder,"lookup_ip_res"));
    lookup_dns_res = (GtkLabel*) GTK_WIDGET(gtk_builder_get_object(builder,"lookup_dns_res"));
    lookup_entry = (GtkEntry*) GTK_WIDGET(gtk_builder_get_object(builder,"lookup_entry"));
    lookup_err = GTK_WIDGET(gtk_builder_get_object(builder,"lookup_err"));

    rlookup_ip_res = (GtkLabel*) GTK_WIDGET(gtk_builder_get_object(builder,"rlookup_ip_res"));
    rlookup_dns_res = (GtkLabel*) GTK_WIDGET(gtk_builder_get_object(builder,"rlookup_dns_res"));
    rlookup_entry = (GtkEntry*) GTK_WIDGET(gtk_builder_get_object(builder,"rlookup_entry"));
    rlookup_err = GTK_WIDGET(gtk_builder_get_object(builder,"rlookup_err"));

    scan_entry =  (GtkEntry *) GTK_WIDGET(gtk_builder_get_object(builder,"scan_entry"));
    scan_port1_entry  = (GtkEntry *)  GTK_WIDGET(gtk_builder_get_object(builder,"scan_port1_entry"));
    scan_port2_entry =  (GtkEntry *)  GTK_WIDGET(gtk_builder_get_object(builder,"scan_port2_entry"));
    scan_res_text = (GtkTextView *)GTK_WIDGET(gtk_builder_get_object(builder,"scan_res_text"));
    scan_res_win = GTK_WIDGET(gtk_builder_get_object(builder,"scan_res_win"));
    scan_err = GTK_WIDGET(gtk_builder_get_object(builder,"scan_err"));

    ping_entry = (GtkEntry *) GTK_WIDGET(gtk_builder_get_object(builder,"ping_entry"));
    ping_res_text = (GtkTextView *)GTK_WIDGET(gtk_builder_get_object(builder,"ping_res_text"));
    ping_res_win = GTK_WIDGET(gtk_builder_get_object(builder,"ping_res_win"));
    ping_err = GTK_WIDGET(gtk_builder_get_object(builder,"ping_err"));


    gtk_widget_show(window);



}


