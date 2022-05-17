#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/**
* @file graph.c
* @details This files creates and displays a graph (mainly used for tests).
* @author Remy Decourcelle <remy.decoutcelle@epita.fr>, Loïck Balloy <loick.balloy@epita.fr>, Axel Cochepin <axel.cochepin@epita.fr>, Guillaume Charvolin <guillaume.charvolin@epita.fr>
* @version 0.1
* @date 2022
*/



int main(void)
{
    Graph g1 = new_graph(5, false);

    add_edge(g1, 1, 2);
    add_edge(g1, 1, 5);
    add_edge(g1, 2, 4);
    add_edge(g1, 2, 3);
    add_edge(g1, 3, 4);
    add_edge(g1, 4, 5);
    add_edge(g1, 1, 4);

    print_graph(g1);
    display_graph(g1);
    erase_graph(g1);
    system("dot -Tpng graph.out -o graph.png");


    return 0;
}
