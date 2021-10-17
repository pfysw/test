/*
 * image.c
 *
 *  Created on: Aug 2, 2021
 *      Author: Administrator
 */

#include <gtk/gtk.h>
#include <gdk/gdk.h>

int ShowJpeg(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *box;
    GdkPixbuf *pixbuf = NULL;
    GtkWidget *image;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "image");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", gtk_main_quit, NULL);
    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add (GTK_CONTAINER (window), box);
    pixbuf = gdk_pixbuf_new_from_file("1376833500.jpg", NULL);
    image = gtk_image_new_from_pixbuf(pixbuf);
    gtk_container_add (GTK_CONTAINER (box), image);
    gtk_widget_show_all (window);

    return 0;
}
