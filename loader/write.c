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
	write_value(habitant_number, 0, file);
	fclose(file);
}

int digit(int value)
{
	for (int i = 0; i
}

int write_value(int value, char end, file)
{
	while (*building_line != '[')
        ++building_line;
	++building_line;

	char buff[32];
	sprintf(buff, "%d", value);
	
	ssize_t x = write(file, buffer, 
}
