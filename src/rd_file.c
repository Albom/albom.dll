
/*
 * Copyright 2011-2021, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#include "seansRd.h"

/// =============================

int seansRd_load(char *filename, seansRd_data *seans)
{
FILE *file;
short  *tempw;
int r, p; // развёртки, точки
int n; // текущая точка

file = fopen(filename, "rb");
if (file == NULL)
    return ERR_FILE;

tempw = (short*) malloc(7*sizeof(short));
if (tempw == NULL)
    return ERR_MEM;

fread(tempw, sizeof(short), 7, file);
seans -> day = tempw[0];
seans -> month  = tempw[1];
seans -> year = tempw[2];
seans -> hour = tempw[3];
seans -> minute = tempw[4];
seans -> second = tempw[5];
seans -> nr = tempw[6];

fread(&(seans -> np), sizeof(int), 1, file);

fread(&(seans -> nc), sizeof(short), 1, file);

fread(&(seans -> lag), sizeof(double), 1, file);

fread(&(seans -> freq), sizeof(double), 1, file);

fread(tempw, sizeof(short), 5, file); // 10 байт пустого пространства

free(tempw);



tempw = (short*) malloc(seans -> nc * seans -> np * seans -> nr * sizeof(short));
if (tempw == NULL)
    return ERR_MEM;

fread(tempw, sizeof(short), seans -> nc * seans -> np * seans -> nr, file);

fclose(file);

seans -> dat4 = seans -> dat3 = seans -> dat2 = seans -> dat1 = NULL;

switch (seans -> nc) // cases without breaks!!!
    {
    case 4:
        seans -> dat4 = (int*) malloc(seans -> np * seans -> nr * sizeof(int));
        if (seans -> dat4 == NULL)
            return ERR_MEM;
    case 3:
        seans -> dat3 = (int*) malloc(seans -> np * seans -> nr * sizeof(int));
        if (seans -> dat3 == NULL)
            return ERR_MEM;
    case 2:
        seans -> dat2 = (int*) malloc(seans -> np * seans -> nr * sizeof(int));
        if (seans -> dat2 == NULL)
            return ERR_MEM;
    case 1:
        seans -> dat1 = (int*) malloc(seans -> np * seans -> nr * sizeof(int));
        if (seans -> dat1 == NULL)
            return ERR_MEM;
    }

n = 0;
for (r = 0 ; r < seans -> nr ; r++)
    for (p = 0 ; p < seans -> np ; p++)
        {
        seans -> dat1[n] = (int) tempw[seans->nc*(r*seans->np + p) + 0];
        if ( seans->nc > 1)
            seans -> dat2[n] = (int) tempw[seans->nc*(r*seans->np + p) + 1];
        if ( seans->nc > 2)
            seans -> dat3[n] = (int) tempw[seans->nc*(r*seans->np + p) + 2];
        if ( seans->nc > 3)
            seans -> dat4[n] = (int) tempw[seans->nc*(r*seans->np + p) + 3];
        n++;
        }

free(tempw);

return OK;
}

/// =============================

int seansRd_close(seansRd_data *seans)
{

if (seans == NULL)
    return 0;

if (seans -> dat1 != NULL)
    free(seans -> dat1);

if (seans -> dat2 != NULL)
    free(seans -> dat2);

if (seans -> dat3 != NULL)
    free(seans -> dat3);

if (seans -> dat4 != NULL)
    free(seans -> dat4);

return OK;
}

