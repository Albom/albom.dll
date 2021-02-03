
/*
 * Copyright 2011-2021, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#include "file_h.h"

int seansH_load(char *fileName, seansH_data *seans)
{

FILE *file;

short dateTime[6];
short n[3];

char *buffer;
size_t bufferSize = 680*114*8*4 + 680*8*6;
size_t sm = 0;

int i, j;

file = fopen (fileName, "rb");
if (file == NULL)
    return 0;

fread(dateTime, sizeof(short), 6, file);

seans->day    = dateTime[0];
seans->month  = dateTime[1];
seans->year   = dateTime[2];
seans->hour   = dateTime[3];
seans->minute = dateTime[4];
seans->second = dateTime[5];

fread(n, sizeof(short), 3, file);
seans->nH = n[0];
seans->nP = n[1];
seans->nR = n[2];


fread(&seans->dT, sizeof(double), 1, file);
fread(&seans->dH, sizeof(double), 1, file);

fread(&seans->magic, sizeof(short), 1, file);

int temp;
fread(&temp, sizeof(int), 1, file);

buffer = (char*) malloc( bufferSize ); // выделить память для буфера
if (buffer == NULL)
    {
    fclose(file);
    return 0;
    }

fread(buffer, bufferSize, 1, file); // считать данные в буфер
fclose (file); // закрыть файл

for (i = 0; i < 680 ; i++)
	for (j = 0; j < 114; j++)
		{
        memcpy(& seans -> dat1[i][j] , buffer+sm, 8);
        sm += 8;
		}

for (i = 0; i < 680 ; i++)
	for (j = 0; j < 114; j++)
		{
		memcpy(& seans -> dat2[i][j] , buffer+sm, 8);
		sm += 8;
		}

for (i = 0; i < 680 ; i++)
	for (j = 0; j < 114; j++)
		{
		memcpy(& seans -> dat3[i][j] , buffer+sm, 8);
		sm += 8;
		}

for (i = 0; i < 680 ; i++)
	for (j = 0; j < 114; j++)
		{
		memcpy(& seans -> dat4[i][j] , buffer+sm, 8);
		sm += 8;
		}

// загрузка "нуля" АЦП
for (i = 0; i < 680 ; i++)
	{
	memcpy( & seans -> dat01[i], buffer+sm, 8);
	sm += 8;
	}

for (i = 0; i < 680 ; i++)
	{
	memcpy( & seans -> dat02[i], buffer+sm, 8);
	sm += 8;
	}


// загрузка мощности по короткому импульсу

for (i = 0; i < 680 ; i++)
	{
	memcpy( & seans -> datps1[i], buffer+sm, 8);
	sm += 8;
	}

for (i = 0; i < 680 ; i++)
	{
	memcpy( & seans -> datps2[i], buffer+sm, 8);
	sm += 8;
	}

// загрузка "нуля" АЦП

for (i = 0; i < 680 ; i++)
	{
	memcpy( & seans -> dat03[i], buffer+sm, 8);
	sm += 8;
	}

for (i = 0; i < 680 ; i++)
	{
	memcpy( & seans -> dat04[i], buffer+sm, 8);
	sm += 8;
	}


free(buffer);

return 1;
}
