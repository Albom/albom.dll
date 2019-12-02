
/*
 * Copyright 2011-2019, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#include "seans3.h"

/// =============================

int seans3_load(char *filename, seans3_data *seans)
{
FILE *file;
short  *tempw;
int r, p; // развёртки, точки
unsigned short magic;
int n; // текущая точка

file = fopen(filename, "rb");
if (file == NULL)
    return ERR_FILE;

tempw = (short*) malloc(8*sizeof(short));
if (tempw == NULL)
    return ERR_MEM;

fread(tempw, sizeof(short), 8, file);
seans -> day = tempw[0];
seans -> month  = tempw[1];
seans -> year = tempw[2];
seans -> hour = tempw[3];
seans -> minute = tempw[4];
seans -> second = tempw[5];
seans -> np = tempw[6];
seans -> nr = tempw[7];

fread(&(seans -> freq), sizeof(double), 1, file);

fread(&magic, sizeof(unsigned short), 1, file); // магическое число
seans -> magic = magic;

if (seans->magic != 55899)
    {
    fclose(file);
    free(tempw);
    return ERR_MAGIC;
    }

fread(tempw, sizeof(short), 4, file); // 8 байт пустого пространства

free(tempw);



tempw = (short*) malloc(4 * seans -> np * seans -> nr * sizeof(short));
if (tempw == NULL)
    return ERR_MEM;

fread(tempw, sizeof(short), 4 * seans -> np * seans -> nr, file);

fclose(file);

seans -> dat1 = (int*) malloc(seans -> np * seans -> nr * sizeof(int));
seans -> dat2 = (int*) malloc(seans -> np * seans -> nr * sizeof(int));
seans -> dat3 = (int*) malloc(seans -> np * seans -> nr * sizeof(int));
seans -> dat4 = (int*) malloc(seans -> np * seans -> nr * sizeof(int));

if ((seans -> dat1 == NULL)||(seans -> dat2 == NULL)||(seans -> dat3 == NULL)||(seans -> dat4 == NULL))
    return ERR_MEM;

n = 0;
for (r = 0 ; r < seans -> nr ; r++)
    for (p = 0 ; p < seans -> np ; p++)
        {
        seans -> dat1[n] = (int) tempw[4*(r*seans->np + p) + 0];
        seans -> dat2[n] = (int) tempw[4*(r*seans->np + p) + 1];
        seans -> dat3[n] = (int) tempw[4*(r*seans->np + p) + 2];
        seans -> dat4[n] = (int) tempw[4*(r*seans->np + p) + 3];
        n++;
        }

free(tempw);

return OK;
}




/// =============================

int seans3_close(seans3_data *seans)
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

return 0;
}
