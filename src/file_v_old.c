
/*
 * Copyright 2011-2021, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#include "file_v_old.h"


int seans1v_test(char *filename) {
    FILE *file;
    long size;

    file = fopen (filename, "rb");

    if (file == NULL)
        return 0;

    fseek (file,0,SEEK_END);
    size = ftell(file);

    fclose(file);

    if (size == 21200) // without labels
        return 1;

    if (size == 21430) // with labels (no compatibility with old (KENTAVR) program)
        return 2;

    return 0;
}



int seans1v_load(char *filename, seans1v_data *seans) {
    FILE *file;

    char *buffer;
    unsigned char  header[20];
    int mem_need; // сколько памяти нужно для буфера

    int isM; // есть ли метки?

    isM = seans1v_test(filename);
    if (isM == 0) {
        return 0;
    }

    if (isM == 2) {
        mem_need =  4*(230 + 230*2*10 + 230*2 + 230); // количество необходимой памяти для буфера (с учётом меток)
    } else {
        mem_need = 4*(230 + 230*2*10 + 230*2); // количество необходимой памяти для буфера
    }

    buffer = (char*) malloc( mem_need ); // выделить память для буфера

    file = fopen (filename, "rb");
    if (file == NULL) {
        return 0;
    }

    fread(header, 20, 1, file); // считать заголовок файла

    seans -> day = header[0]*256+header[1];
    seans -> month = header[2]*256+header[3];
    seans -> year = header[4]*256+header[5];

    seans -> hour = header[6]*256+header[7];
    seans -> minute = header[8]*256+header[9];
    seans -> second = header[10]*256+header[11];

    seans -> nseans = header[12]*256+header[13];
    seans -> nr0 = header[14]*256+header[15];
    seans -> nr1 = header[16]*256+header[17];

    seans -> u1 = header[18]*256+header[19];

    fread(buffer, mem_need, 1, file); // считать данные в буфер

    fclose (file);

    for (int i = 0; i < 230 ; i++) {
        seans->dat_cos[i][1] = buffer[4*i*21];
        seans->dat_sin[i][1] = buffer[4*i*21+4];
        seans->dat_cos[i][0] = buffer[4*i*21+8];
        seans->dat_sin[i][0] = 0;

        for (int j = 2; j < 11; j++) {
            seans->dat_cos[i][j] = buffer[4*i*21+j*4+4];
            seans->dat_sin[i][j] = buffer[4*i*21+j*4+4];
        }
    }

    for (int i = 0; i < 230 ; i++) {
        seans->datm_cos[i] = buffer[4*i*2+19340];
        seans->datm_cos[i] = buffer[4*i*2+19340+4];
    }

    if (isM == 2) {
        for (int i = 0; i < 230 ; i++) {
            seans->datm_cos[i] = buffer[4*i+21180];
        }
    }

    return 1;
}



int seans1v_saveM0(char *filename) {
    int isM; // есть ли метки?
    FILE *file;

    isM = seans1v_test(filename);
    if (isM == 0)
        return 0;

    if (isM == 1)
        return 1;

    file = fopen(filename, "a+b");
    if (file == NULL)
        return 0;

    ftruncate(fileno(file), 21200);

    fclose(file);

    return 1;
}



int seans1v_saveM3(char *filename, seans1v_data *seans) {
    int isM; // есть ли метки?
    FILE *file;

    isM = seans1v_test(filename);
    if (isM == 0)
        return 0;

    file = fopen (filename, "a+b");
    if (file == NULL)
        return 0;

    ftruncate(fileno(file), 21180);

    fseek(file, 0, SEEK_END);

    fwrite(&seans->m, 230*4, 1, file);
    /*
    for (int i = 0; i < 230; i++) {
        buf[i*2] = (seans->m[i]) & 0xff;
        buf[i*2+1] = (seans->m[i]/256) & 0xff;



    }
    */

    fclose (file);

    return 1;
}
