
/*
 * Copyright 2011-2021, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#include "file_c_old.h"



int seans1c_test(char *filename) {
    FILE *file;
    long fileSize;

    file = fopen (filename, "rb");

    if (file == NULL)
        return 0;

    fseek (file,0,SEEK_END);
    fileSize = ftell(file);

    fclose(file);

    if (fileSize == 21650)
        return 1;

    if (fileSize == 22370)
        return 2;

    if (fileSize == 21620)
        return 3;

    return 0;
}



double seans1c_alt(int H) {
    return H*9.821-35;//-44.815+9.821/2;
}



int seans1cv_load(char *filename, seans1c_data *seans) {

    FILE *file;

    char *buffer;
    unsigned char  header[20];
    unsigned char  temp[4];
    int mem_need; // сколько памяти нужно для буфера
    int i, j;
    unsigned sm = 0;
    int isM; // есть ли метки?


    isM = seans1c_test(filename);
    if (isM == 0)
        return 0;

    if (isM == 2)
        mem_need = 4*(3*360 + 360*2*6) + 30 + 360*2; // количество необходимой памяти для буфера (с учётом меток)
    else
        mem_need = 4*(3*360 + 360*2*6); // количество необходимой памяти для буфера

    buffer = (char*) malloc( mem_need ); // выделить память для буфера

    file = fopen (filename, "rb");
    if (file == NULL)
        return 0;

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

    sm = 0;

    for (i = 0; i < 360 ; i++) {
        memcpy(temp, buffer+sm, 4);
        seans -> dat0[i] = makeint(temp);
        sm += 4;

        memcpy(temp, buffer+sm, 4);
        seans -> dat1[i][0] = makeint(temp);
        sm += 4;

        memcpy(temp, buffer+sm, 4);
        seans -> dat2[i][0] = makeint(temp);
        sm += 4;
    }

    for (j = 1; j < 7; j++) {
        for (i = 0; i < 360 ; i++) {
            memcpy(temp, buffer+sm, 4);
            seans -> dat1[i][j] = makeint(temp);
            sm += 4;

            memcpy(temp, buffer+sm, 4);
            seans -> dat2[i][j] = makeint(temp);
            sm += 4;
        }
    }

    if (isM == 2) {
        //sm = 21650-20; // 20 байт - заголовок
        sm += 30;
        for (i = 0; i < 360 ; i++) {
            seans -> m[i] = buffer[sm+1]*256+buffer[sm];
            sm += 2;
        }
    } else
        for (i = 0; i < 360 ; i++)
            seans -> m[i] = 0;

    free(buffer); // освобождение буфера

    return 1;
}



int seans1c_load(char *filename, seans1c_data *seans) {

    FILE *file;

    char *buffer;
    unsigned char  header[20];
    unsigned char  temp[4];
    int mem_need; // сколько памяти нужно для буфера
    int i, j;
    unsigned sm = 0;
    int isM; // есть ли метки?


    isM = seans1c_test(filename);
    if (isM == 0)
        return 0;

    if (isM == 2)
        mem_need = 4*(3*360 + 360*2*6) + 30 + 360*2; // количество необходимой памяти для буфера (с учётом меток)
    else
        mem_need = 4*(3*360 + 360*2*6); // количество необходимой памяти для буфера

    buffer = (char*) malloc( mem_need ); // выделить память для буфера

    file = fopen (filename, "rb");
    if (file == NULL)
        return 0;

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

    sm = 0;

    for (j = 0; j < 7; j++) {
        for (i = 0; i < 360 ; i++) {
            memcpy(temp, buffer+sm, 4);
            seans -> dat1[i][j] = makeint(temp);
            sm += 4;

            memcpy(temp, buffer+sm, 4);
            seans -> dat2[i][j] = makeint(temp);
            sm += 4;
        }
    }

    for (i = 0; i < 360 ; i++) {
        seans -> dat0[i] = 0;
        sm += 4;
    }

    if (isM == 2) {
        //sm = 21650-20; // 20 байт - заголовок
        sm += 30;
        for (i = 0; i < 360 ; i++) {
            seans -> m[i] = buffer[sm+1]*256+buffer[sm];
            sm += 2;
        }
    } else
        for (i = 0; i < 360 ; i++)
            seans -> m[i] = 0;

    free(buffer); // освобождение буфера

    return 1;
}



int seans1c_noise1(seans1c_data *seans, double *noise_acf, int len, int alt_start, int alt_end) {
    int i, j, k;

    for (i = 0; i < len; i++)
        noise_acf[i] = 0;

    k = 0; // обнулим счётчик количества "хороших" высот
    for (j = alt_start; j < alt_end; j++) {
        if (seans->m[j] == 0) {
            for (i = 0; i < len; i++)
                noise_acf[i] += seans->dat1[j][i];
            k++;
        } // if
    } // j

    if (k == 0) {
        for (i = 0; i < len; i++)
            noise_acf[i] = 0;
        return 1;
    }

    for (i = 0; i < len; i++)
        noise_acf[i] /= k;

    return 0;
}



int seans1c_noise2(seans1c_data *seans, double *noise_acf, int len, int alt_start, int alt_end) {
    int i, j, k;

    for (i = 0; i < len; i++)
        noise_acf[i] = 0;

    k = 0; // обнулим счётчик количества "хороших" высот
    for (j = alt_start; j < alt_end; j++) {
        if (seans->m[j] == 0) {
            for (i = 0; i < len; i++)
                noise_acf[i] += seans->dat2[j][i];
            k++;
        } // if
    } // j

    if (k == 0) {
        for (i = 0; i < len; i++)
            noise_acf[i] = 0;
        return 1;
    }

    for (i = 0; i < len; i++)
        noise_acf[i] /= k;

    return 0;
}



int seans1c_saveM0(char *filename) {
    int isM; // есть ли метки?
    FILE *file;

    isM = seans1c_test(filename);

    if (isM == 0)
        return 0;

    if (isM == 1)
        return 1;

    file = fopen(filename, "a+b");
    if (file == NULL)
        return 0;

    ftruncate(fileno(file), 21650);

    fclose(file);

    return 1;
}



int seans1c_saveM3(char *filename, seans1c_data *seans) {
    int isM;
    FILE *file;
    int i;
    short buf[360];

    isM = seans1c_test(filename);

    if (isM == 0)
        return 0;

    file = fopen (filename, "a+b");
    if (file == NULL)
        return 0;

    ftruncate(fileno(file), 21650);

    for (i = 0; i < 360; i++)
        buf[i] = (short)(seans->m[i]);

    fseek(file, 0, SEEK_END);
    fwrite(buf, 360*2, 1, file);

    fclose (file);

    return 1;
}
