
/*
 * Copyright 2011-2019, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#include "seans2.h"

/// =============================

int seans2_load_header(char *filename, seans_header *header)
{

FILE *file;

unsigned char  buffer[20];

if ( seans2_test(filename) == 0 )
    return 0;

file = fopen (filename, "rb");
if (file == NULL)
    return 0;

fread(buffer, sizeof(char), 20, file); // считать заголовок файла

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

fclose(file);

return 1;
}

/// =============================

int seans2_load(char *filename, seans2_data *seans)
{

FILE *file;

char *buffer;
unsigned char  header[20];
unsigned char  temp[4];
int i, j;
unsigned int sm = 0;
int buf_size, filetype;

filetype = seans2_test(filename);

if ( filetype == 0 )
    return 0;

if ( filetype == 1 )
    buf_size = (680*19*4+680*2)*4 + 680*4*4;
else
    buf_size = (680*19*4+680*2)*4 + 680*4*4 + 680;

buffer = (char*) malloc( buf_size ); // выделить память для буфера
if (buffer == NULL)
    return 0;

file = fopen (filename, "rb");
if (file == NULL)
    return 0;

fread(header, sizeof(char), 20, file); // считать заголовок файла

// разбор заголовка
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


fread(buffer, buf_size, 1, file); // считать данные в буфер
fclose (file); // закрыть файл

for (i = 0; i < 680 ; i++)
	for (j = 0; j < 19; j++)
		{
        memcpy(temp, buffer+sm, 4);
        seans -> dat1[i][j] = makeint(temp);
        sm += 4;
		}

for (i = 0; i < 680 ; i++)
	for (j = 0; j < 19; j++)
		{
		memcpy(temp, buffer+sm, 4);
		seans -> dat2[i][j] = makeint(temp);
		sm += 4;
		}

for (i = 0; i < 680 ; i++)
	for (j = 0; j < 19; j++)
		{
		memcpy(temp, buffer+sm, 4);
		seans -> dat3[i][j] = makeint(temp);
		sm += 4;
		}

for (i = 0; i < 680 ; i++)
	for (j = 0; j < 19; j++)
		{
		memcpy(temp, buffer+sm, 4);
		seans -> dat4[i][j] = makeint(temp);
		sm += 4;
		}

// загрузка "нуля" АЦП
for (i = 0; i < 680 ; i++)
	{
	memcpy(temp, buffer+sm, 4);
	seans -> dat01[i] = makeint(temp);
	sm += 4;
	}

for (i = 0; i < 680 ; i++)
	{
	memcpy(temp, buffer+sm, 4);
	seans -> dat02[i] = makeint(temp);
	sm += 4;
	}


// загрузка мощности по короткому импульсу

for (i = 0; i < 680 ; i++)
	{
	memcpy(temp, buffer+sm, 4);
	seans -> datps1[i] = makeint(temp);
	sm += 4;
	}

for (i = 0; i < 680 ; i++)
	{
	memcpy(temp, buffer+sm, 4);
	seans -> datps2[i] = makeint(temp);
	sm += 4;
	}

// загрузка "нуля" АЦП

for (i = 0; i < 680 ; i++)
	{
	memcpy(temp, buffer+sm, 4);
	seans -> dat03[i] = makeint(temp);
	sm += 4;
	}
for (i = 0; i < 680 ; i++)
	{
	memcpy(temp, buffer+sm, 4);
	seans -> dat04[i] = makeint(temp);
	sm += 4;
	}

if (filetype == 1)
    {
    for (i = 0; i < 680; i++)
        seans -> m[i] = 0;
    }
else
    {
    for (i = 0; i < 680; i++)
        {
        seans -> m[i] = buffer[sm];
        sm++;
        }
    }

free(buffer); // освобождение буфера

return 1;
}


/// =============================

int seans2_test(char *filename)
{
FILE *file;
long size;

file = fopen (filename, "rb");

if (file == NULL)
    return 0;

fseek (file,0,SEEK_END);
size = ftell(file);

fclose(file);

if (size == 223060)
    return 1;

if (size == 223740)
    return 2;

return 0;
}

/// =============================

int seans2_save(char *filename, seans2_data *seans)
{

FILE *f;
int i, j;
unsigned char c[4];
unsigned char  header[20];

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

for (j = 0; j < 680; j++)
for (i = 0; i < 19; i++)
    {
    makearray( c, seans->dat1[j][i]);
    fwrite (c, 4, 1, f);
    }

for (j = 0; j < 680; j++)
for (i = 0; i < 19; i++)
    {
    makearray( c, seans->dat2[j][i]);
    fwrite (c, 4, 1, f);
    }

for (j = 0; j < 680; j++)
for (i = 0; i < 19; i++)
    {
    makearray( c, seans->dat3[j][i]);
    fwrite (c, 4, 1, f);
    }

for (j = 0; j < 680; j++)
for (i = 0; i < 19; i++)
    {
    makearray( c, seans->dat4[j][i]);
    fwrite (c, 4, 1, f);
    }

for (j = 0; j < 680; j++)
    {
    makearray( c, seans->dat01[j]);
    fwrite (c, 4, 1, f);
    }

for (j = 0; j < 680; j++)
    {
    makearray( c, seans->dat02[j]);
    fwrite (c, 4, 1, f);
    }

for (j = 0; j < 680; j++)
    {
    makearray( c, seans->datps1[j]);
    fwrite (c, 4, 1, f);
    }

for (j = 0; j < 680; j++)
    {
    makearray( c, seans->datps2[j]);
    fwrite (c, 4, 1, f);
    }

for (j = 0; j < 680; j++)
    {
    makearray( c, seans->dat03[j]);
    fwrite (c, 4, 1, f);
    }

for (j = 0; j < 680; j++)
    {
    makearray( c, seans->dat04[j]);
    fwrite (c, 4, 1, f);
    }

fclose(f);

return 0;
}

/// =============================

double seans2_altL(int num)
{
return -82+4.583*num;
}

/// =============================

double seans2_altS(int num)
{
return -141+4.583*num;
}

/// =============================

double seans2_altL_front(int num)
{
return seans2_altL(num)+49.7;
}

/// =============================

int seans2_saveM0(char *filename)
{
int isM; // есть ли метки?
FILE *file;

isM = seans2_test(filename);
if (isM == 0)
    return 0;

if (isM == 1)
    return 1;

file = fopen(filename, "a+b");
if (file == NULL)
    return 0;

ftruncate(fileno(file), 223060);

fclose(file);

return 1;
}

/// =============================

int seans2_saveM3(char *filename, seans2_data *seans)
{
int isM;
FILE *file;
int i;
char buf[680];

isM = seans2_test(filename);
if (isM == 0)
    return 0;

file = fopen (filename, "a+b");
if (file == NULL)
    return 0;

ftruncate(fileno(file), 223060);

for (i = 0; i < 680; i++)
    buf[i] = (char)(seans->m[i]);

fseek(file, 0, SEEK_END);
fwrite(buf, 680, 1, file);

fclose (file);

return 1;
}

/// =============================

int seans2_noise(seans2_data *seans, double *noise_acf, int len, int alt_start, int alt_end, int ch)
{
int i, j, k;

for (i = 0; i < len; i++)
    noise_acf[i] = 0;

k = 0; // обнулим счётчик количества "хороших" высот
for (j = alt_start; j < alt_end; j++)
    {
    if (seans->m[j] == 0)
        {
        for (i = 0; i < len; i++)
            {
            switch (ch)
                {
                case 1:
                    noise_acf[i] += seans->dat1[j][i];
                    break;

                case 2:
                    noise_acf[i] += seans->dat2[j][i];
                    break;

                case 3:
                    noise_acf[i] += seans->dat3[j][i];
                    break;

                case 4:
                    noise_acf[i] += seans->dat4[j][i];
                    break;
                }; //switch ch
            } //for i
        k++;
        }//if m
    }//for j


if (k == 0)
    {
    for (i = 0; i < len; i++)
        noise_acf[i] = 0;
    return 1;
    }

for (i = 0; i < len; i++)
    noise_acf[i] /= k;

return 0;
}

/// =============================

int seans2_noise1(seans2_data *seans, double *acf_noise, int len, int alt_start, int alt_end)
{
return seans2_noise(seans, acf_noise, len, alt_start, alt_end, 1);
}

/// =============================

int seans2_noise2(seans2_data *seans, double *acf_noise, int len, int alt_start, int alt_end)
{
return seans2_noise(seans, acf_noise, len, alt_start, alt_end, 2);
}

/// =============================

int seans2_noise3(seans2_data *seans, double *acf_noise, int len, int alt_start, int alt_end)
{
return seans2_noise(seans, acf_noise, len, alt_start, alt_end, 3);
}

/// =============================

int seans2_noise4(seans2_data *seans, double *acf_noise, int len, int alt_start, int alt_end)
{
return seans2_noise(seans, acf_noise, len, alt_start, alt_end, 4);
}

/// =============================
