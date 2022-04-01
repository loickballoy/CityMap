#ifndef NEED_H
#define NEED_H

unsigned int *select(unsigned char type);

struct building *build(unsigned char type);

struct building **initTownList();

struct buildList **initTownList2(unsigned int nb_hab, unsigned int sec);

unsigned int *initTownList3(unsigned int nb_hab, double sec);


#endif
