
/*
 * Copyright 2011-2016, Oleksandr Bogomaz (albom85@yandex.ru)
 */

#include "seans.h"

/// =============================

double seans1s_alt(int H) {
    return -82+H*4.583;
}

/// =============================

double seans1s_alt_front(int H) {
    return seans1s_alt(H)+49.7;
}

/// =============================

double seans1s_alt_795(int H) {
    return seans1s_alt(H)
           -10.5 // из-за того, что импульс не 663, а 795 мкс
           -4.5; // поправка, определённая экспериментально
}

/// =============================

int seans1s_test(char *filename) {
    FILE *file;
    long fileSize;

    file = fopen (filename, "rb");

    if (file == NULL)
        return 0;

    fseek (file,0,SEEK_END);
    fileSize = ftell(file);

    fclose(file);

    if ((fileSize == 18000) || (fileSize == 23823)||(fileSize == 18020))
        return 1;

    if (fileSize == 19360)
        return 2;

    if (fileSize == 17680)
        return 3;

    return 0;
}

/// =============================

int seans1s_load_header(char *filename, seans_header *header) {

    FILE *file;

    unsigned char  buffer[20];

    if ( seans1s_test(filename) == 0 )
        return 0;

    file = fopen (filename, "rb");
    if (file == NULL)
        return 0;

    fread(buffer, sizeof(char), 20, file); // считать заголовок файла
    fclose(file);

// разбор заголовка
    header -> day = buffer[0]*256+buffer[1];
    header -> month = buffer[2]*256+buffer[3];
    header -> year = buffer[4]*256+buffer[5];

    header -> hour = buffer[6]*256+buffer[7];
    header -> minute = buffer[8]*256+buffer[9];
    header -> second = buffer[10]*256+buffer[11];

    header -> nseans = buffer[12]*256+buffer[13];
    header -> nr0 = buffer[14]*256+buffer[15];
    header -> nr1 = buffer[16]*256+buffer[17];

    header -> u1 = buffer[18]*256+buffer[19];


    return 1;
}

/// =============================

int seans1s_load(char *filename, seans1s_data *seans) {

    FILE *file;

    char *buffer;
    unsigned char  header[20];
    unsigned char  temp[4];
    int mem_need; // сколько памяти нужно для буфера
    int i, j;
    unsigned sm = 0;
    int isM; // есть ли метки?

    isM = seans1s_test(filename);
    if (isM == 0)
        return 0;

    if ( (isM == 1) || (isM == 3) )
        mem_need = 4*(170*18 + 680*2); // количество необходимой памяти для буфера
    else
        mem_need = 4*(170*18 + 680*2) + 300 + 680*2; // количество необходимой памяти для буфера (с учётом меток)

    buffer = (char*) malloc( mem_need ); // выделить память для буфера
    if (buffer == NULL)
        return 0;

    file = fopen (filename, "rb");
    if (file == NULL)
        return 0;

    if (isM != 3) {
        fread(header, sizeof(char), 20, file); // считать заголовок файла

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
    } else {

        struct stat st;
        if (stat(filename, &st) < 0) {
            free(buffer);
            return 0;
        }

        unixtime_2date(st.st_mtime, &seans -> day, &seans -> month, &seans -> year,
                       &seans -> hour, &seans -> minute, &seans -> second);

        seans -> nseans = header[12]*256+header[13];
        seans -> nr0 = 1463;
        seans -> nr1 = 0;

        seans -> u1 = 0;
    }

    fread(buffer, mem_need, 1, file); // считать данные в буфер

    fclose (file);

    for (i = 0; i < 680 ; i++) {
        memcpy(temp, buffer+sm, 4);
        seans -> datp[i] = makeint(temp);
        sm += 4;
    }

    for (i = 0; i < 170 ; i++)
        for (j = 0; j < 18; j++) {
            memcpy(temp, buffer+sm, 4);
            seans -> dat[i][j] = makeint(temp);
            sm += 4;
        }

    for (i = 0; i < 680 ; i++) {
        memcpy(temp, buffer+sm, 4);
        seans -> datm[i] = makeint(temp);
        sm += 4;
    }

    if (isM == 2) {
        sm = 18000-20; // 20 байт - заголовок файла
        for (i = 0; i < 680 ; i++) {
            seans -> m[i] = buffer[sm+1]*256+buffer[sm];
            sm += 2;
        }
    } else {
        for (i = 0; i < 680 ; i++)
            seans -> m[i] = 0;
    }

    free(buffer); // освобождение буфера

    return 1;
}


/// =============================


