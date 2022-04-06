#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gtk/gtk.h>
#include "build_city.h"
#include "../assign/assign.c"
#include "../assign/main.c"

typedef struct s_Window
{
    GtkWidget *widget;
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *entry;
    GtkWidget *button;
} t_Window;

const char *nb_habitant;

char **MakeMatrice(struct cell *map)
{

  int DIM = 40;
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
    printf("%c ;",matrice[souslist][i%DIM]);
  }
  return matrice;
}

gboolean on_click_button (GtkWidget *button, GdkEventButton *event, gpointer data)
{
    t_Window *my_w = (t_Window*) data;

// On récupère le texte contenu dans la GtkEntry
    nb_habitant = gtk_entry_get_text(GTK_ENTRY(my_w->entry));

    int hab_int = atoi(nb_habitant);

    char **matrice = MakeMatrice(testAssign(hab_int, 50)->cells);

    build_city(matrice);   //TODO :Passer en parametre le nombre d'habitant

    printf("Execute Build_City avec %s habitants \n", nb_habitant);

// On redonne la main à GTK
    return FALSE;
}

void RunGTK(int argc, char **argv){
  t_Window *my_window = (t_Window*) malloc (sizeof (t_Window));
  if (my_window == NULL)
    exit(EXIT_FAILURE);

  // On initialise GTK
  gtk_init( &argc, &argv );

  // On initialise les Widgets
  my_window->widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  my_window->box = gtk_hbox_new( TRUE, 0 );
  my_window->button = gtk_button_new_with_label("Lancer");
  my_window->label = gtk_label_new("Bienvenue sur CityMap");
  my_window->entry = gtk_entry_new();

  // Tout d'abord, on met la GtkHBox dans la GtkWindow :
  gtk_container_add(GTK_CONTAINER(my_window->widget), my_window->box );

  // Puis on met les Widgets dans la GtkHBox:
  gtk_box_pack_start (GTK_BOX(my_window->box), my_window->entry, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX(my_window->box), my_window->button, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX(my_window->box), my_window->label, TRUE, TRUE, 0);

  // On connecte le bouton à l'évenement « clicked »
  g_signal_connect(my_window->button, "button-press-event", (GCallback)on_click_button, my_window);

  // On demande enfin à GTK de montrer notre Window et ce qu'elle contient :
  gtk_widget_show_all(my_window->widget);

  // Puis on entre dans la boucle GTK qui garde la fenêtre ouverte
  gtk_main();
}




int main (int argc, char **argv)
{
  RunGTK(argc, argv);
  return 0;
}
