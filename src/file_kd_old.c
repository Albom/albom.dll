
/*
 * Copyright 2011-2021, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#include "file_kd_old.h"


int seans1kd_load(char *filename, seans1kd_data *seans) {

    FILE *file;
    char date_time[64];

    file = fopen(filename, "rb");
    if (file == NULL)
        return 0;

    fread( date_time, 64, 1, file );

    seans->day =   date_time[23]*10 + date_time[24];
    seans->month = date_time[15]*10 + date_time[16];
    seans->year =  date_time[31]*1000 + date_time[32]*100 + date_time[33]*10 + date_time[34];

    return 1;
}
