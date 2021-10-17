#include <gtk/gtk.h>

#include "exampleapp.h"
#include "image.h"

int
main11 (int argc, char *argv[])
{
//    GtkWidget *window;
//    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    setvbuf(stdout, NULL, _IONBF, 0);
  return g_application_run (G_APPLICATION (example_app_new ()), argc, argv);
}

int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);
    gtk_init(&argc,&argv);
    ShowJpeg(argc,argv);

    gtk_main();
    return 0;
    return 0;
}
