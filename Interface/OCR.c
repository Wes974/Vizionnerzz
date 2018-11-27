#include <gtk/gtk.h>
#include <stdio.h>

typedef struct
{
    GtkBuilder *builder;
    gpointer user_data;
} SGlobalData;

int main(int argc, char *argv [])
{
    GtkWidget *fenetre_principale;
    SGlobalData data;
    GError *error = NULL;
    gchar *filename;
    /* Initialisation de la librairie Gtk. */
    gtk_init(&argc, &argv);

    /* Ouverture du fichier Glade de la fenêtre principale */
    data.builder = gtk_builder_new();

    /* Création du chemin complet pour accéder au fichier test.glade. */
    /* g_build_filename(); construit le chemin complet en fonction du système */
    /* d'exploitation. ( / pour Linux et \ pour Windows) */
    filename =  g_build_filename ("OCR.glade", NULL);

    /* Chargement du fichier test.glade. */
    gtk_builder_add_from_file (data.builder, filename, &error);
    g_free (filename);
    if (error)
    {
        gint code = error->code;
        g_printerr("%s\n", error->message);
        g_error_free (error);
        return code;
    }

    gtk_builder_connect_signals(data.builder, &data);

    /* Récupération du pointeur de la fenêtre principale */
    fenetre_principale = GTK_WIDGET(gtk_builder_get_object (data.builder, "mainWindow"));
    /*GtkWidget *quit = GTK_WIDGET(gtk_builder_get_object (data.builder, "Quit"));*/

    /* Affectation du signal "destroy" à la fonction gtk_main_quit(); pour la */
    /* fermeture de la fenêtre. */
    /*g_signal_connect (G_OBJECT (fenetre_principale), "destroy", (GCallback)gtk_main_quit, NULL);
    g_signal_connect (G_OBJECT (quit), "activate", (GCallback)gtk_main_quit, NULL);*/

    /* Affichage de la fenêtre principale. */
    gtk_widget_show_all (fenetre_principale);

    gtk_main();

    return 0;
}

void callback_close (GtkMenuItem *menuitem, gpointer user_data)
{
    SGlobalData *data = (SGlobalData*) user_data;
    GtkWidget *fileSelector = NULL;

    fileSelector = GTK_WIDGET (gtk_builder_get_object (data->builder, "FileSelector"));

    gtk_dialog_run (GTK_DIALOG (fileSelector));

    gtk_widget_hide(fileSelector);
}
