/* main.c */
#include <math.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gtkiconlist.h>
#include "icons.h"
#include "btlib.h"

struct btdev_name *dev_names;

/* this is a callback function.. more on this down below. */
void hello (void){
	g_print ("Hello World\n");
}


void destroy (void){
	gtk_main_quit ();
}

int main (int argc, char *argv[])
{	
	/* GtkWidget is the storage type for all types of widgets */
	GtkWidget *window;
	GtkWidget *scrollw;
	GtkWidget *iconlist;
	gchar label[56];
	gint i;
	struct btdev_name * devnames;
	
	/* this is called in all gtk applications.  Arguements are parsed from
	* the command line and are returned to the application. */
	gtk_init (&argc, &argv);
	
	/* Create a new window */
	window = gtk_window_new ( GTK_WINDOW_TOPLEVEL );
	gtk_window_set_title( GTK_WINDOW(window), "BT Manager 0.1" );
	gtk_widget_set_usize( window, 400, 200 );
	gtk_widget_set_uposition( window, 300, 200 );
	gtk_container_border_width (GTK_CONTAINER (window), 10);
	
	/*
	// Insert a vbox
	vbox = gtk_vbox_new( FALSE, 0 );
	gtk_container_add( GTK_CONTAINER(window), vbox );
	gtk_widget_show( vbox );
	*/
	
	// scrolled window
	scrollw = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollw), GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	gtk_container_add( GTK_CONTAINER(window), scrollw );
	gtk_widget_show(scrollw);
	
	/// add iconlist
	iconlist = gtk_icon_list_new(50, 2);
	gtk_icon_list_set_selection_mode( GTK_ICON_LIST(iconlist), 0 );
	gtk_scrolled_window_add_with_viewport( GTK_SCROLLED_WINDOW( scrollw ), iconlist );
	
	// can and add icons
	int num_rsp = btdev_scan(100);
	for(i = 0; i < num_rsp; i++){
		sprintf(label, "%s", dev_names[i].name);
		gtk_icon_list_add_from_data(GTK_ICON_LIST(iconlist), sheet_icon2, label, NULL);	
	}
	
	gtk_widget_show(iconlist);
	
	gtk_signal_connect (GTK_OBJECT (window), "destroy", GTK_SIGNAL_FUNC (destroy), NULL);
	
	/* show window */
	gtk_widget_show (window);
	
	/* all gtk applications must have a gtk_main().  Control ends here
	* and waits for an event to occur (like a keypress or mouse event). */
	gtk_main ();
	
	return 0;
}
