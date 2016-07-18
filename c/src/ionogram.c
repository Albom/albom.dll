
/*
 * Copyright 2011-2016, Oleksandr Bogomaz (albom85@yandex.ru)
 */

#include "ionogram.h"

int ionogram_load(char *filename, ionogram_basis *ionogram)
{

FILE *file;
long fileSize;
int nf;       // number of frequencies 
int nh = 250; // number of altitudes
int nr = 16;  // number of repeats on one frequency
char header[21];
unsigned char *data;

file = fopen(filename, "rb");
if (file == NULL)
    return 0;

fseek (file, 0, SEEK_END);
fileSize = ftell(file);

switch (fileSize)
{
    case 1600021:
        nf = 400;
        break;
    case 1200021:
        nf = 300;
        break;
    default:
        fclose(file);
        return 0;
}

ionogram->nf = nf;
ionogram->nr = nr;
ionogram->nh = nh;

fseek (file, 0, SEEK_SET);

fread(&header, 21, 1, file);

ionogram->day   = (int)(header[1] - '0')*10 + (int)(header[2] - '0');
ionogram->month = (int)(header[4] - '0')*10 + (int)(header[5] - '0');
ionogram->year  = (int)(header[7] - '0')*1000 + (int)(header[8] - '0')*100 + (int)(header[9] - '0')*10 + (int)(header[10] - '0');

ionogram->hour   = (int)(header[12] - '0')*10 + (int)(header[13] - '0');
ionogram->minute = (int)(header[15] - '0')*10 + (int)(header[16] - '0');
ionogram->second = (int)(header[18] - '0')*10 + (int)(header[19] - '0');

data = (unsigned char*) malloc( fileSize-21 );

fread(data, fileSize-21, 1, file);

int offset = 0;
for (int f = 0; f < nf; f++)
    for (int r = 0; r < nr; r++)
        for (int h = 0; h < nh; h++)
            {
            ionogram->data[r][f][h] = data[offset];
            offset++;
            }

free(data);

fclose(file);

return 1;
}
