
/*
 * Copyright 2011-2019, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#include "seans3c3.h"

int seans3c3_load(char *filename, seans3c3_data *seans)
{
    FILE *file;
    short  *tempw;

    tempw = (short*) malloc(sizeof(short));
    if (tempw == NULL)
        return ERR_MEM;

    file = fopen(filename, "rb");
    if (file == NULL)
        return ERR_FILE;

    fread(tempw, sizeof(short), 1, file);
    if (*tempw <= 0)
        return ERR_TYPE;

    seans -> np = *tempw;

    fread(tempw, sizeof(short), 1, file);
    if (*tempw <= 0)
        return ERR_TYPE;

    seans -> nr = *tempw;

    fread(&seans->lag, sizeof(double), 1, file);

    fseek(file,10,SEEK_CUR);

    free(tempw);

    seans->tdatetime = (double*) malloc((seans->nr)*sizeof(double));
    if (seans->tdatetime == NULL)
        return ERR_MEM;

    seans->dat1 = (short*) malloc((seans->np)*(seans->nr)*sizeof(short));
    if (seans->dat1 == NULL)
        return ERR_MEM;

    seans->dat2 = (short*) malloc((seans->np)*(seans->nr)*sizeof(short));
    if (seans->dat2 == NULL)
        return ERR_MEM;

    seans->dat3 = (short*) malloc((seans->np)*(seans->nr)*sizeof(short));
    if (seans->dat3 == NULL)
        return ERR_MEM;

    int n = 0;
    for (int r = 0 ; r < seans -> nr ; r++)
    {
        fread(&seans->tdatetime[r], sizeof(double), 1, file);
        for (int p = 0 ; p < seans -> np ; p++)
        {

            fread(&seans->dat1[n], sizeof(short), 1, file);
            fread(&seans->dat2[n], sizeof(short), 1, file);
            fread(&seans->dat3[n], sizeof(short), 1, file);
            n++;
        }
    }
    return OK;
}
