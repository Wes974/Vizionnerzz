#include <gtk/gtk.h>
#include <stdio.h>
#include "OCR.h"
#include "Basics.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/* Struct used to keep global variables */
typedef struct
{
    GtkBuilder *builder;
    gpointer user_data;
    GtkWidget *currentWindow;
    const gchar *filename;
    const gchar *nul;
    int showtime;
} SGlobalData;

int main(int argc, char *argv [])
{
    GtkWidget *main_window;
    SGlobalData data;
    GError *error = NULL;
    gchar *filename;
    data.showtime = 0;

    /* Initialize the GTK library */
    gtk_init(&argc, &argv);

    /* Open the Glade file for the main window */
    data.builder = gtk_builder_new();

    /* Create the path to OCR.glade depending on the OS */
    filename =  g_build_filename ("OCR.glade", NULL);

    /* Load OCR.glade */
    gtk_builder_add_from_file (data.builder, filename, &error);
    g_free (filename);
    if (error)
    {
        gint code = error->code;
        g_printerr("%s\n", error->message);
        g_error_free (error);
        return code;
    }

    /* Connect all the signals entered in Glade */
    gtk_builder_connect_signals(data.builder, &data);

    /* Get the pointer to the main window */
    main_window = GTK_WIDGET(gtk_builder_get_object (data.builder, "mainWindow"));

    /* Show the main window */
    gtk_widget_show_all (main_window);

    gtk_main();

    return 0;
}

void callback_file (GtkMenuItem *menuitem, gpointer user_data)
{
    /* Cast the user_data pointer to get the data */
    SGlobalData *data = (SGlobalData*) user_data;

    data->nul = gtk_menu_item_get_label(menuitem);

    /* Get the FileSelector window */
    data->currentWindow = GTK_WIDGET (gtk_builder_get_object (data->builder, "FileSelector"));
    
    /* Lock the window in wait of a response */
    gtk_dialog_run (GTK_DIALOG (data->currentWindow));

    gtk_widget_hide(data->currentWindow);
}

void callback_savefile (GtkMenuItem *menuitem, gpointer user_data)
{
    /* Cast the user_data pointer to get the data */
    SGlobalData *data = (SGlobalData*) user_data;

    data->nul = gtk_menu_item_get_label(menuitem);

    /* Get the FileSelector window */
    data->currentWindow = GTK_WIDGET (gtk_builder_get_object (data->builder, "FileSaver"));
    
    /* Lock the window in wait of a response */
    gtk_dialog_run (GTK_DIALOG (data->currentWindow));

    gtk_widget_hide(data->currentWindow);
}

void callback_cancel (GtkButton *cancel, gpointer user_data)
{
    SGlobalData *data = (SGlobalData*) user_data;

    data->nul = gtk_button_get_label(cancel);

    gtk_dialog_response(GTK_DIALOG(data->currentWindow), GTK_RESPONSE_CLOSE);
}


void callback_image(GtkButton *open, gpointer user_data)
{
    SGlobalData *data = (SGlobalData*) user_data;

    data->nul = gtk_button_get_label(open);

    /* Get the path to the .bmp image selected in the FileSelector */
    const gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(data->currentWindow));

    data->filename = filename;

    GtkImage *image = GTK_IMAGE(gtk_builder_get_object(data->builder, "Image"));

    /* Show the image selected in the GtkImage */
    gtk_image_set_from_file(image, filename);

    GtkButton *analyze = GTK_BUTTON(gtk_builder_get_object(data->builder, "Analyze"));

    gtk_button_set_label(analyze, "Analyze");

    gtk_dialog_response(GTK_DIALOG(data->currentWindow), GTK_RESPONSE_CLOSE);
}

void callback_OCR(GtkButton *analyze, gpointer user_data)
{
    SGlobalData *data = (SGlobalData*) user_data;

    printf("%s\n", data->filename);

    SDL_Surface* image;
    image = load_image("Images/image_text2BLACK.bmp");
    
    for(size_t i = 0; i < image->h; i++)
    {
        for(size_t j = 0; j < image->w; j++)
        {
            Uint32 pixel = get_pixel(image, j, i);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            printf("%i ", pixel);
            //array[i * image->w + j] = 0.3 * r + 0.59 * g + 0.11 * b;
        }
        printf("\n");
    }

    OCR(image, data->showtime);

    GtkTextBuffer *buff = GTK_TEXT_BUFFER(gtk_builder_get_object(data->builder, "Buffer"));

    //Recup results.txt
    FILE *resultFile;
    resultFile = fopen("./data/result.txt", "r");
    char lolresult = 0;
    char *resultChar = &lolresult;
    fscanf(resultFile, "%s", resultChar);
    fclose(resultFile);
    const gchar *result = (const gchar *)resultChar;

    gtk_text_buffer_set_text(buff, result, -1);

    gtk_button_set_label(analyze, "Done !");
}

void callback_about(GtkMenuItem *menuitem, gpointer user_data)
{
    SGlobalData *data = (SGlobalData*) user_data; 
    
    data->nul = gtk_menu_item_get_label(menuitem);
    
    GtkWidget *about = GTK_WIDGET(gtk_builder_get_object (data->builder, "About"));

    gtk_widget_show(about);

    gtk_dialog_run(GTK_DIALOG(about));

    gtk_widget_hide(about);
}

void callback_su (GtkMenuItem *version, gpointer user_data)
{
    SGlobalData *data = (SGlobalData*) user_data;

    data->nul = gtk_menu_item_get_label(version);

    data->showtime = !(data->showtime);

    /*if(data->showtime == 1)
        printf("Dev Mode");
    else
        printf("Normal Mode");*/
}

void callback_save(GtkButton *save, gpointer user_data)
{
    SGlobalData *data = (SGlobalData*) user_data;

    data->nul = gtk_button_get_label(save);

    GtkEntry *entry = GTK_ENTRY(gtk_builder_get_object (data->builder, "SaveEntry"));

    GtkFileChooser *file = GTK_FILE_CHOOSER(gtk_builder_get_object (data->builder, "FileSaver"));

    gchar *path = gtk_file_chooser_get_current_folder(file);

    const gchar *name = gtk_entry_get_text(entry);

    //copy result with new name
    char *pathChar = (char *)path;
    char *nameChar = (char *)name;
    if (nameChar == NULL)
        nameChar = "result";
    char fullPath[200];
    strcpy(fullPath, pathChar);
    strcat(fullPath, "/");
    strcat(fullPath, nameChar);
    strcat(fullPath, ".txt");
    char fullFullPath[236];
    sprintf(fullFullPath, "cp data/result.txt %s", fullPath);
    system(fullFullPath);

    gtk_dialog_response(GTK_DIALOG(data->currentWindow), GTK_RESPONSE_CLOSE);
}
