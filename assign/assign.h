#ifndef ASSIGN_H
#define ASSIGN_H

#define RDMRANGE 8

//! Runs two map generations and returns the most optimal of both maps
struct map *minMaxMap(struct map *newMap, struct map *testMap);

//! Initalises the terrain on which our functions will work
struct map *initMap(unsigned int maxH, unsigned int maxW);

//! Fills the town with buildings from the buildingList according to the needs spread around the map
int fillTown(struct map *map, int *buildingList, int roof, int **building_value);

//! Acts as a test for map modulation in order to get the best map/city possible
void replaceTown(struct map *map, int *buildingList, int roof, int **building_value, int *nbreplacement);

//! The search algorithm used to find the best possible building in the modulation phase
struct cell *replaceGlobalNeed(struct map *map, int *buildingList ,int *maxstat,int roof, int *a);

//! The search algorithm used to find the best possible building in the first filling phase
struct cell *searchGlobalNeed(struct map *map, int *buildingList, int *maxstat, int roof, int *a);

//! Generates a random building when the search algorithm was unsuccesful
struct cell *generateRandomBuilding(struct map *map, int *buildingList, int *maxstat, int *a, int nbcompt);

struct cell **generateRandomSubway(struct map *map, int *buildingList);

#endif
