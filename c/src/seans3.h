
/*
 * Copyright 2011-2021, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#ifndef _Included_seans3
#define _Included_seans3

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct __attribute__((packed))
{

int day;
int month;
int year;
int hour;
int minute;
int second;

int np;
int nr;

double freq;

int magic;

int *dat1;
int *dat2;
int *dat3;
int *dat4;

} seans3_data ;

#define OK          (0)
#define ERR_FILE    (1)
#define ERR_MEM     (2)
#define ERR_MAGIC   (3)

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif
DLL_EXPORT int seans3_load(char *filename, seans3_data *seans);
DLL_EXPORT int seans3_close(seans3_data *seans);
#ifdef __cplusplus
}
#endif

#endif // _Included_seans3
