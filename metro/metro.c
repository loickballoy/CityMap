#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

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
