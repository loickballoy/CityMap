#include "read.h"
#include <stdio.h>

void write_habitant_number(int habitant_number)
{
	FILE *file = settings_open(SETTINGS_PATH);
	char buffer[LINE_BUFFER_SIZE];
	fgets(buffer, LINE_BUFFER_SIZE, file);
	int habitant_number;
	while(!isHabitant(buffer))
		fgets(buffer, LINE_BUFFER_SIZE, file);
	write_value(i, , buffer);
	fclose(file);
}

