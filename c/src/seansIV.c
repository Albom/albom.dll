
/*
 * Copyright 2011-2019, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#include "seansIV.h"

int seansIV_load(char *filename, seansIV_data *seans)
{

    FILE *f = fopen(filename, "rb");
    if (f == NULL)
    {
        return ERR_FILE;
    }

    fread(&seans->ver, sizeof(int), 1, f);
    fread(seans->date, 1, 20, f);
    fread(&seans->nR, sizeof(int), 1, f);
    fread(&seans->nP, sizeof(int), 1, f);
    fread(&seans->dT, sizeof(int), 1, f);

    fseek(f, 44, SEEK_CUR);

    seans->scans = malloc(7*seans->nR*sizeof(seansIV_scan));
    for (int i = 0; i < 7*seans->nR; i++)
    {
        seans->scans[i].data1 = malloc(seans->nP*sizeof(short));
        seans->scans[i].data2 = malloc(seans->nP*sizeof(short));
        fread(&seans->scans[i].type, 1, 1, f);
        fread(seans->scans[i].data1, sizeof(short), seans->nP, f);
        fread(seans->scans[i].data2, sizeof(short), seans->nP, f);
    }

    fclose(f);

    return OK;
}


int seansIV_close(seansIV_data *seans)
{
    for (int i = 0; i < seans->nR; i++)
    {
        free(seans->scans[i].data1);
        free(seans->scans[i].data2);
    }
    free(seans->scans);
    return OK;
}
