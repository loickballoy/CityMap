#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "build_city.h"
#include "../assign/assign.c"
#include "../assign/assign_tools.c"
#include "../assign/main.c"
#include "../loader/write.c"

//!gtk used struct
typedef struct s_Window
{
  GtkWidget *widget;
  GtkWidget *box;
  GtkWidget *label;
  GtkWidget *entry;
  GtkWidget *button;
  GtkWidget *map;
  GtkWidget *metro;
  GtkWidget *images;
  GtkWidget *legend;
  GtkWidget *texts;

  GtkWidget *policy;
  GtkWidget *job;
  GtkWidget *habitation;
  GtkWidget *economy;
  GtkWidget *health;
  GtkWidget *security;
  
} t_Window;

const char *nb_habitant;

const char *policy;
const char *job;
const char *habitation;
const char *economy;
const char *health;
const char *security;

//!makes a matrice
char **MakeMatrice(struct cell *map, int DIM)
{

  char **matrice =  malloc(sizeof(char *)* DIM);

  for(int k = 0; k < DIM; k++)
  {
    matrice[k] = malloc(sizeof(char *) * DIM);
  }

  int souslist = -1;
  for (int i = 0; i < DIM*DIM; i++)
  {
    if(i % DIM == 0)
    {
      souslist++;
      printf("\n");
    }
    if(((map+i)->type) != -1)
      matrice[souslist][i%DIM] = ((map+i)->type)+'0';
    if(((map+i)->type) == -1)
      matrice[souslist][i%DIM] = 7;
    
  }
  return matrice;
}

//!Using Gtk to define events on click event
gboolean on_click_button (GtkWidget *button, GdkEventButton *event, gpointer data)
{
    t_Window *my_w = (t_Window*) data;

    // Get the text given in GtkEntry
    
    nb_habitant = gtk_entry_get_text(GTK_ENTRY(my_w->entry));

    policy = gtk_entry_get_text(GTK_ENTRY(my_w->policy));
    job = gtk_entry_get_text(GTK_ENTRY(my_w->job));
    habitation = gtk_entry_get_text(GTK_ENTRY(my_w->habitation));
    economy = gtk_entry_get_text(GTK_ENTRY(my_w->economy));
    health = gtk_entry_get_text(GTK_ENTRY(my_w->health));
    security = gtk_entry_get_text(GTK_ENTRY(my_w->security));

    int pol_int = atoi(policy);
    int job_int = atoi(job);
    int habb_int = atoi(habitation);
    int eco_int = atoi(economy);
    int hea_int = atoi(health);
    int sec_int = atoi(security);

    int *biais = calloc(6, sizeof(int));

    biais[0] = pol_int;
    biais[1] = job_int;
    biais[2] = habb_int;
    biais[3] = eco_int;
    biais[4] = hea_int;
    biais[5] = sec_int;

    
    write_bias(biais);

    int hab_int = atoi(nb_habitant);
    struct map* map = testAssign(hab_int, 50);
    int DIM = map->maxWidth;
    char **matrice = MakeMatrice(map->cells, DIM);

    build_city(matrice, DIM);

    gtk_widget_destroy(my_w->images);

    GdkPixbuf *p_map;
    p_map = gdk_pixbuf_new_from_file_at_size("CityMap.png",800,800,NULL);
    my_w->map = gtk_image_new_from_pixbuf (p_map);

    GdkPixbuf *p_metro;
    p_metro = gdk_pixbuf_new_from_file_at_size("Metro.png",800,800,NULL);
    my_w->metro = gtk_image_new_from_pixbuf (p_metro);

    my_w->legend = gtk_image_new_from_file("legend.png");

    my_w->images = gtk_grid_new();

    gtk_grid_attach(my_w->images, my_w->map,0,0,1,1);
    gtk_grid_attach(my_w->images, my_w->metro,1,0,1,1);
    gtk_grid_attach(my_w->images, my_w->legend,2,0,1,1);

    gtk_box_pack_start (GTK_BOX(my_w->box), my_w->images, TRUE, TRUE, 0);


    gtk_widget_show_all(my_w->widget);

    return FALSE;
}

//!Runs the Gtk GUI
void RunGTK(int argc, char **argv){
  t_Window *my_window = (t_Window*) malloc (sizeof (t_Window));
  if (my_window == NULL)
    exit(EXIT_FAILURE);

  // GTK initialisation
  gtk_init( &argc, &argv );

  // Widget initialisation
  my_window->widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  my_window->box = gtk_box_new( TRUE, 0 );
  my_window->button = gtk_button_new_with_label("Lancer CityMap");
  my_window->label = gtk_label_new("Bienvenue sur CityMap");
  my_window->entry = gtk_entry_new();

  my_window->policy = gtk_entry_new();
  my_window->job = gtk_entry_new();
  my_window->habitation = gtk_entry_new();
  my_window->economy = gtk_entry_new();
  my_window->health = gtk_entry_new();
  my_window->security = gtk_entry_new();
  

  gtk_entry_set_placeholder_text(my_window->entry, "Habitants");
  
  gtk_entry_set_placeholder_text(my_window->policy, "[Politique]");
  gtk_entry_set_placeholder_text(my_window->job, "[Travail]");
  gtk_entry_set_placeholder_text(my_window->habitation, "[Logement]");
  gtk_entry_set_placeholder_text(my_window->economy, "[Commerce]");
  gtk_entry_set_placeholder_text(my_window->health, "[Santé]");
  gtk_entry_set_placeholder_text(my_window->security, "[Sécurité]");

  my_window->texts = gtk_grid_new();

  gtk_grid_attach(my_window->texts, my_window->button,7,0,2,1);

  gtk_grid_attach(my_window->texts, my_window->entry,0,0,1,1);

  gtk_grid_attach(my_window->texts, my_window->policy,1,0,1,1);
  gtk_grid_attach(my_window->texts, my_window->job,2,0,1,1);
  gtk_grid_attach(my_window->texts, my_window->habitation,3,0,1,1);
  gtk_grid_attach(my_window->texts, my_window->economy,4,0,1,1);
  gtk_grid_attach(my_window->texts, my_window->health,5,0,1,1);
  gtk_grid_attach(my_window->texts, my_window->security,6,0,1,1);
  
  

  my_window->map = gtk_image_new_from_file("map.png");
  my_window->metro = gtk_image_new_from_file("metro.png");
  my_window->legend = gtk_image_new_from_file("legend.png");

  my_window->images = gtk_grid_new();

  gtk_grid_attach(my_window->images, my_window->map,0,0,1,1);
  gtk_grid_attach(my_window->images, my_window->metro,1,0,1,1);
  gtk_grid_attach(my_window->images, my_window->legend,2,0,1,1);

  

  // First, we add GtkHBox inside GtkWindow
  gtk_container_add(GTK_CONTAINER(my_window->widget), my_window->box );

  // Then we add the Widgets inside GtkHBox
  gtk_box_pack_start (GTK_BOX(my_window->box), my_window->entry, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX(my_window->box), my_window->label, TRUE, TRUE, 0);
  

   gtk_box_pack_start (GTK_BOX(my_window->box), my_window->texts, TRUE, TRUE, 0);
  
  gtk_box_pack_start (GTK_BOX(my_window->box), my_window->images, TRUE, TRUE, 0);


  // We connect the button to the "clicked" event
  g_signal_connect(my_window->button, "button-press-event", (GCallback)on_click_button, my_window);

  // Gtk displays what our window contains
  gtk_widget_show_all(my_window->widget);

  gtk_main();
}




int main (int argc, char **argv)
{
  RunGTK(argc, argv);
  return 0;
  }