int seans1s_save(char *filename, seans1s_data *seans) {

    FILE *f;
    int i, j;
    unsigned char c[4];
    unsigned char  header[20];
    unsigned char  buffer[300];

    f = fopen(filename, "wb");
    if (f == NULL)
        return 0;

// создание заголовка файла
    header[0] = ((seans -> day)/256) & 0xff;
    header[1] = (seans -> day) & 0xff;
    header[2] = ((seans -> month)/256) & 0xff;
    header[3] = (seans -> month) & 0xff;
    header[4] = ((seans -> year)/256) & 0xff;
    header[5] = (seans -> year) & 0xff;
    header[6] = ((seans -> hour)/256) & 0xff;
    header[7] =(seans -> hour) & 0xff;
    header[8] = ((seans -> minute)/256) & 0xff;
    header[9] =(seans -> minute) & 0xff;
    header[10] = ((seans -> second)/256) & 0xff;
    header[11] =(seans -> second) & 0xff;
    header[12] = ((seans -> nseans)/256) & 0xff;
    header[13] =(seans -> nseans) & 0xff;
    header[14] = ((seans -> nr0)/256) & 0xff;
    header[15] =(seans -> nr0) & 0xff;
    header[16] = ((seans -> nr1)/256) & 0xff;
    header[17] =(seans -> nr1) & 0xff;
    header[18] = ((seans -> u1)/256) & 0xff;
    header[19] = (seans -> u1) & 0xff;

    fwrite (header, 20, 1, f);

    for (i = 0; i < 680 ; i++) {
        makearray( c, seans -> datp[i]);
        fwrite (c, 4, 1, f);
    }

    for (i = 0; i < 170 ; i++)
        for (j = 0; j < 18; j++) {
            makearray( c, seans->dat[i][j]);
            fwrite (c, 4, 1, f);
        }

    for (i = 0; i < 680 ; i++) {
        makearray( c, seans -> datm[i]);
        fwrite (c, 4, 1, f);
    }

    for (i = 0; i < 300 ; i++)
        buffer[i] = 0;

    fwrite (buffer, 300, 1, f);

    fclose(f);

    return 0;
}

/// =============================

int seans1s_saveM0(char *filename) {
    int isM; // есть ли метки?
    FILE *file;

    isM = seans1s_test(filename);
    if (isM == 0)
        return 0;

    if (isM == 1)
        return 1;

    file = fopen(filename, "a+b");
    if (file == NULL)
        return 0;

    ftruncate(fileno(file), 18000);

    fclose(file);

    return 1;
}

/// =============================

int seans1s_saveM1(char *filename, int m, int num) {
    return 1;
}

/// =============================

int seans1s_saveM2(char *filename, int m[680]) {
    int isM; // есть ли метки?
//FILE *file;
//unsigned char buf[680*2];
//int i;

    isM = seans1s_test(filename);
    if (isM == 0)
        return 0;

    if (isM == 1)
        return 1;

    return 1;
}

/// =============================

int seans1s_saveM3(char *filename, seans1s_data *seans) {
    int isM; // есть ли метки?
    FILE *file;
    int i;
    char buf[680*2];

    isM = seans1s_test(filename);
    if (isM == 0)
        return 0;

    if (isM == 3)
        seans1s_save(filename, seans);

    file = fopen (filename, "a+b");
    if (file == NULL)
        return 0;

    ftruncate(fileno(file), 18000);

    for (i = 0; i < 680; i++) {
        buf[i*2] = (seans->m[i]) & 0xff;
        buf[i*2+1] = (seans->m[i]/256) & 0xff;
    }

    fseek(file, 0, SEEK_END);
    fwrite(buf, 680*2, 1, file);

    fclose (file);

    return 1;
}



/// =============================

int seans1s_noise(seans1s_data *seans, double *noise_acf, int len, int alt_start, int alt_end) {
    int i, j, k;

    for (i = 0; i < len; i++)
        noise_acf[i] = 0;

    k = 0; // обнулим счётчик количества "хороших" высот
    for (j = alt_start; j < alt_end; j++) {
        if (seans->m[j] == 0) {
            noise_acf[0] += seans->datp[j*4];
            for (i = 0; i < len; i++)
                noise_acf[i+1] += seans->dat[j][i];
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

/// =============================

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

/// =============================

double seans1c_alt(int H) {
    return H*9.821-35;//-44.815+9.821/2;
}


/// =============================


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

/// =============================

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

/// =============================

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

/// =============================

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

/// =============================

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
/// =============================

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


/// =============================


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

/// =============================

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

/// =============================

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

/// =============================

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

/// =============================


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
